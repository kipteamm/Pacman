//
// Created by toroe on 09/12/2025.
//

#include "GhostModel.h"

using namespace logic;


GhostModel::GhostModel(const float normalizedX, const float normalizedY, const float mapWidth, const float mapHeight, const float speed, const GhostType type) : MovingEntityModel(normalizedX, normalizedY, mapWidth, mapHeight, speed), type(type) {
    if (type == GhostType::BLINKY || type == GhostType::PINKY) {
        this->state = GhostState::CHASING;
    } else {
        this->state = GhostState::WAITING;
    }
}


void GhostModel::move(const World& world, float dt) {
    if (this->state == GhostState::WAITING) return;
}

