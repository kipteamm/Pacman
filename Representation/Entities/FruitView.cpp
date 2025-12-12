//
// Created by PPetre on 12/12/2025.
//

#include "../AssetManager.h"
#include "FruitView.h"


FruitView::FruitView(const std::shared_ptr<logic::FruitModel> &model, const std::shared_ptr<Camera> &camera) : EntityView(model, camera, 0) {
    sprite.setTexture(AssetManager::getInstance().getSpriteSheet());
    sprite.setTextureRect(sf::IntRect(sf::IntRect(6 * 16, 16, 16, 16)));
}


void FruitView::update(const logic::Events event) {
    switch (event) {
        case logic::Events::FRUIT_EATEN:
            this->markedForDeletion = true;
            break;

        default: break;
    }
}