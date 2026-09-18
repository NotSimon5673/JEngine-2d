#include "Text.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace JUI{

    TextElement::TextElement(sf::Vector2f position,sf::Font& font, std::string message, sf::Color textColor, uint characterSize){

        loadedFont = font;
        
        sf::Text txt = sf::Text(font, message, characterSize);
        sf::FloatRect bounds = txt.getLocalBounds();
        std::cout << txt.getLocalBounds().size.x << " " << txt.getLocalBounds().size.y << std::endl;
        this->transform.origin = {bounds.size.x/2, bounds.size.y/2};
        this->transform.position = position;
        txt.setFillColor(textColor);

        auto temp = std::make_shared<sf::Text>(txt);

        objectDrawable = temp;
        objectTransformable = temp;
    }

    void TextElement::setText(std::string message){
        sf::Text& txt = dynamic_cast<sf::Text&>(*objectDrawable);
        txt.setString(message);
        
        sf::FloatRect bounds = txt.getLocalBounds();
        this->transform.origin = {bounds.size.x/2, bounds.size.y/2};

        
    }
}
