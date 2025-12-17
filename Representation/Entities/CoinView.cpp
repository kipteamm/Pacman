//
// Created by toroe on 28/11/2025.
//

#include "../AssetManager.h"
#include "CoinView.h"

CoinView::CoinView(const std::shared_ptr<logic::CoinModel> &model) : EntityView(model, 0) {
    sprite.setTexture(AssetManager::getInstance().getSpriteSheet());
    sprite.setTextureRect(sf::IntRect(sf::IntRect(14 * 16, 16, 16, 16)));
}


void CoinView::update(const logic::Events event) {
    switch (event) {
        case logic::Events::COIN_EATEN:
            this->markedForDeletion = true;
            break;

        default: break;
    }
}
