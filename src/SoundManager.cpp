#include "SoundManager.hpp"
#include <iostream>

SoundManager::SoundManager() 
    : backgroundMusic(nullptr), soundEnabled(true), volume(64) {}

SoundManager::~SoundManager() {
    cleanup();
}

bool SoundManager::initialize() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer initialization failed: " << Mix_GetError() << std::endl;
        return false;
    }
    
    Mix_Volume(-1, volume);
    return true;
}

void SoundManager::cleanup() {
    for (auto& pair : sounds) {
        if (pair.second) {
            Mix_FreeChunk(pair.second);
        }
    }
    sounds.clear();
    
    if (backgroundMusic) {
        Mix_FreeMusic(backgroundMusic);
        backgroundMusic = nullptr;
    }
    
    Mix_CloseAudio();
}

bool SoundManager::loadSound(const std::string& name, const std::string& filename) {
    Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());
    if (!sound) {
        std::cerr << "Failed to load sound " << filename << ": " << Mix_GetError() << std::endl;
        return false;
    }
    
    sounds[name] = sound;
    return true;
}

void SoundManager::playSound(const std::string& name) {
    if (!soundEnabled) return;
    
    auto it = sounds.find(name);
    if (it != sounds.end() && it->second) {
        Mix_PlayChannel(-1, it->second, 0);
    }
}

bool SoundManager::loadMusic(const std::string& filename) {
    backgroundMusic = Mix_LoadMUS(filename.c_str());
    if (!backgroundMusic) {
        std::cerr << "Failed to load music " << filename << ": " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void SoundManager::playMusic(bool loop) {
    if (!soundEnabled || !backgroundMusic) return;
    
    Mix_PlayMusic(backgroundMusic, loop ? -1 : 0);
}

void SoundManager::stopMusic() {
    Mix_HaltMusic();
}

void SoundManager::setVolume(int newVolume) {
    volume = newVolume;
    Mix_Volume(-1, volume);
    Mix_VolumeMusic(volume);
}

void SoundManager::setSoundEnabled(bool enabled) {
    soundEnabled = enabled;
    if (!enabled) {
        stopMusic();
    }
}

bool SoundManager::isSoundEnabled() const {
    return soundEnabled;
}
