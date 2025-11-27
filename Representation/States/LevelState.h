//
// Created by PPetre on 26/11/2025.
//

#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include "../Entities/ConcreteFactory.h"
#include "../Entities/EntityView.h"
#include "../../Logic/World.h"
#include "StateManager.h"
#include "../Camera.h"


class LevelState final : public State {
public:
    explicit LevelState(StateManager* context, const std::shared_ptr<ConcreteFactory>& factory, const std::shared_ptr<Camera>& camera);

    void update(double dt) override;
    void handleInput(const sf::Event::KeyEvent &keyPressed) override;
    void render() override;

private:
    std::shared_ptr<ConcreteFactory> factory;
    std::unique_ptr<logic::World> world;

    std::vector<std::shared_ptr<EntityView>> entityViews;
};



#endif //LEVELSTATE_H
