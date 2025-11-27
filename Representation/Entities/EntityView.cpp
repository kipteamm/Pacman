//
// Created by PPetre on 26/11/2025.
//

#include "EntityView.h"
#include "../Window.h"

EntityView::EntityView(const std::shared_ptr<logic::EntityModel> &model, const std::shared_ptr<Camera>& camera) : model(model), camera(camera) {}


void EntityView::render() {
    sprite.setOrigin(8.0f, 8.0f);

    const float x = camera->xToPixel(model->getX());
    const float y = camera->yToPixel(model->getY());
    sprite.setPosition(x, y);

    const float scaleX = camera->getTileWidth() / 16.0f;
    const float scaleY = camera->getTileHeight() / 16.0f;
    sprite.setScale(scaleX, scaleY);

    Window::getInstance().draw(sprite);
}