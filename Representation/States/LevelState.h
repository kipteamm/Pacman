#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include <unordered_map>

#include "../Entities/WorldView.h"
#include "StateManager.h"


class LevelState final :
    public State,
    public logic::Observer,
    public std::enable_shared_from_this<LevelState> {

    // The Pass-Key pattern is a way to control who can create instances of a
    // class when using smart pointers. Smart pointers do not work with private
    // constructors, so a different method is used.
    struct passkey{};

public:
    /**
     * @brief Creates a LevelState which initiates a Pacman Level by setting up
     * a logic::Word and rendering the game views.
     * @param context
     * @return LevelState std::shared_ptr
     */
    static std::shared_ptr<LevelState> create(StateManager& context);

    /**
     * @warning This constructor uses the passkey pattern as you are not
     * suposed to directly interact with it. Use LevelState::create instead.
     * @brief This State initiates a Pacman level by setting up a logic::World
     * and rendering the game views.
     * @param context StateManager
     */
    explicit LevelState(passkey, StateManager& context);

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
     * @brief Passes concrete Moves to the World instance & handles pausing.
     * @param keyPressed SFML KeyEvent
     */
    void handleInput(const sf::Event::KeyEvent &keyPressed) override;

    /**
     * @brief Will resize the Game Views.
     */
    void resized() override;

    /**
     * @brief Updates ScoreSystem and World.
     * @param dt Deltatime
     */
    void update(double dt) override;

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
    bool resizeRequired;

    std::unordered_map<Layer, std::vector<std::shared_ptr<EntityView>>> entityViews{
        {Layer::BACKGROUND, std::vector<std::shared_ptr<EntityView>>()},
        {Layer::FOREGROUND, std::vector<std::shared_ptr<EntityView>>()},
        {Layer::PACMAN, std::vector<std::shared_ptr<EntityView>>()}
    };
};



#endif //LEVELSTATE_H
