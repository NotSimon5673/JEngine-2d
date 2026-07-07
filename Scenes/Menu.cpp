#include "Menu.hpp"
#include "../ui/UIElement.hpp"
#include "../ui/Rectangle.hpp"
#include "../ui/Text.hpp"
#include "../ui/Button.hpp"
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
        
        JUI::Button otherButton = JUI::Button({window.getSize().x/2, 700}, {400, 100}, sf::Color::White, assets->getFont("kill"), "play", [this]() {SuggestForQueue(std::make_unique<Scenes::BlackJack>(window,assets));}, sf::Color::Black, 50);
        this->sceneInteractables.push_back(std::make_unique<JUI::Button>(otherButton));

        JUI::Button exitButton = JUI::Button({window.getSize().x/2, 900}, {400, 100}, sf::Color::White, assets->getFont("comic"), "Quit", [this]() {window.close();}, sf::Color::Black, 50);
        this->sceneInteractables.push_back(std::make_unique<JUI::Button>(exitButton));
    }

    void Menu::onExpire(){

    }

    void Menu::onUpdate(){
        
    }
}