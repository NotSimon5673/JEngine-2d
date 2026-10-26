#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace JUI{

    Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, sf::Font& font, std::string message,  sf::Color textColor, uint textSize) : text(position, font, message, textColor, textSize), rect(position, size, fillColor){
        
        this->transform.origin = {size.x/2, size.y/2};
        this->transform.position = position;
        this->transform.scale = {1, 1};
        this->transform.rotation = sf::Angle::Zero;
    }

    void Button::updateTransform(){
        rect.transform.position = this->transform.position;
        text.transform.position = this->transform.position;

        rect.transform.scale = this->transform.scale;
        text.transform.scale = this->transform.scale;

        rect.transform.rotation = this->transform.rotation;
        text.transform.rotation = this->transform.rotation;
    }

    void Button::draw(sf::RenderWindow& window){

        this->updateTransform();
        
        rect.draw(window);
        text.draw(window);
    }
}