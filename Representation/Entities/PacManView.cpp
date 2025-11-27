//
// Created by PPetre on 27/11/2025.
//

#include "PacManView.h"

#include "../AssetManager.h"
#include "../Window.h"


PacManView::PacManView(const std::shared_ptr<logic::PacManModel> &model, const std::shared_ptr<Camera> &camera) : EntityView(model, camera) {
    sprite.setTexture(AssetManager::getInstance().getSpriteSheet());
    sprite.setTextureRect(sf::IntRect(sf::IntRect(0, 0, 16, 16)));
}


void PacManView::render() {
    const float x = camera->xToPixel(model->getX());
    const float y = camera->xToPixel(model->getY());

    sprite.setPosition(x, y);
    Window::getInstance().draw(sprite);
}


