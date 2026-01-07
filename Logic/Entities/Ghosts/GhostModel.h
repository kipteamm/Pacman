#ifndef PACMAN_GHOSTMODEL_H
#define PACMAN_GHOSTMODEL_H

#include "../PacmanModel.h"


namespace logic {

    /**
     * Ghosts have a few states they could be in. Being frightened is not a
     * State but rather a way of being in some sense. I decided against making
     * it a State because it overlaps with what the Ghost actually is (doing)
     * at that point.
     *
     * WAITING:
     *      This is the initial state of a (respawned) Ghost. A Ghost waits for
     *      as long as it is still on cooldown before EXITING.
     * EXITING:
     *      This is an intermediary state between WAITING and CHASING. This
     *      state forces the Ghost to get out of its enclosure. The moment it
     *      successfully left said enclosure it will start CHASING.
     * CHASING:
     *      While CHASING a Ghost will target Pacman as per it's specific
     *      targetting behaviour. It will not stop doing so unless frightened,
     *      afterwhich it will pause its chasing activities and start running
     *      away. When no longer frigthened it will just continue as normal.
     * DEAD:
     *      In this state Pacman can no longer collide with the Ghost. A Ghost
     *      will remain in this state while it is navigating back to its
     *      enclosure. When it is at its spawnpoint again it will be in a
     *      WAITING state again.
     */
    enum class GhostState { WAITING, EXITING, CHASING, DEAD };


    class GhostModel : public MovingEntityModel {
    public:
        /**
         * @brief Base class for Ghosts. Handles Ghost state and how that
         * influences ghost behaviour.
         *
         * Uses GhostNavigator helper functions for Pathfinding and Path
         * related decision-making.
         *
         * @param normalizedX Normalized x spawn coordinate
         * @param normalizedY Normalized y spawn coordinate
         * @param mapWidth Map width (in tiles)
         * @param mapHeight Map height (in tiles)
         * @param cooldown Spawn cooldown before leaving enclosure
         */
        explicit GhostModel(float normalizedX, float normalizedY, float mapWidth, float mapHeight, double cooldown);
        ~GhostModel() override = default;


        /**
         * @brief Returns the current state of the Ghost.
         * @return GhostState
         */
        [[nodiscard]] GhostState getState() const;

        /**
         * @brief Returns whether the Ghost is currently frightened.
         * @return Frightened
         */
        [[nodiscard]] bool isFrightened() const;

        /**
         * @brief Returns the Grid mapped X coordinate of where the Ghost
         * spawned.
         * @return Grid X coordinate of Ghost spawn
         */
        [[nodiscard]] int getGridSpawnX() const;

        /**
         * @brief Returns the Grid mapped Y coordinate of where the Ghost
         * spawned.
         * @return Grid Y coordinate of Ghost spawn
         */
        [[nodiscard]] int getGridSpawnY() const;


        /**
         * @brief Allows the World to set toggle whether the Ghost is
         * Frigthened or not.
         * @warning Any change to the frightened state is ignored while a
         * Ghost is dead.
         *
         * Changes the Ghost's internal state and notifies Observers. Updates
         * the Ghost speed to match its frightenedness. Updates the Ghost's
         * internal pathing to either run away or re-target Pacman.
         *
         * @param frightened True or False toggle
         * @param world World
         */
        void setFrightened(bool frightened, const World& world);


        /**
         * @brief Tells the Ghost it collided with Pacman and should handle
         * this situation.
         *
         * Depending on whether the Ghost is frightened or not it will kill
         * Pacman, or get killed.
         *
         * @param world World
         */
        void pacmanCollides(World& world);

        /**
         * @brief This function is to be called in the World update loop. The
         * Ghost will act based on it's current State and possibly move.
         *
         * Whether the Ghost actually moves or not depends on its state. A
         * GhostState::WAITING will not move until its cooldown runs out.
         * Otherwise, it will move based on it's behaviour and whether it is
         * frightened.
         *
         * @param world World
         * @param dt Deltatime since last call
         */
        void move(const World& world, float dt) override;

        /**
         * @brief Tell the Ghost to respawn. It will go back to its spawnpoint
         * and start in a GhostState::WAITING state again.
         *
         * If the Ghost must respawn because of getting eaten while being
         * frightened, it may instantly switch to a GhostState::EXITING without
         * waiting for its cooldown to pass. If Pacman dies and the World
         * resets, the Ghost will have to watch its cooldown again.
         */
        void respawn() override;

    protected:
        /**
         * @brief This function must be overriden by any inheriting Ghost
         * classes. It must return the best Move according to its attacking
         * personality.
         * @param world World
         * @return The best Move for this Ghost
         */
        virtual Moves decideNextMove(const World& world) = 0;

    private:
        /**
         * @brief Checks whether the Ghost has surpassed its cooldown and may
         * leave its enclosure.
         * @param world World
         * @param dt Deltatime since last call
         */
        void updateWaiting(const World& world, double dt);

        /**
         * @brief Checks whether the Ghost has finished leaving its enclosure
         * and is ready to target Pacman.
         * @param world World
         */
        void updateExiting(const World& world);

        /**
         * @brief In this state the Ghost will either chase Pacman based on its
         * behaviour, or run away if frightened.
         * @param world World
         */
        void updateChasing(const World& world);

        /**
         * @brief When dead the Ghost will BFS its way back to its enclosure.
         * @param world World
         */
        void updateDead(const World& world);

        GhostState state;
        float defaultSpeed;

        int gridSpawnX;
        int gridSpawnY;

        bool frightened = false;

        double startCooldown;
        double waitingTime;

        std::list<Moves> cachedPath;
    };

}


#endif //PACMAN_GHOSTMODEL_H