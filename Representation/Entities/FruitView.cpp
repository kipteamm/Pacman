#include "../AssetManager.h"
#include "FruitView.h"

#include "../../Logic/Difficulty.h"


FruitView::FruitView(const std::shared_ptr<logic::FruitModel> &model) : EntityView(model, 0) {
    sprite.setTexture(AssetManager::getInstance().getSpriteSheet());

    // The fruit sprite differs per difficulty. The logic::Difficulty class
    // gives access to the necessary sprite offset information
    sprite.setTextureRect(sf::IntRect(
        (6 + logic::Difficulty::getInstance().getFruitSpriteOffset()) * 16,
        16,
        16,
        16
    ));
}


void FruitView::update(const logic::Events event) {
    switch (event) {
        case logic::Events::FRUIT_EATEN:
            this->markedForDeletion = true;
            break;

        default: break;
    }
}