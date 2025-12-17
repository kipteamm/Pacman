//
// Created by PPetre on 26/11/2025.
//

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

    [[nodiscard]] static AssetManager& getInstance();

    [[nodiscard]] sf::Font& getFont();

    [[nodiscard]] sf::Texture& getPacmanLogo();
    [[nodiscard]] sf::Texture& getSpriteSheet();

    [[nodiscard]] sf::SoundBuffer& getSoundBuffer(const std::string& name);

private:
    AssetManager();

    sf::Font font;

    sf::Texture pacmanLogo;
    sf::Texture spriteSheet;

    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
};



#endif //ASSETMANAGER_H
