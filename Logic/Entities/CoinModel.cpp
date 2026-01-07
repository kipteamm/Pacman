#include "CoinModel.h"

using namespace logic;


CoinModel::CoinModel(const float normalizedX, const float normalizedY): CollectibleEntityModel(normalizedX, normalizedY) {}


Events CoinModel::collect() {
    notify(Events::COIN_EATEN);

    return Events::COIN_EATEN;
}
