#ifndef MAUDIO_STREAM_H
#define MAUDIO_STREAM_H

#include "OpenALHeaders.h"
#include "Export.h"
#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/observer_ptr>
#include <string>
#include <deque>
#include <vector>

#include <sndfile.h>
// ssize_t is missing on windows... needed by mpg123
#ifdef WIN32
#define ssize_t long
#endif
#include <mpg123.h>
#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>

#include <OpenThreads/Thread>
#include <OpenThreads/Mutex>
	
namespace maudio {

	/// \addtogroup audio
	/// @{
	
	class StreamThread;
	
	class MAUDIO_EXPORT Stream : public osg::Referenced {
	public:
		Stream(const std::string& filename);
		virtual ~Stream();
		
		const std::string& getFileName() const { return filename; }

		void setSource(ALuint source);
		void start();
		void stop();
		virtual double getLength() = 0;
		virtual void rewind() = 0;
		
		/// Get a new stream of appropriate class for the specified filename
		static Stream *get(const std::string& filename);
		
		static void useThread(const bool value);
		static bool usingThread();
		static bool isStreamingActive();
		static void stopStreaming();
		
		virtual void update();
		
	protected:
	
		virtual void updateStream();
		virtual bool stream(ALuint buffer) = 0;
		
		std::string filename;
		typedef std::deque<ALuint> BufferList;
		BufferList buffers;
		ALuint source;
		ALenum format;
		
		static bool useStreamThread;
		static StreamThread streamThread;
		friend class StreamThread;
	};
	
//----------------------------- OGG ---------------------------------------

	class MAUDIO_EXPORT OggStream : public Stream {
	public:
		OggStream(const std::string& filename);
		virtual ~OggStream();
		
		virtual double getLength();
		virtual void rewind();
	
	protected:
		void open();
		void close();
		virtual bool stream(ALuint buffer);
		std::string errorString(int code);
		
	private:
        OggVorbis_File oggFile;
        ALsizei freq;
	};
	
// -------------------------- Sndfile ---------------------------------------

	class MAUDIO_EXPORT SndStream : public Stream {
	public:
		SndStream(const std::string& filename);
		virtual ~SndStream();
		
		virtual double getLength();
		virtual void rewind();
	
	protected:
		void open();
		void close();
		virtual bool stream(ALuint buffer);
		
	private:
		SNDFILE *sndfile;
		SF_INFO sfinfo;
        ALsizei freq;
	};
	
// -------------------------- MP3 ---------------------------------------

	class MAUDIO_EXPORT MP3Stream : public Stream {
	public:
		MP3Stream(const std::string& filename);
		virtual ~MP3Stream();
		
		virtual double getLength();
		virtual void rewind();
	
	protected:
		void open();
		void close();
		virtual bool stream(ALuint buffer);
		
	private:
		mpg123_handle *mh;
        ALsizei freq;
        int channels;
	};
	

//--------------------------- StreamThread ----------------------------------
	
	class MAUDIO_EXPORT StreamThread : public OpenThreads::Thread {
	public:
		virtual void run();
		void registerStream(Stream *stream);
		void unregisterStream(Stream *stream);
		unsigned int getNumStreams() { return streams.size(); }
		void setDone(const bool value) { done = true; }
	protected:
		OpenThreads::Mutex mutex;
		friend class Stream;
	private:
		typedef std::vector< osg::observer_ptr<Stream> > StreamList;
		StreamList streams;
		bool done;
	};
	
	/// @}

}

#endif
