#ifndef PACMAN_DIFFICULTY_H
#define PACMAN_DIFFICULTY_H
#include <unordered_map>


namespace logic {


    struct DifficultySpecs {
        int spriteOffset;
        int fruitPoints;
        float pacmanSpeed;
        float ghostSpeed;
        float frighenedGhostSpeed;
        float frightTime;
        int flashesh;
    };


    // https://pacman.holenet.info/#LvlSpecs
    class Difficulty {
    public:
        /**
         * Singletons should not be cloneable or assignable.
         */
        Difficulty(Difficulty &other) = delete;
        void operator=(const Difficulty &) = delete;

        [[nodiscard]] static Difficulty& getInstance();

        void increaseDifficulty();
        [[nodiscard]] DifficultySpecs* getDifficulty();

    private:
        Difficulty();

        int difficulty = 0;

        std::unordered_map<int, DifficultySpecs> difficultyMap = {
            {0, DifficultySpecs{0, 100, 4, 2.3, 0.5, 6, 5}},
            {1, DifficultySpecs{1, 300, 4.4, 2.5, 0.6, 5, 5}},
            {2, DifficultySpecs{2, 500, 4.4, 2.5, 0.6, 4, 5}},
            {3, DifficultySpecs{2, 500, 4.4, 2.5, 0.6, 3, 5}},
            {4, DifficultySpecs{3, 700, 4.5, 2.7, 0.7, 2, 5}},
            {5, DifficultySpecs{3, 700, 4.5, 2.7, 0.7, 5, 5}},
            {6, DifficultySpecs{4, 1000, 4.5, 2.7, 0.7, 2, 5}},
            {7, DifficultySpecs{5, 2000, 4.5, 2.7, 0.7, 2, 5}},
            {8, DifficultySpecs{5, 2000, 4.5, 2.8, 0.7, 1, 2}},
            {9, DifficultySpecs{6, 3000, 4.5, 2.8, 0.7, 2, 4}},
            {10, DifficultySpecs{7, 5000, 4.5, 2.8, 0.8, 1, 2}},
        };
    };
}



#endif