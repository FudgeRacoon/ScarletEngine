#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <iostream>

#include "core/IScene.hpp"

class Editor : public IScene
{
public:
    void OnEnter() override
    {
        std::cout << "Entered the editor scene" << '\n';
    }

    void Update() override
    {
        std::cout << "Editor scene is being updated" << '\n';
    }

    void OnExit() override
    {
        std::cout << "Exited the editor scene" << '\n';
    }
};

#endif