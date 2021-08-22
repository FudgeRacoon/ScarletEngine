#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <iostream>
#include <string>
#include <map>

#include "scarlet/core/IState.hpp"

#include "scarlet/utils/logger/Logger.hpp"

namespace scarlet
{
    class StateManager
    {
    private:
        static std::map<std::string, IState*> states;
        static IState* currentState;

    public:
        static void AddState(std::string name, IState* state);
        static void RemoveState(std::string name);
        static void ChangeState(std::string name);
        static void UpdateState();
    };
}

#endif