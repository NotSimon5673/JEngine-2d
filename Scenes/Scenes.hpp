#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include<list>

#include "../Game/AssetManager.hpp"
#include "../ui/UIElement.hpp"
#include "../ui/Interactable.hpp"


namespace Game {class SceneManager;}

namespace Scenes{

    class Scene
    {
        private:

            friend class Game::SceneManager;

            bool IsExpired = false;
            
            std::unique_ptr<Scene> suggestedScene;

            void reloadScene();


        protected:
            sf::RenderWindow& window;
            std::unique_ptr<Game::AssetManager>& assets;

            bool needsReload = false;
            void SuggestForQueue(std::unique_ptr<Scene>);
            
        public:
            std::list<std::unique_ptr<JUI::UIElement>> sceneUI;
            std::list<std::unique_ptr<JUI::Interactable>> sceneInteractables;
            
            Scene(sf::RenderWindow&, std::unique_ptr<Game::AssetManager>&);
            sf::Color backGroundColor; //probably delete maybe or like turn to UI element

            virtual void onLoad();         
            virtual void onExpire();       
            virtual void onUpdate(sf::Time deltaTime);    
    };
}