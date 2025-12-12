//
// Created by PPetre on 12/12/2025.
//

#include "FruitModel.h"

using namespace logic;


FruitModel::FruitModel(const float normalizedX, const float normalizedY, const unsigned int score) : CollectibleEntityModel(normalizedX, normalizedY), score(score) {}


Events FruitModel::collect() {
    notify(Events::FRUIT_EATEN);

    return Events::FRUIT_EATEN;
}
