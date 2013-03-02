#include <unittest++/UnitTest++.h>
#include <maudio/AudioManager.h>
#include <mlog/Log.h>

int main() {
	maudio::AudioManager::instance().init();
#ifdef MAUDIO_TEST_SILENT
	maudio::AudioManager::instance().setListenerGain(0);
#else
	maudio::AudioManager::instance().setListenerGain(0.5);
	mlog::setDebugLevel(4, mlog::AUDIO);
#endif
	int ret = UnitTest::RunAllTests();
	maudio::AudioManager::instance().shutdown();
	return ret;
}
