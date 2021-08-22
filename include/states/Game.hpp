#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "scarlet/core/IState.hpp"

class Game : public IState
{
public:
    void OnEnter() override
    {
        std::cout << "Entered the game scene" << '\n';
    }

    void OnUpdate() override
    {
        std::cout << "Game scene is being updated" << '\n';
    }

    void OnImGuiRender() override
    {
        std::cout << "Exited the game scene" << '\n';
    }
};

#endif