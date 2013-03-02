#include <unittest++/UnitTest++.h>
#include <maudio/SingleSource.h>
#include <maudio/AudioManager.h>
#include <mlog/Log.h>
#include <OpenThreads/Thread>

using namespace maudio;
using namespace mlog;

#ifdef MAUDIO_TEST_SILENT
#  define DURATION 10000
#else
#  define DURATION 125000
#endif

#ifdef MAUDIO_TESTFILE_WAV
TEST (SampleSourceWAV) {
	osg::ref_ptr<SingleSource> source = new SingleSource;
	source->setSample(Sample::get(MAUDIO_TESTFILE_WAV));
	dout(1, AUDIO) << "Playing sample " << MAUDIO_TESTFILE_WAV << "\n";
	source->play();
	CHECK(source->isPlaying());
	OpenThreads::Thread::microSleep(DURATION);
	source->stop();
	CHECK(!source->isPlaying());
}
#endif

#ifdef MAUDIO_TESTFILE_OGG
TEST (SampleSourceOGG) {
	osg::ref_ptr<SingleSource> source = new SingleSource;
	source->setSample(Sample::get(MAUDIO_TESTFILE_OGG));
	dout(1, AUDIO) << "Playing sample " << MAUDIO_TESTFILE_OGG << "\n";
	source->play();
	CHECK(source->isPlaying());
	OpenThreads::Thread::microSleep(DURATION);
	source->stop();
	CHECK(!source->isPlaying());
}
#endif

#ifdef MAUDIO_TESTFILE_MP3
TEST (SampleSourceMP3) {
	osg::ref_ptr<SingleSource> source = new SingleSource;
	source->setSample(Sample::get(MAUDIO_TESTFILE_MP3));
	dout(1, AUDIO) << "Playing sample " << MAUDIO_TESTFILE_MP3 << "\n";
	source->play();
	CHECK(source->isPlaying());
	OpenThreads::Thread::microSleep(DURATION);
	source->stop();
	CHECK(!source->isPlaying());
}
#endif

#if !defined(MAUDIO_TEST_SILENT) && defined(MAUDIO_TESTFILE_WAV) && defined(MAUDIO_TESTFILE_OGG) && defined(MAUDIO_TESTFILE_MP3)
TEST (SampleSeveralSources) {
	osg::ref_ptr<SingleSource>
		source1 = new SingleSource(MAUDIO_TESTFILE_WAV),
		source2 = new SingleSource(MAUDIO_TESTFILE_OGG),
		source3 = new SingleSource(MAUDIO_TESTFILE_MP3);
	source2->setPosition(osg::Vec3(-1,0,0));
	source3->setPosition(osg::Vec3(1,0,0));
	OpenThreads::Thread::microSleep(DURATION);
	dout(1, AUDIO) << "Playing all three\n";
	source1->play(); source2->play(); source3->play();
	OpenThreads::Thread::microSleep(DURATION*2);
}
#endif

TEST (NonExistingSampleSource) {
	int level = getDebugLevel();
	setDebugLevel(-3);
	osg::ref_ptr<SingleSource> source = new SingleSource("nonexistent.wav");
	setDebugLevel(level);
	source->initialize();
	CHECK(!source->isInitialized());
	source->realize();
	CHECK(!source->isRealized());
	source->play();
	CHECK(!source->isPlaying());
}

