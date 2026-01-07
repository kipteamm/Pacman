#include <stdexcept>

#include "AssetManager.h"


AssetManager::AssetManager() {
    if (!font.loadFromFile("../Representation/assets/font.otf"))
        throw std::runtime_error("Could not load 'Representation/assets/font.otf' asset");

    if (!pacmanLogo.loadFromFile("../Representation/assets/pacman_logo.png"))
        throw std::runtime_error("Could not load 'Representation/assets/pacman_logo.png' asset");

    if (!spriteSheet.loadFromFile("../Representation/assets/sprite_sheet.png"))
        throw std::runtime_error("Could not load 'Representation/assets/sprite_sheet.png' asset");

    if (!easterEgg.loadFromFile("../Representation/assets/easteregg.png"))
        throw std::runtime_error("Could not load 'Representation/assets/easteregg.png' asset");
}

AssetManager& AssetManager::getInstance() {
    // The instance is created the first time this function is called.
    // It is destroyed automatically when the program exits.
    static AssetManager instance;
    return instance;
}


sf::Font &AssetManager::getFont() {
    return font;
}


sf::Texture &AssetManager::getPacmanLogo() {
    return pacmanLogo;
}

sf::Texture &AssetManager::getSpriteSheet() {
    if (easterEggToggle) return easterEgg;
    return spriteSheet;
}


void AssetManager::toggleEasterEgg(const bool toggle) {
    easterEggToggle = toggle;
}


sf::SoundBuffer& AssetManager::getSoundBuffer(const std::string& name) {
    if (soundBuffers.count(name)) return soundBuffers[name];

    sf::SoundBuffer& buffer = soundBuffers[name];
    if (!buffer.loadFromFile("../Representation/sounds/eduard/" + name)) throw std::runtime_error("Failed to load sound: " + name);

    return buffer;
}
