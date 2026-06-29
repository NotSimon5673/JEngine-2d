#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "UIElement.hpp"

namespace JUI{

    class TextElement : public UIElement
    {
        private:;
        sf::Text text;
        sf::Font loadedFont;
        public:
            TextElement(sf::Vector2f, sf::Font&, std::string, sf::Color, uint size = 30);

            void draw(sf::RenderWindow& window) override;


    };
}