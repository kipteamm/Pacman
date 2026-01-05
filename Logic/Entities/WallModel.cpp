#include "WallModel.h"

using namespace logic;


WallModel::WallModel(
    const float normalizedX,
    const float normalizedY,
    const bool isDoor
) : EntityModel(normalizedX, normalizedY), door(isDoor) {}
