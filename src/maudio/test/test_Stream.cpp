#include <unittest++/UnitTest++.h>
#include <maudio/StreamSource.h>
#include <maudio/AudioManager.h>
#include <osgDB/FileUtils>
#include <mlog/Log.h>
#include <cmath>

using namespace maudio;
using namespace mlog;

/// \todo streamsource with no stream / not found
/// + sample same thing

#ifdef MAUDIO_TEST_SILENT
#  define DURATION 100000
#else
#  define DURATION 500000
#endif

#ifdef MAUDIO_TESTSTREAM_WAV
TEST (StreamSourceWAV) {
	CHECK(!Stream::isStreamingActive());
	osg::ref_ptr<StreamSource> source = new StreamSource(MAUDIO_TESTSTREAM_WAV);
	source->initialize();
	CHECK(source->isInitialized());
	source->realize();
	CHECK(source->isRealized());
	dout(1, AUDIO) << "Playing stream " << MAUDIO_TESTSTREAM_WAV << "\n";
	source->play();
	CHECK(source->isPlaying());
	if (Stream::usingThread())
		CHECK(Stream::isStreamingActive());
	OpenThreads::Thread::microSleep(DURATION);
	source->stop();
	CHECK(!source->isPlaying());
	source->unrealize();
	OpenThreads::Thread::microSleep(10000);	
	CHECK(!Stream::isStreamingActive());
}

TEST (StreamSourceCopy) {
	osg::ref_ptr<StreamSource>
		orig = new StreamSource(MAUDIO_TESTSTREAM_WAV),
		source = new StreamSource(*orig.get(), osg::CopyOp::SHALLOW_COPY);
	source->initialize();
	CHECK(source->isInitialized());
	source->realize();
	CHECK(source->isRealized());
	dout(1, AUDIO) << "  .. copied\n";
	source->play();
	CHECK(source->isPlaying());
	OpenThreads::Thread::microSleep(DURATION);
	source->stop();
	CHECK(!source->isPlaying());
}

#endif

#ifdef MAUDIO_TESTSTREAM_OGG
TEST (StreamSourceOGG) {
	osg::ref_ptr<StreamSource> source = new StreamSource(MAUDIO_TESTSTREAM_OGG);
	dout(1, AUDIO) << "Playing stream " << MAUDIO_TESTSTREAM_OGG << "\n";
	source->play();
	CHECK(source->isPlaying());
	OpenThreads::Thread::microSleep(DURATION);
	source->stop();
	CHECK(!source->isPlaying());
	// Try rewinding
	source->rewind();
	dout(1, AUDIO) << "  .. stop, rewind and play\n";
	source->play();
	CHECK(source->isPlaying());
	OpenThreads::Thread::microSleep(DURATION);
	source->stop();
	CHECK(!source->isPlaying());
}
#endif


#ifdef MAUDIO_TESTSTREAM_MP3
TEST (StreamSourceMP3) {
	osg::ref_ptr<StreamSource> source = new StreamSource(MAUDIO_TESTSTREAM_MP3);
	dout(1, AUDIO) << "Playing stream " << MAUDIO_TESTSTREAM_MP3 << "\n";
	source->play();
	CHECK(source->isPlaying());
	OpenThreads::Thread::microSleep(DURATION);
	// Try rewinding
	source->rewind();
	dout(1, AUDIO) << "  .. rewind\n";
	if (Stream::usingThread())
		CHECK(source->isPlaying());
	OpenThreads::Thread::microSleep(DURATION);
	source->stop();
	CHECK(!source->isPlaying());
}
#endif

#if !defined(MAUDIO_TEST_SILENT) && defined(MAUDIO_TESTSTREAM_WAV) && defined(MAUDIO_TESTSTREAM_OGG) && defined(MAUDIO_TESTSTREAM_MP3)
TEST (StreamSeveralSources) {
	osg::ref_ptr<StreamSource>
		source1 = new StreamSource(MAUDIO_TESTSTREAM_WAV),
		source2 = new StreamSource(MAUDIO_TESTSTREAM_OGG),
		source3 = new StreamSource(MAUDIO_TESTSTREAM_MP3);
	source2->setPosition(osg::Vec3(-1,0,0));
	source3->setPosition(osg::Vec3(1,0,0));
	dout(1, AUDIO) << "Playing all three\n";
	source1->play(); source2->play(); source3->play();
	OpenThreads::Thread::microSleep(DURATION*4);
}
#endif

TEST (NonExistingStreamSource) {
	int level = getDebugLevel();
	setDebugLevel(-3);
	osg::ref_ptr<StreamSource> source = new StreamSource("nonexistent.wav");
	setDebugLevel(level);
	source->play();
	CHECK(!source->isInitialized());
	CHECK(!source->isRealized());
	CHECK(!source->isPlaying());
}
