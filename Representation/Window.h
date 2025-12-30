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

    /**
     * @brief Returns an instance of the Window class.
     *
     * @return Window instance
     */
    [[nodiscard]] static Window& getInstance();


    //
    // Directly exposing SFML RenderWindow methods to reduce verbosity.
    //


    /**
     * @brief Tell whether the window is open
     *
     * @return True if the window is open, false if has been closed.
    */
    [[nodiscard]] bool isOpen() const;

    /**
     * @brief Pop the event on top of the event queue, if any, and return it.
     *
     * This function is not blocking: if there's no pending event then it will
     * return false and leave <b>event</b> unmodified. Note that more than one event
     * may be present in the event queue, thus you should always call this
     * function in a loop to make sure that you process every pending event
     *
     * @param event Event to be returned.
     * @return True if an event was returned, or false if the event queue was empty.
     */
    [[nodiscard]] bool pollEvent(sf::Event& event);

    /**
     * @brief Draw a drawable object to the window
     *
     * @param drawable Object to draw
     */
    void draw(const sf::Drawable& drawable);

    /**
     * @brief Clear the window.
     */
    void clear();

    /**
     * @brief Display on screen what has been drawn to the window since the last clear.
     */
    void display();

    /**
     * @brief Close the window and destroy all the attached resources
     */
    void close();

    /**
     * @brief Limit the framerate to a maximum fixed frequency
     *
     * If a limit is set, the window will use a small delay after each call to
     * display() to ensure that the current frame lasted long enough to match
     * the framerate limit. SFML will try to match the given limit as much as
     * it can, but since it internally uses sf::sleep, whose precision depends
     * on the underlying OS, the results may be a little unprecise as well (for
     * example, you can get 65 FPS when requesting 60).
     *
     * @param frameRate Framerate limit, in frames per seconds (use 0 to disable
     * limit).
     */
    void setFramerateLimit(unsigned int frameRate);

    /**
     * @brief Change the current active view
     *
     * The view is like a 2D camera, it controls which part of the 2D scene is
     * visible, and how it is viewed in the render target. The new view will
     * affect everything that is drawn, until another view is set. The render
     * target keeps its own copy of the view object, so it is not necessary to
     * keep the original one alive after calling this function. To restore the
     * original view of the target, you can pass the result of getDefaultView()
     * to this function.
     *
     * @param view New view to use
     */
    void setView(const sf::View& view);

    /**
     * @brief Get the width of the rendering region of the window. This does not
     * include the borders of the window.
     *
     * @return Width in pixels
     */
    [[nodiscard]] unsigned int getWidth() const;

    /**
     * @brief Get the height of the rendering region of the window. This does not
     * include the titlebar or borders of the window.
     *
     * @return Height in pixels
     */
    [[nodiscard]] unsigned int getHeight() const;

private:
    Window();

    sf::RenderWindow window;
};


#endif //WINDOW_H
