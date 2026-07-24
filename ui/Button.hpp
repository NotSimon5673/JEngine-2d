#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Interactable.hpp"
#include "Rectangle.hpp"
#include "Text.hpp"

namespace JUI{

    class Button: public UIElement{

        private:
            

        public:

        //put back in private once my awful code is fixed
            Rectangle rect;
            TextElement text;

            sf::Vector2f Size; //uhhh change this later probably

            Button(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, sf::Font& TextFont, std::string message,  sf::Color textColor = sf::Color::Black, uint textSize = 30);

            void move(sf::Vector2f position);

            void setRotation(sf::Angle destinationAngle);

            void addBorder(float thickness, sf::Color color);

            void setColor(sf::Color);

            void draw(sf::RenderWindow& window) override;

            void updateTransform() override;

            ~Button() override = default;
    };
}