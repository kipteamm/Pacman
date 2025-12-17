//
// Created by toroe on 17/12/2025.
//

#include "../Logic/Random.h"
#include "SoundManager.h"
#include "AssetManager.h"


SoundManager::SoundManager() {
    loadSound(eatingCoinSound, "eatingCoins.flac");
}


void SoundManager::update(const logic::Events event) {
    switch (event) {
        case logic::Events::COIN_EATEN:
            eatingCoinSound.play(); break;

        default: return;
    }
}


void SoundManager::loadSound(sf::Sound& sound, const std::string& name) {
    sound.setBuffer(AssetManager::getInstance().getSoundBuffer(name));
}
