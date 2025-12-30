//
// Created by toroe on 26/11/2025.
//

#ifndef PACMAN_SCORE_H
#define PACMAN_SCORE_H

#include <fstream>
#include <utility>
#include <vector>

#include "Observer.h"


namespace logic {
    constexpr int SCORE_DECAY = 10; // 10 points per second
    constexpr int GHOST_POINTS = 200;
    constexpr int LEVEL_CLEAR_POINTS = 500;
    constexpr int BASE_COIN_POINTS = 10;


    struct Highscore {
        std::string username;
        int score;

        Highscore() : username(""), score(0) {}
        Highscore(std::string username, const int score) : username(std::move(username)), score(score) {}

        bool operator<(const Highscore& other) const {
            return score > other.score;
        }
    };


    class Score final : public Observer, public Subject {
    public:
        Score();
        ~Score() override;

        [[nodiscard]] std::vector<std::unique_ptr<Highscore>>* getHighscores();
        [[nodiscard]] int getScore() const;
        [[nodiscard]] const Highscore& getLastScore() const;
        [[nodiscard]] int getGhostPoints() const;

        void setUser(const std::string& username);
        void addScore(int score);
        void write() const;
        void update(double dt);

    private:
        std::string filename = "highscores.txt";
        std::vector<std::unique_ptr<Highscore>> highscores;
        std::string username;
        Highscore lastScore{};

        bool paused = false;
        int score;

        double timeLastCoin = 0;
        double accumulator = 0;
        int ghostPoints = 0;

        [[nodiscard]] std::fstream createHighscoresFile() const;
        void update(Events event) override;
    };
}

#endif //PACMAN_SCORE_H