#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Interactable.hpp"

namespace JUI{

    class Button: public Interactable
    {
        private:
            std::function<void()> buttonFunction;
        public:

            sf::RectangleShape rectObject;
            sf::Text text;

            Button(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, sf::Font& TextFont, std::string message, std::function<void()>, sf::Color textColor = sf::Color::Black, uint textSize = 30);

            void move(sf::Vector2f position);

            void setRotation(sf::Angle destinationAngle);

            void addBorder(float thickness, sf::Color color);

            void setColor(sf::Color);

            void onPress(sf::Vector2i ClickPosition) override {};

            void onRelease(sf::Vector2i ClickPosition) override;

            void draw(sf::RenderWindow& window) override;
    };
}