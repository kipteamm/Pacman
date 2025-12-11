#include "World.h"
#include <fstream>
#include <iostream>

using namespace logic;


World::World(const std::shared_ptr<AbstractFactory> &factory) : ghostExitX(0), ghostExitY(0), factory(factory) {}


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

int World::getGhostExitX() const {
    return ghostExitX;
}

int World::getGhostExitY() const {
    return ghostExitY;
}

std::shared_ptr<PacmanModel> World::getPacman() const {
    return this->pacman;
}

bool World::collidesWithWall(const float x, const float y, const bool passDoor) const {
    for (const std::shared_ptr<WallModel>& wall : walls) {
        if (wall->isDoor() && passDoor) continue;

        const float wallX = wall->getX();
        const float wallY = wall->getY();

        if (std::abs(x - wallX) < tileWidth / 2.0f && std::abs(y - wallY) < tileHeight / 2.0f) return true;
    }

    return false;
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
                case '*':
                    pacman = factory->createPacMan(x, y, mapWidth, mapHeight); break;
                case '.':
                    collectibles.push_back(factory->createCoin(x, y)); break;
                case '#':
                    ghostExitX = col;
                    ghostExitY = row;
                    collectibles.push_back(factory->createCoin(x, y)); break;
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
                case 'd':
                    walls.push_back(factory->createWall(x, y, tile)); break;
                case 'B':
                    ghosts.push_back(factory->createBlinky(x, y, mapWidth, mapHeight)); break;
                case 'P':
                    ghosts.push_back(factory->createPinky(x, y, mapWidth, mapHeight)); break;
                case 'I':
                    ghosts.push_back(factory->createInky(x, y, mapWidth, mapHeight)); break;
                case 'C':
                    ghosts.push_back(factory->createClyde(x, y, mapWidth, mapHeight)); break;

                default: throw std::runtime_error("Unsupported tile '" + std::string(1, tile) + "' in level '" + filename + "'");
            }
        }
    }
}

void World::resetLevel() {
    pacman->respawn();

    for (const auto& ghost : ghosts) {
        ghost->respawn();
    }

    restarting = false;
    restartTime = 0;
}


void World::update(const double dt) {
    if (restarting) {
        restartTime += dt;

        if (restartTime >= DEATH_DURATION) resetLevel();
        return;
    }

    pacman->move(*this, dt);

    constexpr float epsilon = 0.1f;

    for (const auto& ghost : ghosts) {
        ghost->update(*this, dt);
        ghost->move(*this, dt);

        if (std::abs(pacman->getX() - ghost->getX()) > epsilon || std::abs(pacman->getY() - ghost->getY()) > epsilon) continue;
        lives--;

        restarting = true;
        pacman->notify(Events::DEATH);
    }
}

void World::handleMove(const Moves &move) const {
    pacman->setNextDirection(move);
}
