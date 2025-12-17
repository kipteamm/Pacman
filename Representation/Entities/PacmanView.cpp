#include "../../Logic/Stopwatch.h"
#include "../AssetManager.h"
#include "PacmanView.h"
#include "../Window.h"


PacmanView::PacmanView(const std::shared_ptr<logic::PacmanModel> &model) : EntityView(model, 0.08), pacman(model) {
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

    // DEATH animation
    animations[5] = {
        sf::IntRect{48, 0, 16, 16},
        sf::IntRect{64, 0, 16, 16},
        sf::IntRect{80, 0, 16, 16},
        sf::IntRect{96, 0, 16, 16},
        sf::IntRect{112, 0, 16, 16},
        sf::IntRect{128, 0, 16, 16},
        sf::IntRect{144, 0, 16, 16},
        sf::IntRect{160, 0, 16, 16},
        sf::IntRect{176, 0, 16, 16},
        sf::IntRect{192, 0, 16, 16},
        sf::IntRect{208, 0, 16, 16},
        sf::IntRect{208, 0, 16, 16},
        sf::IntRect{208, 0, 16, 16},
        sf::IntRect{112, 112, 16, 16},
        sf::IntRect{112, 112, 16, 16},
        sf::IntRect{112, 112, 16, 16},
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

        case logic::Events::RESPAWN:
            dying = false;
            moving = true;
            animation = &animations[pacman->getDirection()];

            frameIndex = 0;
            elapsedTime = 0;
            break;

        case logic::Events::DEATH:
            dying = true;
            animation = &animations[5];

            frameIndex = 0;
            elapsedTime = 0;
            break;

        case logic::Events::ISMOVING_CHANGED:
            moving = pacman->isMoving(); break;

        default: break;
    }
}


void PacmanView::render() {
    float x = Camera::getInstance().xToPixel(model->getX());
    float y = Camera::getInstance().yToPixel(model->getY());
    sprite.setPosition(x, y);

    switch (pacman->getNextDirection()) {
        case logic::Moves::UP:
            directionSprite.setTextureRect(sf::IntRect(sf::IntRect(14 * 16, 2 * 16, 16, 16)));
            y -= Camera::getInstance().getTileWidth();
            break;

        case logic::Moves::DOWN:
            directionSprite.setTextureRect(sf::IntRect(sf::IntRect(14 * 16, 3 * 16, 16, 16)));
            y += Camera::getInstance().getTileWidth();
            break;

        case logic::Moves::LEFT:
            directionSprite.setTextureRect(sf::IntRect(sf::IntRect(14 * 16, 4 * 16, 16, 16)));
            x -= Camera::getInstance().getTileWidth();
            break;

        case logic::Moves::RIGHT:
            directionSprite.setTextureRect(sf::IntRect(sf::IntRect(14 * 16, 5 * 16, 16, 16)));
            x += Camera::getInstance().getTileWidth();
            break;

        default: return;
    }

    directionSprite.setPosition(x, y);

    const float scaleX = Camera::getInstance().getTileWidth() / 16.0f;
    const float scaleY = Camera::getInstance().getTileHeight() / 16.0f;
    directionSprite.setScale(scaleX, scaleY);

    Window::getInstance().draw(directionSprite);

    if (!moving && !dying) {
        Window::getInstance().draw(sprite);
        return;
    }

    sprite.setScale(scaleX, scaleY);

    const double dt = logic::Stopwatch::getInstance().getDeltaTime();
    const sf::IntRect rect = animation->at(getFrameIndex(static_cast<float>(dt), animation->size()));
    sprite.setTextureRect(rect);

    Window::getInstance().draw(sprite);
}
