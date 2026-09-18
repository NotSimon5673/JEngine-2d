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
    
    void Scene::onUpdate(sf::Time deltaTime){
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
        this->sceneUI.clear();
        this->events.clear();

        this->onLoad();
    }

    void Scene::addToScene(JUI::UIElement element){
        this->sceneUI.push_back(std::make_unique<JUI::UIElement>(element));
    }

    void Scene::addToScene(JUI::Button button){
        this->sceneUI.push_back(std::make_unique<JUI::Button>(button));
    }
}