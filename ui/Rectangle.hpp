#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdio.h>
#include "UIElement.hpp"

namespace JUI{

    class Rectangle: public UIElement
    {
        private:
            
        public:

            sf::RectangleShape rectObject;

            Rectangle(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor);

            void move(sf::Vector2f position);

            void setRotation(sf::Angle destinationAngle);

            void addBorder(float thickness, sf::Color color);

            void setColor(sf::Color);

            void draw(sf::RenderWindow& window) override;
    };
}