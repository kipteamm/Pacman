//
// Created by PPetre on 24/11/2025.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>


class Window {
public:
    /**
     * Singletons should not be cloneable or assignable.
     */
    Window(Window &other) = delete;
    void operator=(const Window &) = delete;

    [[nodiscard]] static Window* getInstance();

    /**
     * Directly exposing SFML RenderWindow methods to reduce verbosity
     */
    bool isOpen() const;
    bool pollEvent(sf::Event& event);
    void draw(const sf::Drawable& drawable);
    void clear();
    void display();
    void close();

private:
    Window();

    static Window* instance;
    sf::RenderWindow window;
};



#endif //WINDOW_H
