#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace JUI{

    Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, sf::Font& font, std::string message, std::function<void()> func, sf::Color textColor, uint textSize) : TextElement(position, font, message, textColor, textSize), Rectangle(position, size, fillColor), buttonFunction(func){

    }

    void Button::onRelease(sf::Vector2i ClickPosition){

        //Until I can get SFML to have a generic parent class for drawable and transformable, this will have to do.
        sf::RectangleShape* rect = dynamic_cast<sf::RectangleShape*>(Rectangle::objectDrawable.get());

        sf::Vector2f Position = rect->getPosition();
        sf::Vector2f Size =rect->getSize();


        if(ClickPosition.x > Position.x - Size.x/2 && ClickPosition.y > Position.y - Size.y/2 && ClickPosition.x < Position.x + Size.x/2 && ClickPosition.y < Position.y + Size.y/2){
            buttonFunction();
        }
            
    }

    void Button::draw(sf::RenderWindow& window){
        Rectangle::draw(window);
        TextElement::draw(window);
    }

}