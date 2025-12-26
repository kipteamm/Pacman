#ifndef PACMAN_SOUNDMANAGER_H
#define PACMAN_SOUNDMANAGER_H

#include <SFML/Audio/Sound.hpp>
#include <vector>

#include "../Logic/Observer.h"


class SoundManager final : public logic::Observer {
public:
    SoundManager();

    /**
     * @brief Starts the sounds for a new game.
     */
    void start();

    /**
     * @brief Stops all the sounds.
     */
    void stop();


    /**
     * @brief Starts playing sounds depending on the event.
     *
     * @param event logic::Event
     */
    void update(logic::Events event) override;

private:
    std::vector<sf::Sound> coinSoundPool;
    std::vector<sf::Sound> ghostSoundPool;

    sf::Sound ghostMove;
    sf::Sound ghostFrightened;
    sf::Sound eatingFruit;
    sf::Sound deathSound;

    /**
     * @brief Update a sf::Sound SoundBuffer object to hold the contents of the
     * provided flac file.
     *
     * The SoundBuffer is retrieved from the AssetManager.
     *
     * @param sound Sound used by the SoundManager.
     * @param name Filename of the sound.
     */
    static void loadSound(sf::Sound& sound, const std::string& name);
};


#endif //PACMAN_SOUNDMANAGER_H