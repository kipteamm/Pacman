#ifndef PACMAN_DIFFICULTY_H
#define PACMAN_DIFFICULTY_H
#include <unordered_map>


namespace logic {


    /**
     * Helper struct which holds specific difficulty values. Is mapped against
     * difficulties (in numbers) in the Difficulty::difficultyMap.
     */
    struct DifficultySpecs {
        int fruitSpriteOffset;
        int fruitPoints;
        float pacmanSpeed;
        float ghostSpeed;
        float frighenedGhostSpeed;
        float frightenedTime;
        int flashesh;
    };


    // Relatively accurately based on the table here:
    // https://pacman.holenet.info/#LvlSpecs
    class Difficulty {
    public:
        /**
         * Singletons should not be cloneable or assignable.
         */
        Difficulty(Difficulty &other) = delete;
        void operator=(const Difficulty &) = delete;


        /**
         * @brief Returns an instance of the Difficulty class
         * @return Difficulty instance
         */
        [[nodiscard]] static Difficulty& getInstance();


        //
        // Directly exposing the Specifications from the DifficultySpecs Struct
        // to avoid verbosity.
        //

        /**
         * @brief Retrieves the sprite sheet offset for the fruit associated
         * with the current difficulty level.
         * @return Integer offset for the fruit sprite.
         */
        [[nodiscard]] int getFruitSpriteOffset() const;

        /**
         * @brief The point value differs per difficulty level. As per the
         * original game. https://pacman.fandom.com/wiki/Point_Configurations
         * @return Point value for fruit.
         */
        [[nodiscard]] int getFruitPoints() const;

        /**
         * @brief The speed of Pacman is different on some levels.
         * @return Pacman speed
         */
        [[nodiscard]] float getPacmanSpeed() const;

        /**
         * @brief The speed of the Ghosts is different on some levels.
         * @return Ghost Speed
         */
        [[nodiscard]] float getGhostSpeed() const;

        /**
         * @brief The speed decrease of the ghosts varies on some levels.
         * @return Frightened Ghost Speed negative multiplier.
         */
        [[nodiscard]] float getFrighenedGhostSpeed() const;

        /**
         * @brief This duration differs on every level and goes up and down.
         *
         * By going up and down the player is slightly thrown of guard which
         * makes timing things more difficult for the player.
         *
         * @return How long ghosts are frightened
         */
        [[nodiscard]] float getFrightenedTime() const;

        /**
         * @brief Flashes determine how many warnings the player gets before
         * frightened ghosts turn normal again.
         *
         * Just like the frigthenedTime, this goes up and down between levels
         * to catch the player of guard.
         *
         * @return Amount of flashes
         */
        [[nodiscard]] int getFlashesh() const;


        /**
         * @brief Increases the difficulty for as long as it doesn't out~index
         * the difficulty map. Reuses the final difficulty for anything beyond.
         */
        void increaseDifficulty();

        /**
         * @brief Resets the difficulty back to 0.
         */
        void reset();

    private:
        Difficulty();

        std::unordered_map<int, DifficultySpecs> difficultyMap;
        int difficulty = 0;

        DifficultySpecs& currentDifficulty;
    };
}



#endif