#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "../Entities/ConcreteFactory.h"
#include "../../Logic/Score.h"
#include "StateManager.h"
#include "../Camera.h"

#include <memory>


class MenuState final : public State {
public:
    explicit MenuState(
        const std::shared_ptr<logic::Score>& scoreSystem,
        StateManager* context,
        const std::shared_ptr<ConcreteFactory>& factory,
        const std::shared_ptr<Camera>& camera
    );

    void update(double dt) override {};
    void handleInput(const sf::Event::KeyEvent &keyPressed) override;
    void render() override;

private:
    std::shared_ptr<logic::Score> scoreSystem;
    std::shared_ptr<ConcreteFactory> factory;
    std::shared_ptr<Camera> camera;

    sf::Sprite pacmanLogo;
};


#endif //MENUSTATE_H
