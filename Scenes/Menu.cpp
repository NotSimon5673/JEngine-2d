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
        this->sceneUI.push_back(std::make_unique<JUI::TextElement>(menuTitle));

        JUI::TextElement menuSubtitle = JUI::TextElement( {window.getSize().x/2, 500},assets->getFont("comic"), "Ver 0.1.2",sf::Color::Black, 50);
        this->sceneUI.push_back(std::make_unique<JUI::TextElement>(menuSubtitle));     

        std::unique_ptr<JUI::Button> otherButton = std::make_unique<JUI::Button>(JUI::Button({window.getSize().x/2, 700}, {400, 100}, sf::Color::White, assets->getFont("kill"), "play", sf::Color::Black, 50));
        JUI::EventListener ev1 = JUI::EventListener(otherButton->rect, sf::Event::MouseButtonReleased(),[this]() {SuggestForQueue(std::make_unique<Scenes::BlackJack>(window,assets));});
        //                                                                          ^this will break in the future and is bad
        this->sceneUI.push_back(std::move(otherButton));
        this->events.push_back(std::make_unique<JUI::EventListener>(ev1));

        std::unique_ptr<JUI::Button> exitButton = std::make_unique<JUI::Button>(JUI::Button({window.getSize().x/2, 900}, {400, 100}, sf::Color::White, assets->getFont("comic"), "Quit", sf::Color::Black, 50));
        JUI::EventListener ev2 = JUI::EventListener(exitButton->rect, sf::Event::MouseButtonReleased(),[this]() {window.close();}); 

        this->sceneUI.push_back(std::move(exitButton));
        this->events.push_back(std::make_unique<JUI::EventListener>(ev2));

    }

    void Menu::onExpire(){

    }

    void Menu::onUpdate(sf::Time deltaTime){
    }
}