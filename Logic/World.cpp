#include "World.h"
#include <fstream>
#include <iostream>

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

    this->mapWidth = static_cast<float>(map[0].size());
    this->mapHeight = static_cast<float>(map.size());
    this->tileWidth = 2 / mapWidth;
    this->tileHeight = 2 / mapHeight;

    for (int row = 0; row < mapHeight; row++) {
        for (int col = 0; col < mapWidth; col++) {
            const char tile = map[row][col];
            if (tile == ' ') continue;

            const float x = normalizeX(col);
            const float y = normalizeY(row);

            switch (tile) {
                case 'P':
                    pacman = factory->createPacMan(x, y, mapWidth, mapHeight); break;
                case 'C':
                    interactables.push_back(factory->createCoin(x, y)); break;
                case 't':
                case 'b':
                case 'l':
                case 'r':
                case 'm':
                case 'e':
                case 'f':
                case 'h':
                case 'j':
                case 'k':
                case 'u':
                case 'i':
                case 'o':
                case 'p':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                    walls.push_back(factory->createWall(x, y, tile)); break;

                default: throw std::runtime_error("Unsupported tile '" + std::string(1, tile) + "' in level '" + filename + "'");
            }
        }
    }
}

void World::update(const double dt) {
    pacman->move(*this, dt);

    // for (auto& entity: entities) {
    //     entity->update(dt);
    // }
}

void World::handleMove(const Moves &move) const {
    pacman->setNextDirection(move);
}


bool World::collides(const Moves& direction, const float distance, float &x, float &y) const {
    switch(direction) {
        case Moves::LEFT: x -= distance; break;
        case Moves::RIGHT: x += distance; break;
        case Moves::UP: y -= distance; break;
        case Moves::DOWN: y += distance; break;
    }

    for (const std::shared_ptr<WallModel>& wall : walls) {
        const float wallX = wall->getX();
        const float wallY = wall->getY();
        
        if (std::abs(x - wallX) < tileWidth / 2.0f && std::abs(y - wallY) < tileHeight / 2.0f) return true;
    }

    return false;
}