//
// Created by toroe on 09/12/2025.
//

#include "../../Logic/Stopwatch.h"
#include "../AssetManager.h"
#include "../Window.h"
#include "../Camera.h"
#include "GhostView.h"


GhostView::GhostView(const std::shared_ptr<logic::GhostModel>& model, const int spriteY) : EntityView(model, 0.16), ghost(model) {
    // Up animation
    animations[logic::Moves::UP] = {
        sf::IntRect{64, spriteY, 16, 16},
        sf::IntRect{80, spriteY, 16, 16},
    };

    // Down animation
    animations[logic::Moves::DOWN] = {
        sf::IntRect{96, spriteY, 16, 16},
        sf::IntRect{112, spriteY, 16, 16},
    };

    // Right animation
    animations[logic::Moves::RIGHT] = {
        sf::IntRect{0, spriteY, 16, 16},
        sf::IntRect{16, spriteY, 16, 16},
    };

    // Left animation
    animations[logic::Moves::LEFT] = {
        sf::IntRect{32, spriteY, 16, 16},
        sf::IntRect{48, spriteY, 16, 16},
    };

    // (Eyes) Up animation
    animations[logic::Moves::UP + 4] = {
        sf::IntRect{160, 48, 16, 16},
    };

    // (Eyes) Down animation
    animations[logic::Moves::DOWN + 4] = {
        sf::IntRect{176, 48, 16, 16},
    };

    // (Eyes) Right animation
    animations[logic::Moves::RIGHT + 4] = {
        sf::IntRect{128, 48, 16, 16},
    };

    // (Eyes) Left animation
    animations[logic::Moves::LEFT + 4] = {
        sf::IntRect{144, 48, 16, 16},
    };

    // Frightened animation
    animations[8] = {
        sf::IntRect{128, 32, 16, 16},
        sf::IntRect{144, 32, 16, 16},
    };

    // Frightened flashes
    animations[9] = {
        sf::IntRect{160, 32, 16, 16},
        sf::IntRect{176, 32, 16, 16},
        sf::IntRect{128, 32, 16, 16},
        sf::IntRect{144, 32, 16, 16},
    };

    animation = &animations[ghost->getDirection()];
    sprite.setTexture(AssetManager::getInstance().getSpriteSheet());
    sprite.setOrigin(8, 8);
}


void GhostView::update(const logic::Events event) {
    switch (event) {
        case logic::Events::DIRECTION_CHANGED:
            if (frightened) return;
            animation = &animations[ghost->getDirection() + animationOffset]; break;

        case logic::Events::GHOST_FRIGHTENED:
            frightened = true;
            animation = &animations[8]; break;

        case logic::Events::GHOST_EATEN:
            frightened = false;
            animationOffset = 4;
            animation = &animations[ghost->getDirection() + animationOffset]; break;

        case logic::Events::GHOST_NORMAL:
        case logic::Events::RESPAWN:
            frameDuration = 0.16;
            animationOffset = 0;
            animation = &animations[ghost->getDirection()]; break;

        case logic::Events::FRIGHTENED_FLASHING:
            if (!frightened) return;

            animation = &animations[9];
            frameDuration = 0.1; break;

        default: break;
    }
}


void GhostView::render() {
    const float x = Camera::getInstance().xToPixel(model->getX());
    const float y = Camera::getInstance().yToPixel(model->getY());
    sprite.setPosition(x, y);

    const float scaleX = Camera::getInstance().getTileWidth() / 16.0f;
    const float scaleY = Camera::getInstance().getTileHeight() / 16.0f;
    sprite.setScale(scaleX, scaleY);

    const double dt = logic::Stopwatch::getInstance().getDeltaTime();
    const sf::IntRect rect = animation->at(getFrameIndex(static_cast<float>(dt), animation->size()));
    sprite.setTextureRect(rect);

    Window::getInstance().draw(sprite);
}

