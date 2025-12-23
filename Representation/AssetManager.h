#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>


class AssetManager {
public:
    /**
     * Singletons should not be cloneable or assignable.
     */
    AssetManager(AssetManager &other) = delete;
    void operator=(const AssetManager &) = delete;

    /**
     * @brief Returns an instance of the AssetManager class
     *
     * @return AssetManager instance
     */
    [[nodiscard]] static AssetManager& getInstance();


    /**
     * @brief Returns the font used throughout the project.
     *
     * @return sf::Font
     */
    [[nodiscard]] sf::Font& getFont();


    /**
     * @brief Returns the Pacman logo.
     *
     * @return Pacman logo
     */
    [[nodiscard]] sf::Texture& getPacmanLogo();

    /**
     * @brief Returns the Spritesheet.
     *
     * @return Spritesheet
     */
    [[nodiscard]] sf::Texture& getSpriteSheet();


    /**
     * @brief Returns the sf::SoundBuffer of the file with the provided name.
     *
     * Will return a cached sf::SoundBuffer if this exists, otherwise it will load
     * and extract it from the file (save it to a cache) and return.
     *
     * @param name Sound file name.
     * @return sf::SoundBuffer
     */
    [[nodiscard]] sf::SoundBuffer& getSoundBuffer(const std::string& name);

private:
    AssetManager();

    sf::Font font;

    sf::Texture pacmanLogo;
    sf::Texture spriteSheet;

    // Cache of sf::SoundBuffers by filename.
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
};



#endif //ASSETMANAGER_H
