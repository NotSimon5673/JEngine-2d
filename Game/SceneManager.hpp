#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "AssetManager.hpp"
#include <iostream>

//forward declarations
namespace Scenes{

    class Scene;
} 

namespace Game{

    class SceneManager
    {
    private:
        sf::RenderWindow& window;
        std::unique_ptr<AssetManager>& assets;

        std::unique_ptr<Scenes::Scene> currentScene;
        std::unique_ptr<Scenes::Scene> sceneInQueue;

        bool SceneExpired;
    public:
        SceneManager(sf::RenderWindow&, std::unique_ptr<AssetManager>&);
        ~SceneManager();

        void update(sf::Time deltaTime);
        
        void nextInQueue();

        void drawCurrentScene();

        void handleEvents();
    
        
    };
}
