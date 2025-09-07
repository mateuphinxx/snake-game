#pragma once
#include <SDL_mixer.h>
#include <string>
#include <unordered_map>

class SoundManager {
private:
    std::unordered_map<std::string, Mix_Chunk*> sounds;
    Mix_Music* backgroundMusic;
    bool soundEnabled;
    int volume;

public:
    SoundManager();
    ~SoundManager();
    
    bool initialize();
    void cleanup();
    
    bool loadSound(const std::string& name, const std::string& filename);
    void playSound(const std::string& name);
    
    bool loadMusic(const std::string& filename);
    void playMusic(bool loop = true);
    void stopMusic();
    
    void setVolume(int volume);
    void setSoundEnabled(bool enabled);
    bool isSoundEnabled() const;
};
