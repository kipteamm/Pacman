#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include <unordered_map>

#include "../Entities/WorldView.h"
#include "StateManager.h"


class LevelState final : public State, public logic::Observer {
public:
    /**
     * @brief This State initiates a Pacman level by setting up a logic::World
     * and rendering the game views.
     * @param context StateManager
     */
    explicit LevelState(StateManager& context);

    /**
     * @brief Observer update function called by all subscribed Subjects.
     *
     * This function orchestrates what happens after specific World events.
     * Events handled are GameOver or Victory States and View deletion.
     *
     * @param event World events
     */
    void update(logic::Events event) override;

    /**
     * @brief Updates ScoreSystem and World.
     * @param dt Deltatime
     */
    void update(double dt) override;

    /**
     * @brief Passes concrete Moves to the World instance & handles pausing.
     * @param keyPressed
     */
    void handleInput(const sf::Event::KeyEvent &keyPressed) override;

    /**
     * @brief Renders all Views associated with this level. Does this on a
     * layer basis.
     */
    void render() override;

private:
    std::shared_ptr<ConcreteFactory> factory;
    std::shared_ptr<logic::Score> scoreSystem;
    std::shared_ptr<SoundManager> soundManager;
    std::shared_ptr<logic::World> world;
    std::shared_ptr<WorldView> worldView;

    bool cleanupRequired;

    std::unordered_map<Layer, std::vector<std::shared_ptr<EntityView>>> entityViews{
        {Layer::BACKGROUND, std::vector<std::shared_ptr<EntityView>>()},
        {Layer::FOREGROUND, std::vector<std::shared_ptr<EntityView>>()},
        {Layer::PACMAN, std::vector<std::shared_ptr<EntityView>>()}
    };
};



#endif //LEVELSTATE_H
