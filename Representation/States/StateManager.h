#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <SFML/Window/Event.hpp>
#include <stack>

#include "../Entities/ConcreteFactory.h"
#include "../../Logic/Score.h"


class StateManager;

class State {
public:
    explicit State(StateManager* ctx);

    virtual ~State() = default;

    virtual void update(double dt) = 0;
    virtual void handleInput(const sf::Event::KeyEvent &keyPressed) = 0;
    virtual void render() = 0;

protected:
    // TODO: check this statement
    // Using a raw pointer because the StateManager owns States and not vica versa
    StateManager* context;
};


struct GameContext {
    std::shared_ptr<ConcreteFactory> factory;
    std::shared_ptr<logic::Score> scoreSystem;
    int lives;
};


class StateManager {
public:
    explicit StateManager(const std::shared_ptr<logic::Score>& scoreSystem);

    // TODO: check this statement
    // Returning a raw pointer because ownership should not be transferred
    [[nodiscard]] State* top();
    [[nodiscard]] bool empty() const;
    [[nodiscard]] GameContext* getGameContext() const;

    void swap(std::unique_ptr<State> state);
    void push(std::unique_ptr<State> state);
    void pop();

private:
    std::unique_ptr<GameContext> gameContext;

    std::stack<std::unique_ptr<State>> states;
};

#endif //STATEMANAGER_H
