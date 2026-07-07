#include "Rectangle.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

namespace JUI{

    Rectangle::Rectangle(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor){

        sf::RectangleShape rect = sf::RectangleShape();
        rect.setOrigin({size.x/2,size.y/2});
        rect.setPosition(position);
        rect.setSize(size);
        rect.setFillColor(fillColor);

        object = std::make_unique<sf::RectangleShape>(rect);
    }

}