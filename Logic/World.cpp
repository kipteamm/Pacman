//
// Created by PPetre on 26/11/2025.
//

#include "World.h"

#include <fstream>

using namespace logic;


World::World(const std::shared_ptr<AbstractFactory> &factory) : factory(factory) {}


float World::normalizeX(const int value) const {
    return (static_cast<float>(value) + 0.5f) / mapWidth * 2.0f - 1.0f;
}

float World::normalizeY(const int value) const {
    return (static_cast<float>(value) + 0.5f) / mapHeight * 2.0f - 1.0f;
}

float World::getWidth() const {
    return mapWidth;
}

float World::getHeight() const {
    return mapHeight;
}


void World::loadLevel(const std::string &filename) {
    std::fstream fileStream(filename);
    if (!fileStream.is_open()) throw std::runtime_error("File '" + filename + "' not found.");

    std::vector<std::string> map;
    std::string line;
    while (std::getline(fileStream, line)) {
        map.push_back(line);
    }

    this->mapHeight = static_cast<float>(map.size());
    this->mapWidth = static_cast<float>(map[0].size());

    for (int row = 0; row < mapHeight; row++) {
        for (int col = 0; col < mapWidth; col++) {
            const char tile = map[row][col];
            if (tile == ' ') continue;





            if (tile == 'C') continue;


            const float x = normalizeX(col);
            const float y = normalizeY(row);

            std::shared_ptr<EntityModel> entity;

            switch (tile) {
                case 'P':
                    entity = factory->createPacMan(x, y); break;
                case 't':
                case 'b':
                case 'l':
                case 'r':
                case '1':
                case '2':
                case '3':
                case '4':
                    entity = factory->createWall(x, y, tile); break;

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
