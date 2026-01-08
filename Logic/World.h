#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>

#include "Entities/AbstractFactory.h"
#include "Difficulty.h"


namespace logic {
    enum WorldState { AWAITING_MAP, RESTARTING, FRIGHTENED, PLAYING };

    constexpr float COLLISSION_EPSILON = 0.07f;

    class World final : public Subject {
    public:
        /**
         * @brief Creates a World instance. Creating an instance does nothing
         * on its own.
         * @param factory Concere implementation of AbstractFactory.
         * @param lives Amount of lives that Pacman will begin with.
         */
        explicit World(const std::shared_ptr<AbstractFactory> &factory, int lives);


        /**
         * @brief Returns the width of the currently loaded map (width is in
         * tiles)
         * @return Width
         */
        [[nodiscard]] float getWidth() const;
        /**
         * @brief Returns the height of the currently loaded map (width is in
         * tiles)
         * @return Height
         */
        [[nodiscard]] float getHeight() const;


        /**
         * @brief Exit coordinates are the coordinates specified on the map
         * which Ghosts must go to in their exiting state.
         * @return Ghost exit X coordinate
         */
        [[nodiscard]] int getGhostExitX() const;

        /**
         * @brief Exit coordinates are the coordinates specified on the map
         * which Ghosts must go to in their exiting state.
         * @return Ghost exit Y coordinate
         */
        [[nodiscard]] int getGhostExitY() const;


        /**
         * @return Pacman Model
         */
        [[nodiscard]] std::shared_ptr<PacmanModel> getPacman() const;

        /**
         * @brief The current amount of lives that Pacman has remaining.
         * @return Lives
         */
        [[nodiscard]] unsigned int getLives() const;


        /**
         * @brief Pair that holds the X and Y coordinates of the last
         * collission registered by the World.
         * @return Collission coordinates
         */
        [[nodiscard]] std::pair<float, float> getCollissionCoordinates() const;


        /**
         * @brief Normalizes Grid coordinates on a [-1, 1] bounded coordinate
         * system.
         * @param value Grid X value
         * @return Normalized X value
         */
        [[nodiscard]] float normalizeX(int value) const;

        /**
         * @brief Normalizes Grid coordinates on a [-1, 1] bounded coordinate
         * system.
         * @param value Grid Y value
         * @return Normalized Y value
         */
        [[nodiscard]] float normalizeY(int value) const;


        /**
         * @brief Checks whether the provided coordinates collide with a wall.
         * Takes door Wall types into consideration.
         * @param normalizedX
         * @param normalizedY
         * @param passDoor Whether doors may be seen non-colliding.
         * @return Whether provided coordinates are inside a Wall.
         */
        [[nodiscard]] bool collidesWithWall(float normalizedX, float normalizedY, bool passDoor) const;


        /**
         * @brief Loads any map that is in a rectangular format and follows the
         * specific ASCII formatting. Letters are linked to specific entities.
         * So certain gibberish is unloadable.
         *
         * * - Pacman
         * . - Coin
         * F - Fruit
         * # - Exit tile (acts like a coin and defines the exit coordinates).
         * B - Blinky
         * P - Pinky
         * I - Inky
         * C - Clyde
         * t b r e f h i j k l m u o p 1 2 3 4 5 6 d a c g n - Specific wall pieces
         *
         * @param path Path to file
         */
        void loadMap(const std::string& path);


        /**
         * @brief World Update function. Calls specific helper methods based
         * on the current World state (RESTARTING, FRIGHTENED, PLAYING).
         * @param dt Deltatime
         */
        void update(double dt);


        /**
         * @brief Passes a move down to Pacman.
         * @param move Move
         */
        void handleMove(const Moves& move) const;


        /**
         * @brief Kills Pacman, subtracts a live and puts the World in
         * RESTARTING state.
         */
        void killPacman();

    private:
        /**
         * @param a Entity a
         * @param b Entity b
         * @return Whether a & b collide
         */
        static bool isColliding(const EntityModel& a, const EntityModel& b);


        /**
         * @brief Respawns all entities, notifies observers and sets the World
         * state to PLAYING.
         */
        void respawnEntities();

        /**
         * @brief Sets the World to a FRIGTHENED state, and updates the Ghosts.
         */
        void startFrightened();

        /**
         * @brief Sets the World to PLAYING again and updates the Ghosts.
         */
        void endFrightened();


        /**
         * @brief Will update the restarting timers and respawn all entities
         * when the world is done respawning.
         * @param dt Deltatime
         */
        void updateRestartingState(double dt);

        /**
         * @brief Checks whether the Frightened state is over and calculates
         * when the Ghost should flash.
         * @param dt Deltatime
         */
        void updateFrightenedState(double dt);

        /**
         * @brief Moves entities and checks for collissions. Also checks the
         * win condition of all collectibles being collected and issues an
         * Events::LEVEL_COMPLETED and increases the difficulty.
         * @param dt Deltatime
         */
        void updatePlayingState(double dt);


        /**
         * @brief Moves the ghosts and checks for Pacman collissions.
         * @param dt Deltatime
         */
        void updateGhosts(double dt);

        /**
         * @brief Checks for Pacman collissions with the collectibles.
         */
        void updateCollectibles();

        float mapHeight = 20;
        float mapWidth = 20;

        float tileWidth = 16;
        float tileHeight = 16;

        int ghostExitX;
        int ghostExitY;

        float DEATH_DURATION = 2;
        float FEAR_DURATION = Difficulty::getInstance().getFrightenedTime();
        float FLASH_TIMESTAMP = FEAR_DURATION - (0.4f * Difficulty::getInstance().getFlashesh());

        WorldState state;
        double timer = 0;
        bool flashing = false;

        std::pair<float, float> collissionCoordinates;

        std::shared_ptr<AbstractFactory> factory;
        std::vector<std::shared_ptr<CollectibleEntityModel>> collectibles;
        std::vector<std::shared_ptr<GhostModel>> ghosts;
        std::vector<std::shared_ptr<WallModel>> walls;

        std::shared_ptr<PacmanModel> pacman;
        unsigned int lives;
    };
}



#endif //WORLD_H
