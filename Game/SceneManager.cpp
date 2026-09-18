#include "SceneManager.hpp"
#include "../Scenes/Scenes.hpp"
#include "../Scenes/Menu.hpp"
#include "Events.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include<memory>

namespace Game{

    SceneManager::SceneManager(sf::RenderWindow& parentWindow, std::unique_ptr<AssetManager>& Assets) : window(parentWindow), assets(Assets){
        //Note:: NEVER TRY TO MAKE UNIQUE OF GENERIC SCENE TYPE IT WILL CAUSE SEGFAULTS
        this->currentScene = std::make_unique<Scenes::Menu>(parentWindow, assets);
    }
    SceneManager::~SceneManager() = default;

    void SceneManager::update(sf::Time deltaTime)
    {
        this->sceneInQueue = std::move(currentScene->suggestedScene);
        this->SceneExpired = currentScene->IsExpired;

        currentScene->onUpdate(deltaTime);

        if(currentScene->needsReload) currentScene -> reloadScene();

        if(this->SceneExpired == true) this->nextInQueue();

        if(this->currentScene != nullptr) this->drawCurrentScene();

        this->handleEvents();

    }

    void SceneManager::nextInQueue()
    {
        if(this->currentScene == nullptr) 
            std::cout << "WARNING: SceneManager prompted to switch scenes with no scene in queue";

        else
            this->currentScene = std::move(this->sceneInQueue);
        

        this->SceneExpired = false;
    }

    void SceneManager::drawCurrentScene()
    {
        window.setActive();
        window.clear(currentScene->backGroundColor);


        for(auto& element : currentScene->sceneUI){
            element->draw(window);
        }



        window.display();
    }

    void SceneManager::handleEvents()
    {
        while (const std::optional event = window.pollEvent())
            {
                
                // Request for closing the window
                if (event->is<sf::Event::Closed>()) window.close();
                
                else for(auto& listener : currentScene->events) if(getEventType(event.value()) == listener->eventType) { 
                    listener->activate();
                }
            }
    }

    

}