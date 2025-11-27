//
// Created by PPetre on 26/11/2025.
//

#include "World.h"

#include <fstream>

using namespace logic;


World::World(const std::shared_ptr<AbstractFactory> &factory) : factory(factory) {}


double World::normalizeX(const int value) const {
    return (static_cast<double>(value) / mapWidth) * 2 - 1;
}

double World::normalizeY(const int value) const {
    return (static_cast<double>(value) / mapHeight) * 2 - 1;
}


void World::loadLevel(const std::string &filename) {
    std::fstream fileStream(filename);
    if (!fileStream.is_open()) throw std::runtime_error("File '" + filename + "' not found.");

    std::vector<std::string> map;
    std::string line;
    while (std::getline(fileStream, line)) {
        map.push_back(line);
    }

    this->mapHeight = map.size();
    this->mapWidth = map[0].size();

    for (int row = 0; row < mapHeight; row++) {
        for (int col = 0; col < mapWidth; col++) {
            const char tile = map[row][col];

            // Add 0.5 to center the tile
            const double x = normalizeX(col + 0.5);
            const double y = normalizeY(row + 0.5);

            std::shared_ptr<EntityModel> entity;

            switch (tile) {
                case 'P':
                    entity = factory->createPacMan(x, y); break;

                default: throw std::runtime_error("Unsupported tile '" + std::string(1, tile) + "' in level '" + filename + "'");
            }

            entities.push_back(entity);
        }
    }
}

void World::update(const double dt) {
    for (auto& entity: entities) {
        entity->update(dt);
    }
}

void World::handleMove(const Moves &move) {

}
