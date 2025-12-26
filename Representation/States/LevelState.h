#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include <unordered_map>

#include "../Entities/WorldView.h"
#include "StateManager.h"


class LevelState final : public State {
public:
    /**
     * @brief This State initiates a Pacman level by setting up a logic::World
     * and rendering the game views.
     * @param context StateManager
     */
    explicit LevelState(StateManager& context);

    void update(double dt) override;
    void handleInput(const sf::Event::KeyEvent &keyPressed) override;
    void render() override;

private:
    std::shared_ptr<ConcreteFactory> factory;
    std::shared_ptr<logic::Score> scoreSystem;
    std::shared_ptr<SoundManager> soundManager;
    std::shared_ptr<logic::World> world;
    std::shared_ptr<WorldView> worldView;

    std::unordered_map<Layer, std::vector<std::shared_ptr<EntityView>>> entityViews{
        {Layer::BACKGROUND, std::vector<std::shared_ptr<EntityView>>()},
        {Layer::FOREGROUND, std::vector<std::shared_ptr<EntityView>>()},
        {Layer::PACMAN, std::vector<std::shared_ptr<EntityView>>()}
    };
};



#endif //LEVELSTATE_H
