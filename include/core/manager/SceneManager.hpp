#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <string>
#include <map>

#include "core/IScene.hpp"

namespace scarlet
{
    class SceneManager
    {
    private:
        static std::map<std::string,IScene*> scenes;
        static IScene* currentScene;

    public:
        static void AddScene(std::string name, IScene* scene);
        static void RemoveScene(std::string name);
        static void ChangeScene(std::string name);
        static void UpdateScene();
    };
}

#endif