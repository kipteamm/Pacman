//
// Created by toroe on 28/11/2025.
//

#include "../AssetManager.h"
#include "CoinView.h"

CoinView::CoinView(const std::shared_ptr<logic::CoinModel> &model, const std::shared_ptr<Camera> &camera) : EntityView(model, camera, 0) {
    sprite.setTexture(AssetManager::getInstance().getSpriteSheet());
    sprite.setTextureRect(sf::IntRect(sf::IntRect(14 * 16, 16, 16, 16)));
}