#include "StateManager.h"


State::State(StateManager& ctx) : context(ctx) {}


StateManager::StateManager() {
    gameContext = std::make_unique<GameContext>(
        std::make_shared<logic::Score>(),
        std::make_shared<SoundManager>(),
        3
    );
}


State& StateManager::top() {
    if (states.empty()) throw std::runtime_error("StateManager stack is empty");
    return *states.top();
}

GameContext& StateManager::getGameContext() const {
    return *gameContext;
}


void StateManager::swap(std::unique_ptr<State> state) {
    states.pop();
    states.push(std::move(state));
}

void StateManager::push(std::unique_ptr<State> state) {
    states.push(std::move(state));
}

void StateManager::pop() {
    if (states.empty()) throw std::runtime_error("StateManager stack is empty");
    states.pop();
}


void StateManager::clear(std::unique_ptr<State> state) {
    while (!states.empty()) {
        states.pop();
    }

    states.push(std::move(state));
}
