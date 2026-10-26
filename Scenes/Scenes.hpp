#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include<list>

#include "../Game/AssetManager.hpp"
#include "../ui/UIElement.hpp"
#include "../ui/Button.hpp"
#include "../ui/Interactable.hpp"
#include "../ui/EventListener.hpp"

namespace Game {class SceneManager;}

namespace Scenes{

    class Scene
    {
        private:

            friend class Game::SceneManager;

            bool IsExpired = false;
            
            std::unique_ptr<Scene> suggestedScene;

            void reloadScene();

            std::unordered_map<Game::EventType, std::list<std::unique_ptr<JUI::EventListener>>> eventMap;


        protected:

            bool needsReload = false;
            void SuggestForQueue(std::unique_ptr<Scene>);
            
        public:

            std::unique_ptr<Game::AssetManager>& assets;

            sf::RenderWindow& window;

            std::list<std::unique_ptr<JUI::UIElement>> sceneUI;
            
            Scene(sf::RenderWindow&, std::unique_ptr<Game::AssetManager>&);
            sf::Color backGroundColor; //probably delete maybe or like turn to UI element

            void addToScene(JUI::UIElement);
            void addToScene(JUI::EventListener);
            virtual void onLoad();         
            virtual void onExpire();       
            virtual void onUpdate(sf::Time deltaTime);    
    };
}