#ifndef PACMAN_DIFFICULTY_H
#define PACMAN_DIFFICULTY_H
#include <unordered_map>


namespace logic {


    struct DifficultySpecs {
        int fruitSpriteOffset;
        int fruitPoints;
        float pacmanSpeed;
        float ghostSpeed;
        float frighenedGhostSpeed;
        float frightenedTime;
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
        void reset();

        [[nodiscard]] int getFruitSpriteOffset() const;
        [[nodiscard]] int getFruitPoints() const;
        [[nodiscard]] float getPacmanSpeed() const;
        [[nodiscard]] float getGhostSpeed() const;
        [[nodiscard]] float getFrighenedGhostSpeed() const;
        [[nodiscard]] float getFrightenedTime() const;
        [[nodiscard]] int getFlashesh() const;

    private:
        Difficulty();

        std::unordered_map<int, DifficultySpecs> difficultyMap;
        int difficulty = 0;

        DifficultySpecs& currentDifficulty;
    };
}



#endif