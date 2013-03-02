#ifndef MAUDIO_SAMPLE_H
#define MAUDIO_SAMPLE_H

#include "OpenALHeaders.h"
#include "Export.h"
#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/observer_ptr>
#include <string>
#include <vector>
#include <map>

namespace maudio {

	/// \addtogroup audio
	/// @{
	
	typedef std::vector<short> SampleBuffer;
	
	extern std::string OpenALErrorStringBuffer(ALenum error, ALuint buffer=0);
		
	class MAUDIO_EXPORT Sample : public osg::Referenced {
	public:
		Sample(const std::string& filename);
		Sample(const SampleBuffer& buffer);
		
		const std::string& getFileName() const { return filename; }
		/// Load the sample file into memory
		void load();
		/// Get OpenAL buffer
		ALuint getBufferID();
		/// Get sample length in seconds
		double getLength() const;
		
		/// Reuse existing or create new sample for the specified filename
		static Sample *get(const std::string& filename);
		
	protected:
		typedef std::map<std::string, osg::observer_ptr<Sample> > SampleReuseMap;
		static SampleReuseMap reuseSamples;
		
		/// Load an OGG file (using the vorbisfile library)
		static ALuint loadOGG(const std::string& filename);
		/// Load a sample file (using the sndfile library)
		static ALuint loadSndfile(const std::string& filename);
		/// Load a SampleBuffer containing a sample of the specified frequency and format (mono or stereo supported)
		static ALuint loadSampleBuffer(const SampleBuffer& buffer, const int freq=44100, const int channels=1);
		/// Load an MP3 file (using the libmpg123 library)
		static ALuint loadMP3(const std::string& filename);
		
	private:
		virtual ~Sample();
		std::string filename;
		ALuint bufferID;
	};
	
	/// Exception thrown by Sample on errors
	class MAUDIO_EXPORT SampleException : public std::exception {
	public:
		SampleException(const std::string& nmessage, const Sample* nsample = NULL) { 
			message = nmessage;
			sample = nsample;
		}
		
		~SampleException() throw() { sample = NULL; }
		virtual const char* what() const throw() { return message.c_str(); }
		const Sample *getSample() { return sample; }
	private:
		std::string message;
		const Sample *sample;
	};
	
	extern void saveSampleBuffer(const std::string& filename, const SampleBuffer& buffer, const int freq=44100, const int channels=1);
	
	/// @}
}

#endif
