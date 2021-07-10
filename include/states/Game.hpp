#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "core/IState.hpp"

class Game : public IState
{
public:
    void OnEnter() override
    {
        std::cout << "Entered the game scene" << '\n';
    }

    void Update() override
    {
        std::cout << "Game scene is being updated" << '\n';
    }

    void OnExit() override
    {
        std::cout << "Exited the game scene" << '\n';
    }
};

#endif