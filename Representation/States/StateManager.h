#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <SFML/Window/Event.hpp>
#include <stack>

#include "../Entities/ConcreteFactory.h"
#include "../../Logic/Score.h"
#include "../SoundManager.h"


class StateManager;

class State {
public:
    /**
     * @brief Handler for KeyPressed events.
     *
     * @param keyPressed SFML KeyEvent
     */
    virtual void handleInput(const sf::Event::KeyEvent &keyPressed) = 0;

    /**
     * @brief Called when the window is resized.
     */
    virtual void resized() = 0;

    /**
     * @bief Update function that is called in the main Game loop.
     *
     * @param dt Deltatime
     */
    virtual void update(double dt) = 0;

    /**
     * @brief Render function that is called in the main Game loop.
     *
     * Should render everything relevant to the current state, that could be UI
     * components, game elements or specific Views.
     */
    virtual void render() = 0;

    virtual ~State() = default;

protected:
    /**
     * \brief Creates the base State object.
     *
     * State is a Base class and not supposed to be used separately.
     *
     * @param ctx StateManager
     */
    explicit State(StateManager& ctx);

    StateManager& context;
};


/**
 * Struct used to hold constants throughout the states. This struct is owned by
 * the StateManager and used by states to get access to its members. This way
 * I can avoid recreating them, when one instance is enough. By giving
 * ownership to the StateManager I can give it a simple getter, saving me from
 * having to pass around a lot of arguments to different states.
 */
struct GameContext {
    std::shared_ptr<logic::Score> scoreSystem;
    std::shared_ptr<SoundManager> soundManager;
    unsigned int lives;
};


class StateManager {
public:
    explicit StateManager();

    /**
     * @brief Returns the top of the manager stack.
     * @throws std::runtime_error When the manager stack is empty
     * @return State reference
     */
    [[nodiscard]] State& top();

    /**
     * @brief Returns the GameContext struct.
     * @return GameContext reference
     */
    [[nodiscard]] GameContext& getGameContext() const;


    /**
     * @brief Helper function for swapping the top state with a new state. Does
     * this by updating the pending command.
     *
     * This function is for when the top state wants to switch itself with a
     * different state. Having the StateManager do the swapping itself, avoids
     * calling push or pop function on already destructed objects.
     *
     * @param state State
     */
    void swap(const std::shared_ptr<State>& state);

    /**
     * @brief Pushes the state to the stack. Does this by updating pending command.
     * @param state State
     */
    void push(const std::shared_ptr<State>& state);

    /**
     * @brief Pops the top state from the stack. Does this by updating pending
     * command.
     * @throws std::runtime_error When the manager stack is empty
     */
    void pop();

    /**
     * @brief Clears the state stack and pushes the new state. Does this by
     * updating pending command.
     * @param state State
     */
    void clear(const std::shared_ptr<State>& state);

    /**
     * @brief Applies any pending command, if there is any pending command.
     */
    void executeCommand();

private:
    std::unique_ptr<GameContext> gameContext;

    std::stack<std::shared_ptr<State>> states;

    enum Command { NONE, SWAP, PUSH, POP, CLEAR };
    struct PendingCommand {
        Command command = Command::NONE;
        std::shared_ptr<State> state = nullptr;
    };

    PendingCommand pendingCommand;
};

#endif //STATEMANAGER_H
