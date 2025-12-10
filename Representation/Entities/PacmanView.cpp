#include "../../Logic/Stopwatch.h"
#include "../AssetManager.h"
#include "PacmanView.h"
#include "../Window.h"


PacmanView::PacmanView(const std::shared_ptr<logic::PacmanModel> &model, const std::shared_ptr<Camera> &camera) : EntityView(model, camera), pacman(model) {
    sprite.setTexture(AssetManager::getInstance().getSpriteSheet());

    // Up animation
    animations[logic::Moves::UP] = {
        sf::IntRect{32, 16, 16, 16},
        sf::IntRect{48, 16, 16, 16},
        sf::IntRect{32, 0, 16, 16},
        sf::IntRect{48, 16, 16, 16},
    };

    // Down animation
    animations[logic::Moves::DOWN] = {
        sf::IntRect{64, 16, 16, 16},
        sf::IntRect{80, 16, 16, 16},
        sf::IntRect{32, 0, 16, 16},
        sf::IntRect{80, 16, 16, 16},
    };

    // Right animation
    animations[logic::Moves::RIGHT] = {
        sf::IntRect{0, 0, 16, 16},
        sf::IntRect{16, 0, 16, 16},
        sf::IntRect{32, 0, 16, 16},
        sf::IntRect{16, 0, 16, 16},
    };

    // Left animation
    animations[logic::Moves::LEFT] = {
        sf::IntRect{0, 16, 16, 16},
        sf::IntRect{16, 16, 16, 16},
        sf::IntRect{32, 0, 16, 16},
        sf::IntRect{16, 16, 16, 16},
    };

    animation = &animations[pacman->getDirection()];
    sprite.setOrigin(8, 8);

    directionSprite.setTexture(AssetManager::getInstance().getSpriteSheet());
    directionSprite.setOrigin(8, 8);
}


void PacmanView::update(const logic::Events event) {
    switch (event) {
        case logic::Events::DIRECTION_CHANGED:
            animation = &animations[pacman->getDirection()]; break;
        case logic::Events::ISMOVING_CHANGED:
            moving = pacman->isMoving(); break;

        default: break;
    }
}


void PacmanView::render() {
    if (!moving) {
        Window::getInstance().draw(sprite);
        return;
    }

    float x = camera->xToPixel(model->getX());
    float y = camera->yToPixel(model->getY());
    sprite.setPosition(x, y);

    const float scaleX = camera->getTileWidth() / 16.0f;
    const float scaleY = camera->getTileHeight() / 16.0f;
    sprite.setScale(scaleX, scaleY);

    const double dt = logic::Stopwatch::getInstance().getDeltaTime();
    const sf::IntRect rect = animation->at(getFrameIndex(static_cast<float>(dt), animation->size()));
    sprite.setTextureRect(rect);

    Window::getInstance().draw(sprite);

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
