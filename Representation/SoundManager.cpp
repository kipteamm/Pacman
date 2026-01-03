#include "SoundManager.h"
#include "AssetManager.h"


SoundManager::SoundManager() {
    // I use SoundPools to hold multiple instances of the same sound to overlay
    // them when the same event occurs in short notice, assuring that no sounds
    // get cut off (as that sounds wrong)
    for (int i = 0; i < 4; ++i) {
        sf::Sound s;

        loadSound(s, "eatingCoin.flac");
        // I experimented with changing their individual volumes to make it a
        // bit more interesting, but the results are minimal because you rarely
        // get to the last sounds in the pool.
        s.setVolume(40 + i * 5);

        coinSoundPool.push_back(s);
    }

    // Same as with the coin SoundPool.
    for (int i = 0; i < 4; ++i) {
        sf::Sound s;
        loadSound(s, "eatingGhost.flac");
        ghostSoundPool.push_back(s);
    }

    loadSound(eatingFruit, "eatingFruit.flac");
    loadSound(deathSound, "pacmanDeath.flac");

    // Both the ghostMove and ghostFreightened sounds are looped because they
    // do not stop unless the level is completed, or the state switches.
    // (When ghosts are freigthened the playing sound switches from ghostMove
    // to ghostFrieghtened and vica versa)
    loadSound(ghostMove, "ghostMove.flac");
    ghostMove.setLoop(true);

    loadSound(ghostFrightened, "ghostFrightened.flac");
    ghostFrightened.setLoop(true);
}


void SoundManager::start() {
    ghostMove.play();
}

void SoundManager::stop() {
    ghostFrightened.stop();
    ghostMove.stop();
}


void SoundManager::loadSound(sf::Sound& sound, const std::string& name) {
    sound.setBuffer(AssetManager::getInstance().getSoundBuffer(name));
}


void SoundManager::update(const logic::Events event) {
    switch (event) {
        case logic::Events::COIN_EATEN: {
            sf::Sound* sound = nullptr;

            // Find the first sound in the SoundPool that is not currently
            // playing.
            for (auto& s : coinSoundPool) {
                if (s.getStatus() == sf::Sound::Status::Playing) continue;
                sound = &s;
                break;
            }

            // If no sound is found, the first sound will be used as that will
            // be the one nearest to finishing. The likelyhoods if this
            // happening however are very small.
            if (!sound) sound = &coinSoundPool[0];
            sound->play(); break;
        }

        case logic::Events::GHOST_EATEN: {
            sf::Sound* sound = nullptr;

            // Stop any coin eating sounds to put emphasize on ghost eating.
            for (auto& s : coinSoundPool) {
                s.stop();
            }

            // Find the first sound in the SoundPool that is not currently
            // playing.
            for (auto& s : ghostSoundPool) {
                if (s.getStatus() == sf::Sound::Status::Playing) continue;
                sound = &s;
                break;
            }

            // If no sound is found, the first sound will be used as that will
            // be the one nearest to finishing.
            if (!sound) sound = &ghostSoundPool[0];
            sound->play(); break;
        }

        case logic::Events::FRUIT_EATEN:
            eatingFruit.play(); break;

        case logic::Events::GHOST_FRIGHTENED:
            ghostMove.stop();
            ghostFrightened.play(); break;

        case logic::Events::GHOST_NORMAL:
        case logic::Events::RESPAWN:
            ghostFrightened.stop();
            ghostMove.play(); break;

        case logic::Events::DEATH:
            ghostMove.stop();
            ghostFrightened.stop();
            deathSound.play(); break;

        default: return;
    }
}
