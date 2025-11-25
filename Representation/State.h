//
// Created by toroe on 25/11/2025.
//

#ifndef PACMAN_STATE_H
#define PACMAN_STATE_H


class State {
public:
    State();
    virtual ~State() = default;

    virtual void handleInput();
};


class MenuState final: State {
public:
    MenuState();

    void handleInput() override;
};


#endif //PACMAN_STATE_H