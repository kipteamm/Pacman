#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "../Entities/ConcreteFactory.h"
#include "../../Logic/Score.h"
#include "StateManager.h"


class MenuState final : public State {
public:
    explicit MenuState(StateManager& context);

    void update(double dt) override;
    void handleInput(const sf::Event::KeyEvent &keyPressed) override;
    void render() override;

private:
    std::shared_ptr<logic::Score> scoreSystem;

    sf::Sprite pacmanLogo;
    std::string username;

    bool renderCta = true;
    double elapsedTime;
};


#endif //MENUSTATE_H
