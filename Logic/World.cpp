//
// Created by PPetre on 26/11/2025.
//

#include "World.h"

using namespace logic;


World::World(const std::shared_ptr<AbstractFactory> &factory) : factory(factory) {}


double World::normalizeX(const int value) const {
    return (static_cast<double>(value) / mapWidth) * 2 - 1;
}

double World::normalizeY(const int value) const {
    return (static_cast<double>(value) / mapHeight) * 2 - 1;
}


void World::loadLevel(const std::string &filename) {

}

void World::update(const double dt) {
    for (auto& entity: entities) {
        entity->update(dt);
    }
}

void World::handleMove(const Moves &move) {

}
