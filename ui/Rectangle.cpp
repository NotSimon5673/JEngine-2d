#include "Rectangle.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

namespace JUI{

    Rectangle::Rectangle(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor){

        sf::RectangleShape rect = sf::RectangleShape();

        this->transform.origin = {size.x/2, size.y/2};
        this->transform.position = position;
        this->transform.scale = {1, 1};
        this->transform.rotation = sf::Angle::Zero;

        rect.setSize(size);
        rect.setFillColor(fillColor);

        std::shared_ptr<sf::RectangleShape> temp = std::make_shared<sf::RectangleShape>(rect);

        objectDrawable = temp;
        objectTransformable = temp;
    }

}