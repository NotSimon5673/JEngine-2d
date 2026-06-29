#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

namespace JUI{

    class UIElement
    {
        public:
            virtual void draw(sf::RenderWindow& window) = 0;
    };
}