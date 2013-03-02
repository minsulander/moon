#include "Sample.h"
#include <mlog/Log.h>
#include <osgDB/FileUtils>
#include <vorbis/vorbisfile.h>
#include <sndfile.h>
#include <string.h>

// ssize_t is missing on windows... needed by mpg123
#ifdef WIN32
#define ssize_t long
#endif
#include <mpg123.h>

#include <sstream>

using namespace mlog;

namespace maudio {
	
	std::string OpenALErrorStringBuffer(ALenum error, ALuint buffer)
	{
		std::stringstream ss;
		switch (error) {
			case AL_NO_ERROR: ss << "AL_NO_ERROR"; break;
			case AL_INVALID_NAME: ss << "AL_INVALID_NAME"; break;
			case AL_INVALID_ENUM: ss << "AL_INVALID_ENUM"; break;
			case AL_INVALID_VALUE: ss << "AL_INVALID_VALUE"; break;
			case AL_INVALID_OPERATION: ss << "AL_INVALID_OPERATION"; break;
			case AL_OUT_OF_MEMORY: ss << "AL_OUT_OF_MEMORY"; break;
			default: ss << "??? " << error; break;
		}
		if (buffer)
			ss << " buffer " << buffer;
		return ss.str();
	}
	
#define CHECK_AL_ERROR(message) \
ALenum error = alGetError(); \
if (error != AL_NO_ERROR) \
throw SampleException(std::string(#message) + ": " + filename + ": " + OpenALErrorStringBuffer(error,bufferID), this);
	
#define CHECK_AL_ERROR_STATIC(message) \
ALenum error = alGetError(); \
if (error != AL_NO_ERROR) \
throw SampleException(std::string(#message) + ": " + OpenALErrorStringBuffer(error));
	
	
	
	
	Sample::Sample(const std::string& newFileName)
	: filename(newFileName), bufferID(0)
	{
	}
	
	Sample::Sample(const SampleBuffer& buffer)
	: filename("(buffer)"), bufferID(0)
	{
		bufferID = loadSampleBuffer(buffer);
	}
	
	Sample::~Sample()
	{
		dout(5, AUDIO) << "~Sample(" << bufferID << ")" << "\n";
		if (bufferID != 0)
			alDeleteBuffers(1, &bufferID);
	}
	
	void Sample::load()
	{
		if (filename == "(buffer)")
			return;
		if (bufferID != 0)
			alDeleteBuffers(1, &bufferID);
		std::string path = osgDB::findDataFile(filename);
		if (path.length() == 0)
			throw SampleException("Sound file not fouund: " + path, this);
		std::string ext = path.substr(path.length()-4);
		if (ext == ".ogg" || ext == ".OGG")
			bufferID = loadOGG(path);
		else if (ext == ".mp3" || ext == ".MP3")
			bufferID = loadMP3(path);
		else
			bufferID = loadSndfile(path);
		if (bufferID == AL_NONE)
			throw SampleException("Failed to load sound file: " + path, this);
		ALint freq, bits, channels, size;
		alGetBufferi(bufferID, AL_FREQUENCY, &freq);
		alGetBufferi(bufferID, AL_BITS, &bits);
		alGetBufferi(bufferID, AL_CHANNELS, &channels);
		alGetBufferi(bufferID, AL_SIZE, &size);
		dout(5, AUDIO) << "Loaded Sample(" << bufferID << "): " << path << "\n";
	}
	
	ALuint Sample::getBufferID()
	{
		if (!bufferID && filename.length() > 0)
			load();
		return bufferID;
	}
	
	double Sample::getLength() const
	{
		ALint freq, bits, size;
		alGetBufferi(bufferID, AL_FREQUENCY, &freq);
		alGetBufferi(bufferID, AL_BITS, &bits);
		alGetBufferi(bufferID, AL_SIZE, &size);
		return (8.0*size/bits/freq);
	}
	
	Sample* Sample::get(const std::string& filename)
	{
		std::string path = osgDB::findDataFile(filename);
		if (path.length() == 0) {
			dout(ERROR) << "Sample file not found: " << filename << "\n";
			return NULL;
		}
		SampleReuseMap::iterator it = reuseSamples.find(path);
		if (it != reuseSamples.end() && it->second.valid()) {
			dout(5, AUDIO) << "Reusing sample for " << path << "\n";
			return it->second.get();
		}
		Sample *sample = new Sample(path);
		reuseSamples[path] = sample;
		return sample;
	}
	
#define BUFFER_SIZE 32768
	/// \throw SampleException if opening the file failed, the file is the wrong format, or decoding failed
	ALuint Sample::loadOGG(const std::string& filename)
	{
		int endian = 0;                         // 0 for Little-Endian, 1 for Big-Endian
		int bitStream;
		long bytes;
		char array[BUFFER_SIZE];                // Local fixed size array
		
		dout(3, AUDIO) << "Loading " << filename;
		dout(4, AUDIO) << ": OGG";
		vorbis_info *pInfo;
		OggVorbis_File oggFile;
		
		// Try opening the given file
		char temp[1024];
		strncpy(temp, filename.c_str(), 1023);
		if (ov_fopen(temp, &oggFile) != 0)
			throw SampleException("Failed to open vorbis file " + filename);

		// Get some information about the OGG file
		pInfo = ov_info(&oggFile, -1);
		dout(4, AUDIO) << " v" << pInfo->version << " " << 0.001*pInfo->rate << "kHz " 
		<< pInfo->channels << "ch ";
		if (pInfo->bitrate_upper == pInfo->bitrate_lower == pInfo->bitrate_nominal)
			dout(4, AUDIO) << "fixed " << pInfo->bitrate_nominal;
		else
			dout(4, AUDIO) << "variable " << pInfo->bitrate_lower << "<" 
			<< pInfo->bitrate_nominal << "<" << pInfo->bitrate_upper;
		dout(3, AUDIO) << "\n";
		ALenum format;
		if (pInfo->channels == 1)
			format = AL_FORMAT_MONO16;
		else
			format = AL_FORMAT_STEREO16;
		ALsizei freq = pInfo->rate;
		
		std::vector<char> buffer;
		do {
			bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);
			
			if (bytes < 0) {           
				ov_clear(&oggFile);
				throw SampleException("Error decoding vorbis file " + filename);
			}
			
			// Append to end of buffer
			buffer.insert(buffer.end(), array, array + bytes);
		} while (bytes > 0);
		
		ov_clear(&oggFile);
		
		// Upload sound data to buffer
		ALuint bufferID;
		alGenBuffers(1, &bufferID);
		alBufferData(bufferID, format, &buffer[0], static_cast<ALsizei>(buffer.size()), freq);
		CHECK_AL_ERROR_STATIC(loadOGG);
		
		return bufferID;
	}
	
	/// \throw SampleException if opening the file failed
	ALuint Sample::loadSndfile(const std::string& filename)
	{
		SF_INFO sfinfo;
		SNDFILE *sndfile = sf_open(filename.c_str(), SFM_READ, &sfinfo);
		if (sndfile == NULL)
			throw SampleException("Failed to open sound file " + filename);
		dout(3, AUDIO) << "Loading " << filename;
		if (sfinfo.format & SF_FORMAT_WAV)
			dout(4, AUDIO) << ": WAV ";
		else if (sfinfo.format & SF_FORMAT_AIFF)
			dout(4, AUDIO) << ": AIFF ";
		else if (sfinfo.format & SF_FORMAT_AU)
			dout(4, AUDIO) << ": AU ";
		else if (sfinfo.format & SF_FORMAT_RAW)
			dout(4, AUDIO) << ": RAW ";
		else if (sfinfo.format & SF_FORMAT_FLAC)
			dout(4, AUDIO) << ": FLAC ";
		else if (sfinfo.format & SF_FORMAT_CAF)
			dout(4, AUDIO) << ": CAF ";
		else
			dout(4, AUDIO) << ": sndfile? ";
		if (sfinfo.format & SF_FORMAT_PCM_S8)
			dout(4, AUDIO) << "8bit ";
		else if (sfinfo.format & SF_FORMAT_PCM_16)
			dout(4, AUDIO) << "16bit ";
		else if (sfinfo.format & SF_FORMAT_PCM_24)
			dout(4, AUDIO) << "24bit ";
		else if (sfinfo.format & SF_FORMAT_PCM_32)
			dout(4, AUDIO) << "32bit ";
		else if (sfinfo.format & SF_FORMAT_PCM_U8)
			dout(4, AUDIO) << "U8bit ";
		else if (sfinfo.format & SF_FORMAT_FLOAT)
			dout(4, AUDIO) << "32bit float ";
		else if (sfinfo.format & SF_FORMAT_DOUBLE)
			dout(4, AUDIO) << "64bit ";
		dout(4, AUDIO) << 0.001*sfinfo.samplerate << "kHz ";
		dout(4, AUDIO) << (float)sfinfo.frames/sfinfo.samplerate << "s ";
		dout(4, AUDIO) << sfinfo.channels << "ch";
		dout(3, AUDIO) << "\n";
		std::vector<short> buffer;
		short array[BUFFER_SIZE];                // Local fixed size array
		sf_count_t shorts;
		do {
			shorts = sf_read_short(sndfile, array, BUFFER_SIZE);
			buffer.insert(buffer.end(), array, array + shorts);
		} while (shorts > 0);
		sf_close(sndfile);
		
		ALenum format;
		if (sfinfo.channels == 1)
			format = AL_FORMAT_MONO16;
		else
			format = AL_FORMAT_STEREO16;
		ALsizei freq = sfinfo.samplerate;
		
		ALuint bufferID;
		alGenBuffers(1, &bufferID);
		alBufferData(bufferID, format, &buffer[0], static_cast<ALsizei>(buffer.size()*sizeof(short)), freq);
		CHECK_AL_ERROR_STATIC(loadSndfile);
		return bufferID;
	}
	
	/// \throw SampleException on OpenAL errors when setting buffer data
	ALuint Sample::loadSampleBuffer(const SampleBuffer& buffer, const int freq, const int channels)
	{
		ALenum format;
		if (channels == 1)
			format = AL_FORMAT_MONO16;
		else
			format = AL_FORMAT_STEREO16;
		
		ALuint bufferID;
		alGenBuffers(1, &bufferID);
		alBufferData(bufferID, format, &buffer[0], static_cast<ALsizei>(buffer.size()*sizeof(short)), freq);
		CHECK_AL_ERROR_STATIC(loadSampleBuffer);
		return bufferID;
	}
	
	
	ALuint Sample::loadMP3(const std::string& filename)
	{
		mpg123_handle *mh = NULL;
		int err = MPG123_OK;
		long rate = 0;
		int channels = 0;
		int encoding = 0;
		size_t done = 0;
		off_t samples = 0;
		unsigned short* buf = NULL;
		size_t buf_size = 0;
		
		if( (mh = mpg123_new(NULL, &err)) == NULL
			// Let mpg123 work with the file, that excludes MPG123_NEED_MORE messages.
			|| mpg123_open(mh, filename.c_str()) != MPG123_OK
			// Peek into track and get first output format.
			|| mpg123_getformat(mh, &rate, &channels, &encoding) != MPG123_OK ) {
			dout(ERROR, AUDIO) << "Trouble with mpg123: " << (mh==NULL ? mpg123_plain_strerror(err) : mpg123_strerror(mh)) << "\n";
			mpg123_close(mh);
			mpg123_delete(mh);
			return AL_NONE;
		}
		
		dout(3, AUDIO) << "Loading " << filename;
		dout(4, AUDIO) << ": MP3 " << (float)rate/1000.f << " kHz " << channels << "ch";
		
		mpg123_format_none(mh);
		mpg123_format(mh, rate, channels, encoding);
		buf_size = mpg123_outblock(mh);
		buf = (unsigned short*) malloc(buf_size);

		std::vector<short> buffer;
		do {
			err = mpg123_read(mh, (unsigned char*) buf, buf_size, &done);
			buffer.insert(buffer.end(), buf, buf + done/sizeof(short));
			samples += done/sizeof(short);
		} while (err == MPG123_OK);
				
		if (err != MPG123_DONE) {
			dout(3, AUDIO) << "\n";
			dout(ERROR, AUDIO) << "Decoding " << filename << " failed: " << (err == MPG123_ERR ? mpg123_strerror(mh) : mpg123_plain_strerror(err)) << "\n";
			mpg123_close(mh);
			mpg123_delete(mh);
			free(buf);
			return AL_NONE;
		}
		
		dout(4, AUDIO) << " " << (double) samples/channels/rate;
		dout(3, AUDIO) << "s\n";

		ALenum format;
		if (channels == 1)
			format = AL_FORMAT_MONO16;
		else
			format = AL_FORMAT_STEREO16;

		ALuint bufferID;
		alGenBuffers(1, &bufferID);
		alBufferData(bufferID, format, &buffer[0], static_cast<ALsizei>(buffer.size()*sizeof(short)), rate);
		CHECK_AL_ERROR_STATIC(loadMP3);
		
		mpg123_close(mh);
		mpg123_delete(mh);
		free(buf);
		return bufferID;
	}
	
	void saveSampleBuffer(const std::string& filename, const SampleBuffer& buffer, const int freq, const int channels)
	{
		dout(2, AUDIO) << "Saving sample buffer: " << filename << "\n";
		SF_INFO sfinfo;
		sfinfo.samplerate = freq;
		sfinfo.channels = channels;
		sfinfo.format = SF_FORMAT_PCM_16;
		std::string ext = filename.substr(filename.find_last_of(".")+1);
		if (ext == "wav" || ext == "WAV")
			sfinfo.format |= SF_FORMAT_WAV;
		else if (ext == "aif" || ext == "AIF" || ext == "aiff" || ext == "AIFF")
			sfinfo.format |= SF_FORMAT_AIFF;
		else
			throw SampleException("Unknown file extension '" + ext + "'");
		if (!sf_format_check(&sfinfo))
			throw SampleException("Invalid format");
		SNDFILE *file = sf_open(filename.c_str(), SFM_WRITE, &sfinfo);
		if (!file)
			throw SampleException("Failed to open sound file '" + filename + "'");
		sf_count_t len = sf_write_short(file, &buffer[0], buffer.size());
		if (len != buffer.size())
			throw SampleException("Incomplete write");
		sf_close(file);
	}
	
	Sample::SampleReuseMap Sample::reuseSamples;

}
