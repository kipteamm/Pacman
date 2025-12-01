//
// Created by PPetre on 27/11/2025.
//

#include "../AssetManager.h"
#include "PacmanView.h"
#include "../Window.h"


PacmanView::PacmanView(const std::shared_ptr<logic::PacmanModel> &model, const std::shared_ptr<Camera> &camera) : EntityView(model, camera), pacman(model) {
    sprite.setTexture(AssetManager::getInstance().getSpriteSheet());
    sprite.setTextureRect(sf::IntRect(sf::IntRect(0, 0, 16, 16)));

    directionSprite.setTexture(AssetManager::getInstance().getSpriteSheet());
}


void PacmanView::render() {
    sprite.setOrigin(8.0f, 8.0f);

    const float x = camera->xToPixel(model->getX());
    const float y = camera->yToPixel(model->getY());
    sprite.setPosition(x, y);

    const float scaleX = camera->getTileWidth() / 16.0f;
    const float scaleY = camera->getTileHeight() / 16.0f;
    sprite.setScale(scaleX, scaleY);

    Window::getInstance().draw(sprite);

    switch (pacman->getNextDirection()) {
        case logic::Moves::UP:
            sprite.setTextureRect(sf::IntRect(sf::IntRect(0, 0, 16, 16)));
            break;

        case logic::Moves::DOWN:
            sprite.setTextureRect(sf::IntRect(sf::IntRect(0, 0, 16, 16)));
            break;

        case logic::Moves::LEFT:
            sprite.setTextureRect(sf::IntRect(sf::IntRect(0, 0, 16, 16)));
            break;

        case logic::Moves::RIGHT:
            sprite.setTextureRect(sf::IntRect(sf::IntRect(0, 0, 16, 16)));
            break;

        default: return;
    }

    directionSprite.setPosition(x, y);
    directionSprite.setScale(scaleX, scaleY);

    Window::getInstance().draw(directionSprite);
}
