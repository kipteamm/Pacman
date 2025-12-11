//
// Created by toroe on 09/12/2025.
//

#include "../../Logic/Stopwatch.h"
#include "../AssetManager.h"
#include "../Window.h"
#include "GhostView.h"


GhostView::GhostView(const std::shared_ptr<logic::GhostModel>& model, const std::shared_ptr<Camera>& camera, const int spriteY) : EntityView(model, camera), ghost(model) {
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

    animation = &animations[ghost->getDirection()];
    sprite.setTexture(AssetManager::getInstance().getSpriteSheet());
    sprite.setOrigin(8, 8);
}


void GhostView::update(const logic::Events event) {
    switch (event) {
        case logic::Events::DIRECTION_CHANGED:
            animation = &animations[ghost->getDirection()]; break;

        default: break;
    }
}


void GhostView::render() {
    const float x = camera->xToPixel(model->getX());
    const float y = camera->yToPixel(model->getY());
    sprite.setPosition(x, y);

    const float scaleX = camera->getTileWidth() / 16.0f;
    const float scaleY = camera->getTileHeight() / 16.0f;
    sprite.setScale(scaleX, scaleY);

    const double dt = logic::Stopwatch::getInstance().getDeltaTime();
    const sf::IntRect rect = animation->at(getFrameIndex(static_cast<float>(dt), animation->size()));
    sprite.setTextureRect(rect);

    sf::Text debug;
    debug.setFont(AssetManager::getInstance().getFont());

    switch (ghost->getState()) {
        case logic::GhostState::WAITING:
            debug.setString("WAITING"); break;
        case logic::GhostState::EXITING:
            debug.setString("EXITING"); break;
        case logic::GhostState::CHASING:
            debug.setString("CHASING"); break;
        case logic::GhostState::FRIGHTENED:
            debug.setString("FRIGHTENED"); break;
    }

    debug.setCharacterSize(16);
    debug.setFillColor(sf::Color::White);
    debug.setPosition(x - 50, y - 50);

    Window::getInstance().draw(sprite);
    Window::getInstance().draw(debug);
}