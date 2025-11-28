//
// Created by PPetre on 27/11/2025.
//

#include "../AssetManager.h"
#include "PacManView.h"


PacManView::PacManView(const std::shared_ptr<logic::PacManModel> &model, const std::shared_ptr<Camera> &camera) : EntityView(model, camera) {
    sprite.setTexture(AssetManager::getInstance().getSpriteSheet());
    sprite.setTextureRect(sf::IntRect(sf::IntRect(0, 0, 16, 16)));
}
