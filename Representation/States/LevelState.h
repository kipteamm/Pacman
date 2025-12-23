//
// Created by PPetre on 26/11/2025.
//

#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include <unordered_map>

#include "../Entities/ConcreteFactory.h"
#include "../Entities/EntityView.h"
#include "../../Logic/World.h"
#include "../../Logic/Score.h"
#include "../SoundManager.h"
#include "StateManager.h"
#include "../Entities/WorldView.h"


class LevelState final : public State {
public:
    explicit LevelState(StateManager* context, const std::shared_ptr<ConcreteFactory>& factory, const std::shared_ptr<logic::Score>& scoreSystem, int lives);

    void update(double dt) override;
    void handleInput(const sf::Event::KeyEvent &keyPressed) override;
    void render() override;

private:
    std::shared_ptr<ConcreteFactory> factory;
    std::shared_ptr<logic::World> world;
    std::shared_ptr<logic::Score> scoreSystem;
    std::shared_ptr<SoundManager> soundManager;
    std::shared_ptr<WorldView> worldView;

    std::unordered_map<Layer, std::vector<std::shared_ptr<EntityView>>> entityViews{
        {Layer::BACKGROUND, std::vector<std::shared_ptr<EntityView>>()},
        {Layer::FOREGROUND, std::vector<std::shared_ptr<EntityView>>()},
        {Layer::PACMAN, std::vector<std::shared_ptr<EntityView>>()}
    };
};



#endif //LEVELSTATE_H
