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
        StateManager* context,
        const std::shared_ptr<logic::Score>& scoreSystem,
        const std::shared_ptr<ConcreteFactory>& factory
    );

    void handleInput(const sf::Event::KeyEvent &keyPressed) override;
    void update(double dt) override;
    void render() override;

private:
    std::shared_ptr<logic::Score> scoreSystem;
    std::shared_ptr<ConcreteFactory> factory;

    sf::Sprite pacmanLogo;
    std::string username;

    bool renderCta = true;
    double elapsedTime;
};


#endif //MENUSTATE_H
