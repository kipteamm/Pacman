//
// Created by toroe on 26/11/2025.
//

#ifndef PACMAN_SCORE_H
#define PACMAN_SCORE_H

#include <fstream>
#include <vector>

#include "Observer.h"


namespace logic {
    constexpr int SCORE_DECAY = 10; // 10 points per second
    constexpr int GHOST_POINTS = 200;
    constexpr int FRUIT_POINTS = 100;
    constexpr int LEVEL_CLEAR_POINTS = 500;
    constexpr int BASE_COIN_POINTS = 10;

    class Score final : public Observer, public Subject {
    public:
        Score();
        ~Score() override;

        [[nodiscard]] std::vector<int> getHighscores();
        [[nodiscard]] int getScore() const;

        void addScore(int score);
        void write() const;
        void update(double dt);

    private:
        std::string filename = "highscores.txt";

        double timeLastCoin;
        std::vector<int> highscores;
        int score;

        [[nodiscard]] std::fstream createHighscoresFile() const;
        void update(Events event) override;
    };
}

#endif //PACMAN_SCORE_H