#include "Rectangle.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

namespace JUI{

    Rectangle::Rectangle(sf::Vector2f position, sf::Vector2f rectangleSize, sf::Color fillColor){

        sf::RectangleShape rect = sf::RectangleShape();

        this->transform.origin = {rectangleSize.x/2, rectangleSize.y/2};
        this->transform.position = position;
        this->transform.scale = {1, 1};
        this->transform.rotation = sf::Angle::Zero;

        rect.setSize(rectangleSize);
        rect.setFillColor(fillColor);

        this->bounds = rect.getGlobalBounds();
        this->bounds.position = position - this->transform.origin;

        std::shared_ptr<sf::RectangleShape> temp = std::make_shared<sf::RectangleShape>(rect);

        objectDrawable = temp;
        objectTransformable = temp;
    }

}