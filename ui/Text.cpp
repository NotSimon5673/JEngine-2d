#include "Text.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace JUI{

    TextElement::TextElement(sf::Vector2f position,sf::Font& font, std::string message, sf::Color textColor, uint characterSize){

        loadedFont = font;
        
        sf::Text txt = sf::Text(font, message, characterSize);
        sf::FloatRect bounds = txt.getLocalBounds();

        txt.setOrigin({bounds.size.x/2, bounds.size.y/2});
        txt.setPosition(position);
        txt.setFillColor(textColor);

        objectDrawable = std::make_shared<sf::Text>(txt);
        objectTransformable = std::make_shared<sf::Text>(txt);
    }

    void TextElement::setText(std::string message){

        sf::Text& txt = dynamic_cast<sf::Text&>(*objectDrawable);
        sf::FloatRect bounds = txt.getLocalBounds();

        txt.setString(message);
    }
}
