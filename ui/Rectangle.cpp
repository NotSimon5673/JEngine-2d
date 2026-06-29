#include "Rectangle.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

namespace JUI{

    Rectangle::Rectangle(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor){

        rectObject.setOrigin({size.x/2,size.y/2});
        rectObject.setPosition(position);
        rectObject.setSize(size);
        rectObject.setFillColor(fillColor);
    }

    void Rectangle::draw(sf::RenderWindow& window){ 
        window.draw(this->rectObject);
    }

}