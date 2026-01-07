#ifndef CONCRETEFACTORY_H
#define CONCRETEFACTORY_H

#include <unordered_map>
#include <vector>

#include "../../Logic/Entities/AbstractFactory.h"
#include "EntityView.h"


/**
 * Used to separate Views from each other and define a render order. LevelState
 * renders these as such that PACMAN will always be in front of FOREGROUND
 * views (Ghosts), which in turn will be in front of BACKGROUND views (Coins,
 * Walls, Fruits).
 */
enum Layer { PACMAN, FOREGROUND, BACKGROUND };


class ConcreteFactory final : public logic::AbstractFactory {
public:
    /**
     * @brief Creates a ConreteFactory that can be passed to the World.
     * Requires a views container from LevelState to append to.
     * @param views LevelState views container
     */
    explicit ConcreteFactory(std::unordered_map<Layer, std::vector<std::shared_ptr<EntityView>>>& views);


    /**
     * @brief Creates a PacmanModel and View.
     *
     * The View will be attached as an observer to the Model. The view will
     * also be appended to the PACMAN layer in the LevelState views container.
     *
     * @param x Initial x position
     * @param y Initial y position
     * @param mapWidth Amount of horizontal tiles
     * @param mapHeight Amount of vertical tiles
     * @return PacmanModel to be used by the world
     */
    std::shared_ptr<logic::PacmanModel> createPacMan(float x, float y, float mapWidth, float mapHeight) override;

    /**
     * @brief Creates a ChasingGhost and a normal GhostView (no distinction is
     * made between GhostViews).
     *
     * The View will be attached as an observer to the Model. The view will
     * also be appended to the FOREGROUND layer in the LevelState views
     * container.
     *
     * @param x Normalized initial x position
     * @param y Normalized initial y position
     * @param mapWidth Amount of horizontal tiles
     * @param mapHeight Amount of vertical tiles
     * @return ChasingGhost to be used by the world
     */
    std::shared_ptr<logic::ChasingGhost> createBlinky(float x, float y, float mapWidth, float mapHeight) override;

    /**
     * @brief Creates an AmbushGhost and a normal GhostView (no distinction is
     * made between GhostViews).
     *
     * The View will be attached as an observer to the Model. The view will
     * also be appended to the FOREGROUND layer in the LevelState views
     * container.
     *
     * @param x Normalized initial x position
     * @param y Normalized initial y position
     * @param mapWidth Amount of horizontal tiles
     * @param mapHeight Amount of vertical tiles
     * @return AmbushGhost to be used by the world
     */
    std::shared_ptr<logic::AmbushGhost> createPinky(float x, float y, float mapWidth, float mapHeight) override;
    /**
     * @brief Creates an AmbushGhost and a normal GhostView (no distinction is
     * made between GhostViews).
     *
     * The View will be attached as an observer to the Model. The view will
     * also be appended to the FOREGROUND layer in the LevelState views
     * container.
     *
     * @param x Normalized initial x position
     * @param y Normalized initial y position
     * @param mapWidth Amount of horizontal tiles
     * @param mapHeight Amount of vertical tiles
     * @return AmbushGhost to be used by the world
     */
    std::shared_ptr<logic::AmbushGhost> createInky(float x, float y, float mapWidth, float mapHeight) override;

    /**
     * @brief Creates a RandomGhost and a normal GhostView (no distinction is
     * made between GhostViews).
     *
     * The View will be attached as an observer to the Model. The view will
     * also be appended to the FOREGROUND layer in the LevelState views
     * container.
     *
     * @param x Normalized initial x position
     * @param y Normalized initial y position
     * @param mapWidth Amount of horizontal tiles
     * @param mapHeight Amount of vertical tiles
     * @return RandomGhost to be used by the world
     */
    std::shared_ptr<logic::RandomGhost> createClyde(float x, float y, float mapWidth, float mapHeight) override;

    /**
     * @brief Creates WallModel and View.
     *
     * The View will be attached as an observer to the Model. The view will
     * also be appended to the BACKGROUND layer in the LevelState views
     * container.
     *
     * @param x Normalized initial x position
     * @param y Normalized initial y position
     * @param type Used by to determine the sprite of the view and whether the
     * model is a door
     * @return WallModel to be used by the world
     */
    std::shared_ptr<logic::WallModel> createWall(float x, float y, char type) override;

    /**
     * @brief Creates CoinModel and View.
     *
     * The View will be attached as an observer to the Model. The view will
     * also be appended to the BACKGROUND layer in the LevelState views
     * container.
     *
     * @param x Normalized initial x position
     * @param y Normalized initial y position
     * @return CoinModel to be used by the world
     */
    std::shared_ptr<logic::CoinModel> createCoin(float x, float y) override;

    /**
     * @brief Creates FruitModel and View.
     *
     * The View will be attached as an observer to the Model. The view will
     * also be appended to the BACKGROUND layer in the LevelState views
     * container.
     *
     * @param x Normalized initial x position
     * @param y Normalized initial y position
     * @return FruitModel to be used by the world
     */
    std::shared_ptr<logic::FruitModel> createFruit(float x, float y) override;

private:
    std::unordered_map<Layer, std::vector<std::shared_ptr<EntityView>>>& entityViews;
};




#endif //CONCRETEFACTORY_H
