#include "../AssetManager.h"
#include "PacmanView.h"
#include "../Window.h"


PacmanView::PacmanView(const std::shared_ptr<logic::PacmanModel> &model, const std::shared_ptr<Camera> &camera) : EntityView(model, camera), pacman(model) {
    sprite.setTexture(AssetManager::getInstance().getSpriteSheet());
    sprite.setTextureRect(sf::IntRect(sf::IntRect(16, 0, 16, 16)));
    sprite.setOrigin(8, 8);

    directionSprite.setTexture(AssetManager::getInstance().getSpriteSheet());
    directionSprite.setOrigin(8, 8);
}


void PacmanView::render() {
    float x = camera->xToPixel(model->getX());
    float y = camera->yToPixel(model->getY());
    sprite.setPosition(x, y);

    const float scaleX = camera->getTileWidth() / 16.0f;
    const float scaleY = camera->getTileHeight() / 16.0f;
    sprite.setScale(scaleX, scaleY);

    Window::getInstance().draw(sprite);

    // OBSERVER!!! VERPlAATS DIT!!!
    switch (pacman->getNextDirection()) {
        case logic::Moves::UP:
            directionSprite.setTextureRect(sf::IntRect(sf::IntRect(14 * 16, 2 * 16, 16, 16)));
            y -= camera->getTileWidth();
            break;

        case logic::Moves::DOWN:
            directionSprite.setTextureRect(sf::IntRect(sf::IntRect(14 * 16, 3 * 16, 16, 16)));
            y += camera->getTileWidth();
            break;

        case logic::Moves::LEFT:
            directionSprite.setTextureRect(sf::IntRect(sf::IntRect(14 * 16, 4 * 16, 16, 16)));
            x -= camera->getTileWidth();
            break;

        case logic::Moves::RIGHT:
            directionSprite.setTextureRect(sf::IntRect(sf::IntRect(14 * 16, 5 * 16, 16, 16)));
            x += camera->getTileWidth();
            break;

        default: return;
    }

    directionSprite.setPosition(x, y);
    directionSprite.setScale(scaleX, scaleY);

    Window::getInstance().draw(directionSprite);
}
