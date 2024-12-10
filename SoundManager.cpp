#include "SoundManager.h"

void SoundManager::Start() {
    if (instance) {
        return;
    }
    instance = new SoundManager();
};

SoundManager::SoundManager() {
    hitBuffer.loadFromFile("./assets/hit.ogg");
    playerHitSound = sf::Sound(hitBuffer);
};

SoundManager* SoundManager::instance = nullptr;

void SoundManager::Stop() {
    delete instance;
};

SoundManager::~SoundManager() = default;

SoundManager& SoundManager::GetInstance() {
    return *instance;
};
