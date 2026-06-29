#include "Scenes.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

namespace Scenes{

    Scene::Scene(sf::RenderWindow& parentWindow, std::unique_ptr<Game::AssetManager>& gameAssets) : window(parentWindow), assets(gameAssets) {

        onLoad();
    }


    void Scene::onLoad(){
        //does nothing lmao
    }

    void Scene::onExpire(){
        //also does nothing...
    }
    
    void Scene::onUpdate(){
        
    }

    void Scene::SuggestForQueue(std::unique_ptr<Scene> suggestedForQueue)
    {
        this->IsExpired = true;

        if(suggestedScene != nullptr)
            std::cout << "WARNING: Scene trying to queue up new scene before current scene in queue has been processed" << "\n";
        else suggestedScene = std::move(suggestedForQueue);
    }

    void Scene::reloadScene(){
        this->needsReload = false;
        this->sceneInteractables.clear();
        this->sceneUI.clear();

        this->onLoad();
    }
}