#include "Menu.hpp"
#include "../ui/UIElement.hpp"
#include "../ui/Rectangle.hpp"
#include "../ui/Text.hpp"
#include "../ui/Button.hpp"
#include "../ui/EventListener.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "BlackJack.hpp"

namespace Scenes{

    Menu::Menu(sf::RenderWindow& parentWindow, std::unique_ptr<Game::AssetManager>& gameAssets) : Scene(parentWindow, gameAssets) {
        backGroundColor = sf::Color::Red;
        onLoad();
    }

    void Menu::onLoad(){
        
        JUI::TextElement menuTitle = JUI::TextElement( {window.getSize().x/2,  400},assets->getFont("comic"), "JEngine 2D test",sf::Color::Black, 80);
        this->addToScene(menuTitle);

        JUI::TextElement menuSubtitle = JUI::TextElement( {window.getSize().x/2, 500},assets->getFont("comic"), "Ver 0.1.2",sf::Color::Black, 50);
        this->addToScene(menuSubtitle);

        JUI::Button otherButton = JUI::Button({window.getSize().x/2, 700}, {400, 100}, sf::Color::White, assets->getFont("kill"), "play", sf::Color::Black, 50);

        JUI::EventListener ev1 = AddEvent(otherButton, sf::Event::MouseButtonReleased()){
            sf::Vector2i clickPos = sf::Mouse::getPosition();

            if(otherButton.rect.bounds.contains(window.mapPixelToCoords(clickPos))){
                SuggestForQueue(std::make_unique<Scenes::BlackJack>(window,assets));
            } 
        });
        
        this->addToScene(otherButton);
        this->events.push_back(std::make_unique<JUI::EventListener>(ev1));

        JUI::Button exitButton = JUI::Button({window.getSize().x/2, 900}, {400, 100}, sf::Color::White, assets->getFont("comic"), "Quit", sf::Color::Black, 50);
        JUI::EventListener ev2 = AddEvent(exitButton, sf::Event::MouseButtonReleased()){
            sf::Vector2i clickPos = sf::Mouse::getPosition();

            if(exitButton.rect.bounds.contains(window.mapPixelToCoords(clickPos))){
                window.close();
            }

        });

        this->addToScene(exitButton);
        this->events.push_back(std::make_unique<JUI::EventListener>(ev2));

    }

    void Menu::onExpire(){

    }

    void Menu::onUpdate(sf::Time deltaTime){
    }
}