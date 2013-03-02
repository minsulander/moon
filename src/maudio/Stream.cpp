#include "Stream.h"
#include "Sample.h"
#include <mlog/Log.h>
#include <osgDB/FileUtils>
#include <string.h>

using namespace mlog;

#define BUFFER_SIZE 4096*4
#define STREAM_BUFFERS 2

#define CHECK_AL_ERROR(message) \
{ ALenum error = alGetError(); \
if (error != AL_NO_ERROR) \
throw SampleException(std::string(#message) + ": " + OpenALErrorStringBuffer(error)); }

namespace maudio {

	Stream::Stream(const std::string& nfilename)
	: filename(nfilename), source(AL_NONE), format(AL_NONE)
	{
	}
	
	Stream::~Stream()
	{
		if (useStreamThread)
			streamThread.unregisterStream(this);
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(streamThread.mutex);
		if (source != AL_NONE)
			alSourceStop(source);
		while (buffers.size() > 0) {
			ALuint bufferID = buffers[0];
			if (source)
				alSourceUnqueueBuffers(source, 1, &bufferID);
			alDeleteBuffers(1, &bufferID);
			alGetError();
			buffers.erase(buffers.begin());
		}
	}
	
	void Stream::setSource(ALuint nsource)
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(streamThread.mutex);
		source = nsource;
	}
	
	void Stream::start()
	{
		if (source == AL_NONE)
			throw SampleException("Attempt to start a stream with no source");
		while (buffers.size() < STREAM_BUFFERS) {
		    OpenThreads::ScopedLock<OpenThreads::Mutex> lock(streamThread.mutex);
			ALuint bufferID = AL_NONE;
		    alGenBuffers(1, &bufferID);
		    CHECK_AL_ERROR("GenBuffers");
			if (!stream(bufferID))
				break;
	  		alSourceQueueBuffers(source, 1, &bufferID);
	  		CHECK_AL_ERROR("Queue buffers at start");
			buffers.push_back(bufferID);
		}
		if (useStreamThread)
			streamThread.registerStream(this);
	}
	
	void Stream::stop()
	{
		if (useStreamThread)
			streamThread.unregisterStream(this);
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(streamThread.mutex);
		if (source != AL_NONE)
			alSourceStop(source);
		while (buffers.size() > 0) {
			ALuint bufferID = buffers[0];
			if (source)
				alSourceUnqueueBuffers(source, 1, &bufferID);
			alDeleteBuffers(1, &bufferID);
			alGetError();
			buffers.erase(buffers.begin());
		}
	}
	
	Stream* Stream::get(const std::string& filename)
	{
		std::string path = osgDB::findDataFile(filename);
		if (path.length() == 0) {
			dout(ERROR) << "Stream file not found: " << filename << "\n";
			return NULL;
		}
		std::string ext = path.substr(path.length()-4);
		if (ext == ".ogg" || ext == ".OGG")
			return new OggStream(path);
		else if (ext == ".mp3" || ext == ".MP3")
			return new MP3Stream(path);
		else
			return new SndStream(path);
		return NULL;
	}
	
	void Stream::useThread(const bool value) { useStreamThread = value; }
	bool Stream::usingThread() { return useStreamThread; }
	
	bool Stream::isStreamingActive()
	{
		return streamThread.isRunning();
	}
	
	void Stream::stopStreaming()
	{
		{
			OpenThreads::ScopedLock<OpenThreads::Mutex> lock(streamThread.mutex);
			streamThread.setDone(true);
		}
		while (streamThread.isRunning()) {}
	}
	
	void Stream::update()
	{
		if (useStreamThread)
			return;
		updateStream();
	}
	
	void Stream::updateStream()
	{
		if (source == AL_NONE)
			return;

		int processed;
		bool active = true;

		alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
	
		while(processed--)
		{
			ALuint buffer;
			
			alSourceUnqueueBuffers(source, 1, &buffer);
			if (alGetError() != AL_NO_ERROR)
				break;
			//CHECK_AL_ERROR("Unqueue buffers");
	
			active = stream(buffer);
	
			alSourceQueueBuffers(source, 1, &buffer);
			CHECK_AL_ERROR("Queue buffers");
		}
	
		if (!active)
			alSourceStop(source);
		//return active;
	}
	
	bool Stream::useStreamThread = true;
	StreamThread Stream::streamThread;
	
//----------------------------- OGG ---------------------------------------


	OggStream::OggStream(const std::string& filename)
	: Stream(filename), freq(0)
	{
		oggFile.datasource = NULL;
	}
	
	OggStream::~OggStream()
	{
		if (oggFile.datasource)
			ov_clear(&oggFile);
	}
	
	double OggStream::getLength()
	{
		if (!oggFile.datasource)
			return 0.0;
		return ov_time_total(&oggFile, -1);
	}
	
	void OggStream::rewind()
	{
		if (!oggFile.datasource)
			return;
		int ret = ov_time_seek(&oggFile, 0);
		if (ret != 0)
			throw SampleException("Failed to seek in " + filename + ": " + errorString(ret));
	}
	
	void OggStream::open()
	{
		dout(3, AUDIO) << "Opening stream " << filename;
		dout(4, AUDIO) << ": OGG";
		vorbis_info *pInfo;
		char temp[1024];
		strncpy(temp, filename.c_str(), 1023);
		int ret = ov_fopen(temp, &oggFile);
		if (ret != 0)
			throw SampleException("Failed to open vorbis file " + filename + ": " + errorString(ret));

		// Get some information about the OGG file
		pInfo = ov_info(&oggFile, -1);
		dout(4, AUDIO) << " v" << pInfo->version << " " << 0.001*pInfo->rate << "kHz " 
		<< pInfo->channels << "ch ";
		if (pInfo->bitrate_upper == pInfo->bitrate_lower)
			dout(4, AUDIO) << "fixed " << pInfo->bitrate_nominal/1000 << "k";
		else
			dout(4, AUDIO) << "variable " << pInfo->bitrate_lower/1000 << "k < " 
			<< pInfo->bitrate_nominal/1000 << "k < " << pInfo->bitrate_upper/1000 << "k";
		dout(3, AUDIO) << "\n";
		if (pInfo->channels == 1)
			format = AL_FORMAT_MONO16;
		else
			format = AL_FORMAT_STEREO16;
		freq = pInfo->rate;
	}
	
	void OggStream::close()
	{
		dout(5, AUDIO) << "Closing stream " << filename << "\n";
	    ov_clear(&oggFile);
	    oggFile.datasource = NULL;
	}
	
	bool OggStream::stream(ALuint buffer)
	{
		if (!oggFile.datasource)
			open();
			
		char pcm[BUFFER_SIZE];
		int  size = 0;
		int  section;
		int  result;
	
		while(size < BUFFER_SIZE)
		{
			result = ov_read(&oggFile, pcm + size, BUFFER_SIZE - size, 0, 2, 1, &section);
		
			if(result > 0)
				size += result;
			else
				if(result < 0)
					throw errorString(result);
				else
					break;
		}
		
		if(size == 0)
			return false;
		alBufferData(buffer, format, pcm, size, freq);
		CHECK_AL_ERROR("Stream buffer data");
		
		return true;
	}
	

	std::string OggStream::errorString(int code)
	{
		switch(code)
		{
			case OV_ENOSEEK:
				return std::string("Bitstream is not seekable.");
			case OV_EINVAL:
				return std::string("Invalid argument.");
			case OV_EREAD:
				return std::string("Read from media.");
			case OV_ENOTVORBIS:
				return std::string("Not Vorbis data.");
			case OV_EVERSION:
				return std::string("Vorbis version mismatch.");
			case OV_EBADHEADER:
				return std::string("Invalid Vorbis header.");
			case OV_EFAULT:
				return std::string("Internal logic fault (bug or heap/stack corruption.");
			default:
				return std::string("Unknown Ogg error.");
		}
	}
	
// -------------------------- Sndfile ---------------------------------------

	SndStream::SndStream(const std::string& filename)
	: Stream(filename), sndfile(NULL), freq(0)
	{
	}
	
	SndStream::~SndStream()
	{
		if (sndfile)
			sf_close(sndfile);
	}
	
	void SndStream::open()
	{
		if (sndfile)
			close();
		sndfile = sf_open(filename.c_str(), SFM_READ, &sfinfo);
		if (sndfile == NULL)
			throw SampleException("Failed to open sound file " + filename);
		dout(3, AUDIO) << "Opening stream " << filename;
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
		if (sfinfo.channels == 1)
			format = AL_FORMAT_MONO16;
		else
			format = AL_FORMAT_STEREO16;
		freq = sfinfo.samplerate;
	}
	
	void SndStream::close()
	{
		if (sndfile) {
			dout(5, AUDIO) << "Closing stream " << filename << "\n";
			sf_close(sndfile);
		}
		sndfile = NULL;
	}

	bool SndStream::stream(ALuint buffer)
	{
		if (!sndfile)
			open();
		short array[BUFFER_SIZE];
		sf_count_t size = sf_read_short(sndfile, array, BUFFER_SIZE);
		if(size == 0)
			return false;
		alBufferData(buffer, format, array, size*sizeof(short), freq);
		CHECK_AL_ERROR("Stream buffer data");
		
		return true;
	}
	
	double SndStream::getLength()
	{
		if (!sndfile)
			return 0.0;
		return (double)sfinfo.frames/sfinfo.samplerate;
	}
	
	void SndStream::rewind()
	{
		if (!sndfile)
			return;
		sf_seek(sndfile, 0, SEEK_SET);
	}

//-------------------------------- MP3 --------------------------------------

// ssize_t is missing on windows... needed by mpg123
#ifdef WIN32
#define ssize_t long
#endif

	MP3Stream::MP3Stream(const std::string& filename)
	: Stream(filename), mh(NULL), freq(0), channels(0)
	{
	}
	
	MP3Stream::~MP3Stream()
	{
		if (mh) {
			mpg123_close(mh);
			mpg123_delete(mh);
		}
	}
	
	void MP3Stream::open()
	{
		if (mh)
			close();
		int err = MPG123_OK;
		long rate = 0;
		int encoding = 0;
		
		if( (mh = mpg123_new(NULL, &err)) == NULL
			// Let mpg123 work with the file, that excludes MPG123_NEED_MORE messages.
			|| mpg123_open(mh, filename.c_str()) != MPG123_OK
			// Peek into track and get first output format.
			|| mpg123_getformat(mh, &rate, &channels, &encoding) != MPG123_OK ) {
			dout(ERROR, AUDIO) << "Trouble with mpg123: " << (mh==NULL ? mpg123_plain_strerror(err) : mpg123_strerror(mh)) << "\n";
			mpg123_close(mh);
			mpg123_delete(mh);
			return;
		}
		
		dout(3, AUDIO) << "Opening stream " << filename;
		dout(4, AUDIO) << ": MP3 " << (float)rate/1000.f << " kHz " << channels << "ch";
		dout(3, AUDIO) << "s\n";
		
		mpg123_format_none(mh);
		mpg123_format(mh, rate, channels, encoding);
		if (channels == 1)
			format = AL_FORMAT_MONO16;
		else
			format = AL_FORMAT_STEREO16;
		freq = rate;
	}

	void MP3Stream::close()
	{
		if (mh) {
			mpg123_close(mh);
			mpg123_delete(mh);
		}
		mh = NULL;
	}
	
	bool MP3Stream::stream(ALuint bufferID)
	{
		if (!mh)
			open();
			
		unsigned char array[BUFFER_SIZE];
		size_t size = 0;
		int err = mpg123_read(mh, array, BUFFER_SIZE, &size);
		if (err != MPG123_OK && err != MPG123_DONE) {
			dout(3, AUDIO) << "\n";
			dout(ERROR, AUDIO) << "Decoding " << filename << " failed: " << (err == MPG123_ERR ? mpg123_strerror(mh) : mpg123_plain_strerror(err)) << "\n";
			mpg123_close(mh);
			mpg123_delete(mh);
			return false;
		}		
		alBufferData(bufferID, format, array, size, freq);
		CHECK_AL_ERROR("Stream buffer data");
		if (err == MPG123_DONE)
			return false;
			
		return true;
	}
	
	double MP3Stream::getLength()
	{
		if (!mh)
			return 0.0;
		off_t samples = mpg123_length(mh);
		return (double) samples/freq;
	}
	
	void MP3Stream::rewind()
	{
		if (!mh)
			return;
		mpg123_seek(mh, 0, SEEK_SET);
	}

//--------------------------- StreamThread ----------------------------------

	void StreamThread::run()
	{
		dout(7, AUDIO) << "Starting stream thread\n";
		done = false;
		while (!done) {
			mutex.lock();
			for (StreamList::iterator it = streams.begin(); it != streams.end(); it++) {
				if (it->valid())
					it->get()->updateStream();
			}
			mutex.unlock();
			//OpenThreads::Thread::microSleep(1000);
		}
		dout(7, AUDIO) << "Stream thread done\n";
	}
	
	void StreamThread::registerStream(Stream *stream)
	{
		for (StreamList::iterator it = streams.begin(); it != streams.end(); it++) {
			if (it->get() == stream)
				return;
		}
		mutex.lock();
		streams.push_back(stream);
		mutex.unlock();
		if (!isRunning())
			start();
	}
	
	void StreamThread::unregisterStream(Stream *stream)
	{
		mutex.lock();
		for (StreamList::iterator it = streams.begin(); it != streams.end(); it++) {
			if (it->get() == stream) {
				streams.erase(it);
				break;
			}
		}
		mutex.unlock();
		if (streams.size() == 0)
			done = true;
	}
	
}
