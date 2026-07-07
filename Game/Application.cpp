#include "Application.hpp"
#include "SceneManager.hpp"
#include "AssetManager.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

namespace Game{

    Application::Application(): window(sf::VideoMode::getDesktopMode(), "Simon game", sf::State::Fullscreen){

        this->assetManager = std::make_unique<AssetManager>();
        this->sceneManager = std::make_unique<SceneManager>(window, assetManager);
    }
    Application::~Application() = default;

    void Application::run(){

        sf::Clock clock;
        clock.start();
        while(window.isOpen()){
            sf::Time deltaTime = clock.restart();
            sceneManager->update(deltaTime);
        }
    }








}