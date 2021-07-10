#include "core/manager/StateManager.hpp"
#include "core/Logger.hpp"
using namespace scarlet;

std::map<std::string, IState*> StateManager::states;
IState* StateManager::currentState = nullptr;

void StateManager::AddState(std::string name, IState* State)
{
    states.insert(std::make_pair(name, State));
}
void StateManager::RemoveState(std::string name)
{
    std::map<std::string,IState*>::iterator it;
    it = states.find(name);

    if(it == states.end())
    {
        Logger::LogError("No State exists with that name.");
        return;
    }
    if(it->second == currentState)
    {
        Logger::LogFatal("Cannot remove currently active State.");
        return;
    }

    states.erase(it);
    delete it->second;
}
void StateManager::ChangeState(std::string name)
{
    std::map<std::string,IState*>::iterator it;
    it = states.find(name);

    if(it == states.end())
    {
        Logger::LogError("No State exists with that name.");
        return;
    }

    if(currentState != nullptr)
        currentState->OnExit();

    currentState = it->second;
    currentState->OnEnter();
}
void StateManager::UpdateState()
{
    currentState->Update();
}