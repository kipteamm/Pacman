#include <algorithm>
#include <filesystem>
#include <iostream>

#include "Difficulty.h"
#include "Score.h"

using namespace logic;


Score::Score() : score(0) {
    std::fstream fileStream(filename);

    // If the file does not yet exist, create a new one. I can instantly return
    // because there are no scores to be read.
    if (!std::filesystem::exists(filename)) {
        createHighscoresFile();
        return;
    };

    if (!fileStream.is_open()) throw std::runtime_error("Could not open '" + filename + "'");
    fileStream.seekg(0);

    // Loop over all the lines in the file and extract the ScoreEntry
    // information. Scores must be formatted as USERNAME:SCORE which is parsed
    // here and added to the ScoreEntry vector.
    std::string line;
    while (std::getline(fileStream, line)) {
        std::string username;
        std::string score;
        bool colon = false;

        for (char c : line) {
            if (c == ':') colon = true;
            else if (colon) score += c;
            else username += c;
        }

        highscores.push_back(std::make_unique<ScoreEntry>(username, std::stoi(score)));
    }

    fileStream.close();
}

Score::~Score() {
    write();
}


std::vector<std::unique_ptr<ScoreEntry>>& Score::getHighscores() {
    return highscores;
}

int Score::getScore() const {
    return score;
}

const ScoreEntry& Score::getLastScore() const {
    return lastScore;
}


void Score::setUser(const std::string& username) {
    this->username = username;
}


void Score::addScoreEntry() {
    auto highscore = std::make_unique<ScoreEntry>(username, score);
    lastScore = *highscore;
    highscores.push_back(std::move(highscore));
    this->score = 0;

    // Sort all score entries when a new one is inserted.
    std::ranges::sort(highscores, [](const auto& a, const auto& b) {
        return *a < *b;
    });
}


void Score::write() const {
    if (highscores.empty()) return;

    std::ofstream out(filename, std::ios::trunc);
    out.seekp(0);

    // Write the score entries to the file, in descending order in the same
    // USERNAME:SCORE format.
    out << highscores[0]->username << ":" << highscores[0]->score;
    for (int i = 1; i < highscores.size(); i++) {
        out << "\n" << highscores[i]->username << ":" << highscores[i]->score;
    }

    out.close();
}

void Score::update(const double dt) {
    if (paused) return;

    timeLastCoin += dt;
    accumulator += dt;

    if (accumulator < 1 || score <= 0) return;

    score -= SCORE_DECAY;
    accumulator -= 1;
    notify(Events::SCORE_UPDATE);
}


void Score::createHighscoresFile() const {
    std::fstream fileStream(filename, std::ios::out);
    fileStream.close();
}

void Score::update(const Events event) {
    switch (event) {
        case Events::GAME_OVER:
            addScoreEntry(); break;

        case Events::COIN_EATEN: {
            // Rewards the player for eating coins in a short span. The quicker
            // the succession, the higher the reward. This allows for 'perfect'
            // runs which optimise the coin eating timing. Based on the
            // original game, however I never really managed to pull such
            // 'perfect' runs.
            const int timeBonus = static_cast<int>(50.0 / (timeLastCoin + 0.5));
            score += BASE_COIN_POINTS + timeBonus;

            // Resets after every coin to allow for a "combo" like feeling.
            timeLastCoin = 0.0;
            break;
        }

        case Events::GHOST_EATEN:
            score += ghostPoints;
            // ghostPoints work exponentionally when eaten within one
            // "Frightened" state.
            ghostPoints *= 2; break;

        case Events::GHOST_FRIGHTENED:
            ghostPoints = GHOST_POINTS; break;

        case Events::FRUIT_EATEN:
            // The points rewarded for a coin depend on the current difficulty.
            score += Difficulty::getInstance().getFruitPoints(); break;

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
