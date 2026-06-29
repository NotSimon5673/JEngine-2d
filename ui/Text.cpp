#include "Text.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace JUI{

    TextElement::TextElement(sf::Vector2f position,sf::Font& font, std::string message, sf::Color textColor, uint characterSize) : text(font, message, characterSize){

        sf::FloatRect bounds = text.getLocalBounds();

        text.setOrigin({bounds.size.x/2, bounds.size.y/2});
        text.setPosition(position);
        text.setFillColor(textColor);
    }

    void TextElement::draw(sf::RenderWindow& window){
        window.draw(this->text);
    }

}
