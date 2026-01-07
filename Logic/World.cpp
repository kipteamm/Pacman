#include "World.h"
#include <fstream>

using namespace logic;


World::World(const std::shared_ptr<AbstractFactory> &factory, const int lives)
    : ghostExitX(0), ghostExitY(0), state(WorldState::AWAITING_MAP), factory(factory), lives(lives) {
    Difficulty::getInstance().reset();
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

unsigned int World::getLives() const {
    return lives;
}


std::pair<float, float> World::getCollissionCoordinates() const {
    return collissionCoordinates;
}


float World::normalizeX(const int value) const {
    return (static_cast<float>(value) + 0.5f) / mapWidth * 2.0f - 1.0f;
}

float World::normalizeY(const int value) const {
    return (static_cast<float>(value) + 0.5f) / mapHeight * 2.0f - 1.0f;
}


bool World::isColliding(const EntityModel& a, const EntityModel& b) {
    return  std::abs(a.getX() - b.getX()) <= COLLISSION_EPSILON &&
            std::abs(a.getY() - b.getY()) <= COLLISSION_EPSILON;
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


void World::loadMap(const std::string &filename) {
    std::fstream fileStream(filename);
    if (!fileStream.is_open()) throw std::runtime_error("File '" + filename + "' not found.");

    std::vector<std::string> map;
    std::string line;
    while (std::getline(fileStream, line)) {
        map.push_back(line);
    }

    fileStream.close();

    this->mapWidth = static_cast<float>(map[0].size());
    this->mapHeight = static_cast<float>(map.size());
    this->tileWidth = 2 / mapWidth;
    this->tileHeight = 2 / mapHeight;

    for (int row = 0; row < mapHeight; row++) {
        for (int col = 0; col < mapWidth; col++) {
            const char tile = map[row][col];
            if (tile == ' ' || tile == '/') continue;

            const float x = normalizeX(col);
            const float y = normalizeY(row);

            switch (tile) {
                case '*':
                    pacman = factory->createPacMan(x, y, mapWidth, mapHeight); break;
                case '.':
                    collectibles.push_back(factory->createCoin(x, y)); break;
                case 'F':
                    collectibles.push_back(factory->createFruit(x, y)); break;
                case '#':
                    ghostExitX = col;
                    ghostExitY = row;
                    collectibles.push_back(factory->createCoin(x, y)); break;
                case 't':
                case 'b':
                case 'r':
                case 'e':
                case 'f':
                case 'h':
                case 'i':
                case 'j':
                case 'k':
                case 'l':
                case 'm':
                case 'u':
                case 'o':
                case 'p':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case 'd':

                // These cases are for the large map only.
                case 'a':
                case 'c':
                case 'g':
                case 'n':
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

    state = WorldState::PLAYING;
}


void World::respawnEntities() {
    pacman->respawn();

    for (const auto& ghost : ghosts) {
        ghost->respawn();
    }

    state = WorldState::PLAYING;
    notify(Events::RESPAWN);
}

void World::startFrightened() {
    state = WorldState::FRIGHTENED;
    timer = 0;

    for (const auto& ghost : ghosts) {
        ghost->setFrightened(true, *this);
    }

    notify(Events::GHOST_FRIGHTENED);
}

void World::endFrightened() {
    state = WorldState::PLAYING;
    flashing = false;

    for (const auto& ghost : ghosts) {
        ghost->setFrightened(false, *this);
    }

    notify(Events::GHOST_NORMAL);
}


void World::updateRestartingState(const double dt) {
    timer += dt;

    if (timer < DEATH_DURATION) return;
    respawnEntities();
}

void World::updateFrightenedState(const double dt) {
    timer += dt;

    if (timer >= FEAR_DURATION) return endFrightened();
    if (timer <= FLASH_TIMESTAMP || flashing) return;

    flashing = true;

    for (const auto& ghost : ghosts) {
        ghost->notify(Events::FRIGHTENED_FLASHING);
    }
}

void World::updatePlayingState(const double dt) {
    pacman->move(*this, dt);
    updateGhosts(dt);
    updateCollectibles();

    if (!collectibles.empty()) return;

    Difficulty::getInstance().increaseDifficulty();
    notify(Events::LEVEL_COMPLETED);
}


void World::updateGhosts(const double dt) {
    for (const auto& ghost : ghosts) {
        ghost->move(*this, dt);

        if (!isColliding(*pacman, *ghost)) continue;
        collissionCoordinates = {ghost->getX(), ghost->getY()};

        ghost->pacmanCollides(*this);
    }
}

void World::updateCollectibles() {
    for (auto it = collectibles.begin(); it != collectibles.end(); ) {
        if (!isColliding(*pacman, **it)) {
            ++it;
            continue;
        }

        collissionCoordinates = {(*it)->getX(), (*it)->getY()};
        const Events event = (*it)->collect();
        notify(event);

        if (event == Events::FRUIT_EATEN) startFrightened();
        it = collectibles.erase(it);
    }
}


void World::update(const double dt) {
    switch (state) {
        case WorldState::AWAITING_MAP:
            throw std::runtime_error("You must load a map before calling World::update.");

        case WorldState::RESTARTING:
            updateRestartingState(dt);
            break;

        case WorldState::FRIGHTENED:
            updateFrightenedState(dt);
            // No break because while frightened, the game continues.

        case WorldState::PLAYING:
            updatePlayingState(dt);
            break;
    }
}


void World::handleMove(const Moves &move) const {
    if (state == WorldState::AWAITING_MAP) throw std::runtime_error("You must load a map before calling World::update.");
    if (state == WorldState::RESTARTING) return;
    pacman->setNextDirection(move);
}


void World::killPacman() {
    if (state == WorldState::AWAITING_MAP) throw std::runtime_error("You must load a map before calling World::update.");
    lives--;

    if (lives == 0) {
        notify(Events::GAME_OVER);
        return;
    }

    state = WorldState::RESTARTING;
    timer = 0;

    pacman->notify(Events::DEATH);
    notify(Events::DEATH);
}
