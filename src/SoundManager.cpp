#include "SoundManager.h"
#include <cstdlib>
#include <iostream>

SoundManager::SoundManager() {
	engine = NULL;
}

SoundManager::~SoundManager() {
	if (engine != nullptr)
		engine->drop();
}

void SoundManager::init() {
#if defined(__linux__)
    const char* device = std::getenv("NIGHT_KNIGHT_ALSA_DEVICE");
    if (device == nullptr || device[0] == '\0')
        device = "pulse";

    const int options = ESEO_MULTI_THREADED |
        ESEO_LOAD_PLUGINS |
        ESEO_PRINT_DEBUG_INFO_TO_STDOUT;

    std::cout << "Starting irrKlang ALSA device: " << device << std::endl;
    engine = createIrrKlangDevice(ESOD_ALSA, options, device);
#else
	engine = createIrrKlangDevice();
#endif
	if (engine != nullptr)
		engine->setSoundVolume(0.5f);
}

ISoundEngine* SoundManager::getSoundEngine() {
	return engine;
}

ISound** SoundManager::getBgSoundPtr()
{
	return &bgSound;
}

ISound* SoundManager::changeBgMusic(const char* file, bool loop, bool pause) {
	if (engine == nullptr)
		return nullptr;
	if (bgSound != nullptr) {
		bgSound->stop();
		bgSound->drop();
	}
	bgSound = engine->play2D(file, loop, pause, true);
	//bgSound->setVolume(0.75);
	return bgSound;
}

void SoundManager::pauseBgMusic(bool pause) {
	if (bgSound != nullptr) {
		bgSound->setIsPaused(pause);
	}
}

void SoundManager::stopBgMusic() {
	if (bgSound != nullptr) {
		bgSound->stop();
		bgSound->drop();
		bgSound = nullptr;
	}
}
