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


void StateManager::swap(const std::shared_ptr<State>& state) {
    if (states.empty()) throw std::runtime_error("StateManager stack is empty");
    pendingCommand = {Command::SWAP, state};
}

void StateManager::push(const std::shared_ptr<State>& state) {
    pendingCommand = {Command::PUSH, state};
}

void StateManager::pop() {
    if (states.empty()) throw std::runtime_error("StateManager stack is empty");
    pendingCommand = {Command::POP, nullptr};
}

void StateManager::clear(const std::shared_ptr<State>& state) {
    pendingCommand = {Command::CLEAR, state};
}


void StateManager::executeCommand() {
    switch (pendingCommand.command) {
        case Command::NONE: return;

        case Command::SWAP:
            states.pop();
            states.push(pendingCommand.state); break;

        case Command::PUSH:
            states.push(pendingCommand.state); break;

        case Command::POP:
            states.pop(); break;

        case Command::CLEAR:
            while (!states.empty()) states.pop();
            states.push(pendingCommand.state); break;

        default: break;
    }

    pendingCommand = {Command::NONE, nullptr};
}
