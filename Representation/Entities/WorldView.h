#ifndef PACMAN_WORLDVIEW_H
#define PACMAN_WORLDVIEW_H

#include <SFML/Graphics.hpp>

#include "../../Logic/Score.h"
#include "../../Logic/World.h"


struct ScorePopup {
    sf::Sprite sprite;
    // Time it has spent being active
    double elapsedTime;
    // Tracks whether the Popup is active or can be (re)used.
    bool active;

    /**
     * ScorePopup struct holds a few members that allow me to easily display
     * different scores at different times.
     */
    ScorePopup();

    /**
     * @brief Sets the Sprite sf::TextureRect to the corresponding score.
     * @param score Score to be displayed.
     */
    void setScore(int score);
};


class WorldView final : public logic::Observer {
public:
    /**
     * @brief WorldView renders and manages the Game UI.
     * @param world the World
     * @param scoreSystem the ScoreSystem
     */
    explicit WorldView(
        const std::shared_ptr<logic::World>& world,
        const std::shared_ptr<logic::Score>& scoreSystem
    );

    /**
     * @brief Handles World and ScoreSystem events.
     *
     * Will update the score UI value and possibly show a ScorePopup at an
     * appropriate location if a specific event is received.
     *
     * @param event logic::Events
     */
    void update(logic::Events event) override;

    /**
     * @brief Resizes the Game and World UI.
     */
    void resized();

    /**
     * @brief Renders the Game and World UI.
     */
    void render();

private:
    std::shared_ptr<logic::World> world;
    std::shared_ptr<logic::Score> scoreSystem;

    std::vector<ScorePopup> scores;
    int ghostPoints = logic::GHOST_POINTS;

    sf::Sprite live1;
    sf::Sprite live2;
    sf::Sprite live3;

    sf::Text scoreText;
};


#endif //PACMAN_WORLDVIEW_H