//
// Created by toroe on 09/12/2025.
//

#include "../AssetManager.h"
#include "../Window.h"
#include "GhostView.h"


GhostView::GhostView(const std::shared_ptr<logic::GhostModel>& model, const std::shared_ptr<Camera>& camera, const char type) : EntityView(model, camera) {
    switch (type) {
        case 'R':
            spriteY = 32;
            break;
        case 'P':
            spriteY = 48;
            break;
        case 'C':
            spriteY = 64;
            break;
        case 'O':
            spriteY = 80;
            break;
        default: throw std::runtime_error("Invalid ghost type");
    }

    sprite.setTexture(AssetManager::getInstance().getSpriteSheet());
    sprite.setTextureRect({0, spriteY, 16, 16});
    sprite.setOrigin(8, 8);
}


void GhostView::render() {
    const float x = camera->xToPixel(model->getX());
    const float y = camera->yToPixel(model->getY());
    sprite.setPosition(x, y);

    const float scaleX = camera->getTileWidth() / 16.0f;
    const float scaleY = camera->getTileHeight() / 16.0f;
    sprite.setScale(scaleX, scaleY);

    Window::getInstance().draw(sprite);
}