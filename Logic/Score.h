//
// Created by toroe on 26/11/2025.
//

#ifndef PACMAN_SCORE_H
#define PACMAN_SCORE_H

#include <fstream>
#include <vector>

#include "Observer.h"


namespace logic {
    class Score final : public Observer, public Subject {
    public:
        Score();
        ~Score() override;

        [[nodiscard]] std::vector<int> getHighscores();

        void addScore(int score);
        void write() const;

    private:
        std::string filename = "highscores.txt";


        std::vector<int> highscores;

        [[nodiscard]] std::fstream createHighscoresFile() const;
        void update(Events event) override;
    };
}

#endif //PACMAN_SCORE_H