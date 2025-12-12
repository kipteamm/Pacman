//
// Created by PPetre on 26/11/2025.
//

#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include <unordered_map>

#include "../Entities/ConcreteFactory.h"
#include "../Entities/EntityView.h"
#include "../../Logic/World.h"
#include "StateManager.h"
#include "../Camera.h"
#include "../../Logic/Score.h"


class LevelState final : public State {
public:
    explicit LevelState(StateManager* context, const std::shared_ptr<ConcreteFactory>& factory, const std::shared_ptr<Camera>& camera, const std::shared_ptr<logic::Score>& scoreSystem);

    void update(double dt) override;
    void handleInput(const sf::Event::KeyEvent &keyPressed) override;
    void render() override;

private:
    std::shared_ptr<ConcreteFactory> factory;
    std::unique_ptr<logic::World> world;
    std::shared_ptr<logic::Score> scoreSystem;
    std::shared_ptr<Camera> camera;

    std::unordered_map<Layer, std::vector<std::shared_ptr<EntityView>>> entityViews{
        {Layer::BACKGROUND, std::vector<std::shared_ptr<EntityView>>()},
        {Layer::FOREGROUND, std::vector<std::shared_ptr<EntityView>>()},
        {Layer::PACMAN, std::vector<std::shared_ptr<EntityView>>()}
    };

    sf::Sprite live1;
    sf::Sprite live2;
    sf::Sprite live3;

    sf::Text scoreText;
};



#endif //LEVELSTATE_H
