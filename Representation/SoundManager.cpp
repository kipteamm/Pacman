//
// Created by toroe on 17/12/2025.
//

#include "../Logic/Random.h"
#include "SoundManager.h"
#include "AssetManager.h"


SoundManager::SoundManager() {
    for (int i = 0; i < 4; ++i) {
        sf::Sound s;
        loadSound(s, "eatingCoin.flac");
        coinSoundPool.push_back(s);
    }

    for (int i = 0; i < 4; ++i) {
        sf::Sound s;
        loadSound(s, "eatingGhost.flac");
        ghostSoundPool.push_back(s);
    }

    loadSound(deathSound, "pacmanDeath.flac");

    loadSound(ghostMove, "ghostMove.flac");
    ghostMove.setLoop(true);
    ghostMove.play();

    loadSound(ghostFright, "ghostFright.flac");
    ghostFright.setLoop(true);
}


void SoundManager::update(const logic::Events event) {
    switch (event) {
        case logic::Events::COIN_EATEN: {
            sf::Sound* sound = nullptr;

            for (auto& s : coinSoundPool) {
                if (s.getStatus() == sf::Sound::Status::Playing) continue;
                sound = &s;
                break;
            }

            if (!sound) sound = &coinSoundPool[0];
            sound->play(); break;
        }

        case logic::Events::GHOST_EATEN: {
            sf::Sound* sound = nullptr;

            for (auto& s : coinSoundPool) {
                s.stop();
            }

            for (auto& s : ghostSoundPool) {
                if (s.getStatus() == sf::Sound::Status::Playing) continue;
                sound = &s;
                break;
            }

            if (!sound) sound = &ghostSoundPool[0];
            sound->play(); break;
        }

        case logic::Events::GHOST_FRIGHTENED:
            ghostMove.stop();
            ghostFright.play(); break;

        case logic::Events::GHOST_NORMAL:
        case logic::Events::RESPAWN:
            ghostFright.stop();
            ghostMove.play(); break;

        case logic::Events::DEATH:
            ghostMove.stop();
            ghostFright.stop();
            deathSound.play(); break;

        default: return;
    }
}


void SoundManager::loadSound(sf::Sound& sound, const std::string& name) {
    sound.setBuffer(AssetManager::getInstance().getSoundBuffer(name));
}
