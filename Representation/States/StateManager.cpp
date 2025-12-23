#include "StateManager.h"


State::State(StateManager *ctx) : context(std::move(ctx)) {}


StateManager::StateManager(const std::shared_ptr<logic::Score>& scoreSystem) {
    gameContext = std::make_unique<GameContext>(
        std::make_shared<ConcreteFactory>(),
        scoreSystem,
        3
    );
}


State* StateManager::top() {
    if (states.empty()) return nullptr;
    return states.top().get();
}

bool StateManager::empty() const {
    return states.empty();
}

GameContext* StateManager::getGameContext() const {
    return gameContext.get();
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
