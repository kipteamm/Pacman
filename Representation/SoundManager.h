//
// Created by toroe on 17/12/2025.
//

#ifndef PACMAN_SOUNDMANAGER_H
#define PACMAN_SOUNDMANAGER_H

#include <SFML/Audio/Sound.hpp>
#include "../Logic/Observer.h"


class SoundManager final : public logic::Observer {
public:
    SoundManager();

    void update(logic::Events event) override;

private:
    sf::Sound eatingCoinSound;
    //sf::Sound ghostEatenSound;
    //sf::Sound deathSound;

    void loadSound(sf::Sound& sound, const std::string& name);
};


#endif //PACMAN_SOUNDMANAGER_H