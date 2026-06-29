#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace JUI{

    Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, sf::Font& font, std::string message, std::function<void()> func, sf::Color textColor, uint textSize) : text(font, message, textSize), buttonFunction(func){

        rectObject.setOrigin({size.x/2,size.y/2});
        rectObject.setPosition(position);
        rectObject.setSize(size);
        rectObject.setFillColor(fillColor);

        sf::FloatRect bounds = text.getLocalBounds();

        text.setOrigin({bounds.size.x/2, bounds.size.y/2});
        text.setPosition(position);
        text.setFillColor(textColor);
    }

    void Button::draw(sf::RenderWindow& window){ 
        window.draw(this->rectObject);
        window.draw(this->text);
    }

    void Button::onRelease(sf::Vector2i ClickPosition){
        sf::Vector2f Position = rectObject.getPosition();
        sf::Vector2f Size = rectObject.getSize();


        if(ClickPosition.x > Position.x - Size.x/2 && ClickPosition.y > Position.y - Size.y/2 && ClickPosition.x < Position.x + Size.x/2 && ClickPosition.y < Position.y + Size.y/2){
            buttonFunction();
        }
            
            
    }

}