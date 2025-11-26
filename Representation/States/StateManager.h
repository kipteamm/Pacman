//
// Created by PPetre on 26/11/2025.
//

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <memory>
#include <SFML/Graphics.hpp>

#include <stack>


class StateManager;

class State {
public:
    explicit State(StateManager* ctx);

    virtual ~State() = default;

    virtual void update() = 0;
    virtual void handleInput(const sf::Event::KeyEvent &keyPressed) = 0;
    virtual void render() = 0;

protected:
    // TODO: check this statement
    // Using a raw pointer because the StateManager owns States and not vica versa
    StateManager* context;
};


class StateManager {
public:
    StateManager() = default;

    void swap(std::unique_ptr<State> state);
    void push(std::unique_ptr<State> state);
    void pop();

    // TODO: check this statement
    // Returning a raw pointer because ownership should not be transferred
    [[nodiscard]] State* top();
    [[nodiscard]] bool empty() const;

private:
    std::stack<std::unique_ptr<State>> states;
};

#endif //STATEMANAGER_H
