#include "core/manager/SceneManager.hpp"
#include <windows.h>
using namespace scarlet;

std::map<std::string,IScene*> SceneManager::scenes;
IScene* SceneManager::currentScene = nullptr;

void SceneManager::AddScene(std::string name, IScene* scene)
{
    scenes.insert(std::make_pair(name, scene));
}
void SceneManager::RemoveScene(std::string name)
{
    std::map<std::string,IScene*>::iterator it;
    it = scenes.find(name);

    if(it == scenes.end())
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 4);
        std::cout << "[ERROR]: No scene exists with that name." << '\n';
        SetConsoleTextAttribute(hConsole, 7);
        return;
    }

    scenes.erase(it);
    delete it->second;
}
void SceneManager::ChangeScene(std::string name)
{
    if(currentScene != nullptr)
        currentScene->OnExit();

    std::map<std::string,IScene*>::iterator it;
    it = scenes.find(name);

    if(it == scenes.end())
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 4);
        std::cout << "[ERROR]: No scene exists with that name." << '\n';
        SetConsoleTextAttribute(hConsole, 7);
        return;
    }

    currentScene = it->second;
    currentScene->OnEnter();
}
void SceneManager::UpdateScene()
{
    currentScene->Update();
}