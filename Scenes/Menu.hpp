#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Scenes.hpp"


namespace Scenes{

    class Menu : public Scene
    {
        public:     
        Menu(sf::RenderWindow&, std::unique_ptr<Game::AssetManager>&);

        virtual void onLoad() override;         
        virtual void onExpire() override;       
        virtual void onUpdate() override;    
    };
}