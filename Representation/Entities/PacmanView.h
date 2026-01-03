#ifndef PACMANVIEW_H
#define PACMANVIEW_H

#include <unordered_map>

#include "../../Logic/Entities/PacmanModel.h"
#include "EntityView.h"


class PacmanView final : public EntityView {
public:
    /**
     * @brief PacmanView renders & animates Pacman.
     * @param model Reference Model
     */
    explicit PacmanView(const std::shared_ptr<logic::PacmanModel> &model);

    /**
     * @brief Resizes the Pacman sprite.
     */
    void resized() override;

    /**
     * @brief Renders the Pacman sprite and the Pacman direction indicator.
     */
    void render() override;

private:
    /**
     * @brief Handles World events and animates or changes the view accordingly.
     * @param event World Events
     */
    void update(logic::Events event) override;

    // I store the PacmanModel in the view insteawd of dynamic casting the
    // generic model used in the base EntityView class to use PacmanModel
    // specific functions.
    std::shared_ptr<logic::PacmanModel> pacman;

    bool dying = false;
    // When the model did not move, the current frame of the Pacman walking
    // animation will not update until this boolean changes, effectively
    // freezing Pacman.
    bool moving = true;

    std::unordered_map<int, std::vector<sf::IntRect>> animations{};
    int animationIndex;

    sf::Sprite directionSprite;
};



#endif //PACMANVIEW_H
