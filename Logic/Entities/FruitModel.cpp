//
// Created by PPetre on 12/12/2025.
//

#include "FruitModel.h"

using namespace logic;


FruitModel::FruitModel(const float normalizedX, const float normalizedY) : CollectibleEntityModel(normalizedX, normalizedY) {}


Events FruitModel::collect() {
    notify(Events::FRUIT_EATEN);

    return Events::FRUIT_EATEN;
}
