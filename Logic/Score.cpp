#include "Score.h"

#include <algorithm>
#include <iostream>


using namespace logic;



Score::Score() : score(0) {
    // Try to open the file in read and write mode
    // If the fil does not exist, create it, the function
    // will try to reopen the file in read and write after creation
    std::fstream fileStream(filename);
    if (!fileStream.is_open()) fileStream = createHighscoresFile();

    fileStream.seekg(0);

    std::string line;
    while (std::getline(fileStream, line)) {
        highscores.push_back(std::stoi(line));
    }

    fileStream.close();
}

Score::~Score() {
    write();
}


std::vector<int> Score::getHighscores() {
    return highscores;
}

int Score::getScore() const {
    return score;
}


void Score::addScore(const int score) {
    highscores.push_back(score);

    std::ranges::sort(highscores, std::greater<>());
}


void Score::write() const {
    if (highscores.empty()) return;

    std::ofstream out(filename, std::ios::trunc);
    out.seekp(0);

    out << highscores[0];
    for (int i = 1; i < highscores.size(); i++) {
        out << "\n" << highscores[i];
    }

    out.close();
}

void Score::update(const double dt) {
    if (paused) return;

    timeLastCoin += dt;

    accumulator = 0;
    accumulator += dt;

    if (accumulator < 1 || score <= 0) return;

    score -= SCORE_DECAY;
    accumulator = 0;
    notify(Events::SCORE_UPDATE);
}


std::fstream Score::createHighscoresFile() const {
    std::fstream fileStream(filename, std::ios::out);
    fileStream.close();

    // After creation, try to reopen it in read & try mode
    fileStream.open(filename, std::ios::in | std::ios::out);

    if (!fileStream.is_open()) throw std::runtime_error("Could not create highscores file.");
    return fileStream;
}


void Score::update(const Events event) {
    switch (event) {
        case Events::GAME_OVER:
            addScore(score); break;

        case Events::COIN_EATEN: {
            const int timeBonus = static_cast<int>(50.0 / (timeLastCoin + 0.5));
            score += (BASE_COIN_POINTS + timeBonus);

            timeLastCoin = 0.0;
            break;
        }

        case Events::GHOST_EATEN:
            score += ghostPoints;
            ghostPoints *= 2; break;

        case Events::GHOST_FRIGHTENED:
            ghostPoints = GHOST_POINTS; break;

        case Events::FRUIT_EATEN:
            score += FRUIT_POINTS; break;

        case Events::LEVEL_COMPLETED:
            score += LEVEL_CLEAR_POINTS; break;

        case Events::DEATH:
            paused = true; break;

        case Events::RESPAWN:
            paused = false; break;

        default: return;
    }

    notify(Events::SCORE_UPDATE);
}

