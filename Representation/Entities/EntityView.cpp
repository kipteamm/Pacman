//
// Created by PPetre on 26/11/2025.
//

#include "EntityView.h"
#include "../Camera.h"
#include "../Window.h"

EntityView::EntityView(const std::shared_ptr<logic::EntityModel> &model, const float frameDuration) : model(model), frameDuration(frameDuration) {
    sprite.setOrigin(8.0f, 8.0f);
}


void EntityView::resized() {
    const float scaleX = Camera::getInstance().getTileWidth() / 16.0f;
    const float scaleY = Camera::getInstance().getTileHeight() / 16.0f;
    sprite.setScale(scaleX, scaleY);
}


void EntityView::render() {
    const float x = Camera::getInstance().xToPixel(model->getX());
    const float y = Camera::getInstance().yToPixel(model->getY());
    sprite.setPosition(x, y);

    Window::getInstance().draw(sprite);
}


bool EntityView::shouldDelete() const {
    return this->markedForDeletion;
}

size_t EntityView::getFrameIndex(const float dt, const size_t max) {
    if (frameIndex >= max) frameIndex = 0;
    elapsedTime += dt;

    if (elapsedTime > frameDuration) {
        elapsedTime -= frameDuration;
        frameIndex = (frameIndex + 1) % max;
    }

    return frameIndex;
}
