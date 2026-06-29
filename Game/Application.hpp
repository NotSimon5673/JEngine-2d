
#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
namespace Game{

    //Forward Declarations
    class SceneManager;
    class AssetManager;


    class Application
    {
    private:
        sf::RenderWindow window;
        std::unique_ptr<SceneManager> sceneManager;
        std::unique_ptr<AssetManager> assetManager;

    public:
        Application();
        ~Application();

        void run();

        void stopApplication();

    };
}

