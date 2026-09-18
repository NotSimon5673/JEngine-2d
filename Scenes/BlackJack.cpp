#include "BlackJack.hpp"
#include "../ui/UIElement.hpp"
#include "../ui/Rectangle.hpp"
#include "../ui/Text.hpp"
#include "../ui/EventListener.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include<chrono>
#include<vector>
#include<format>
#include "Menu.hpp"

namespace Scenes{

    BlackJack::BlackJack(sf::RenderWindow& parentWindow, std::unique_ptr<Game::AssetManager>& gameAssets) : Scene(parentWindow, gameAssets) {
        backGroundColor = sf::Color::Green;
        currentDeck.shuffle();
        onLoad();
    }

    void BlackJack::onLoad(){

        this->isGameFinished = false;

        this->dealerTotal = 0;
        this->playerTotal = 0;
        this->isPlayerTurn = false;

        for(auto& card : playerCards){
            this->discard.push_back(std::move(card));
        }
        playerCards.clear();

        for(auto& card : dealerCards){
            this->discard.push_back(std::move(card));
        }
        dealerCards.clear();

        this->addToScene(FPSCounter);
        this->addToScene(moneyCounter);
        this->addToScene(betCounter);
       
        JUI::Button exitButton = JUI::Button({100, 100}, {100, 100}, sf::Color::White, assets->getFont("comic"), "Menu", sf::Color::Black, 30);
        JUI::EventListener ev3 = AddEvent(exitButton, sf::Event::MouseButtonReleased()){
            sf::Vector2i clickPos = sf::Mouse::getPosition();

            if(exitButton.rect.bounds.contains(window.mapPixelToCoords(clickPos))){
                SuggestForQueue(std::make_unique<Scenes::Menu>(window,assets));
            } 
        });
                
        this->addToScene(exitButton);
        this->events.push_back(std::make_unique<JUI::EventListener>(ev3));


        JUI::Button hitButton = JUI::Button({window.getSize().x/4, 900}, {400, 100}, sf::Color::White, assets->getFont("kill"), "hit", sf::Color::Black, 50);
        JUI::EventListener hitEvent = AddEvent(hitButton, sf::Event::MouseButtonReleased()){
            sf::Vector2i clickPos = sf::Mouse::getPosition();

            if(hitButton.rect.bounds.contains(window.mapPixelToCoords(clickPos)) && this->isPlayerTurn){
                draw();
            }
        });

        this->addToScene(hitButton);
        this->events.push_back(std::make_unique<JUI::EventListener>(hitEvent));

        JUI::Button standButton = JUI::Button({window.getSize().x*3/4, 900}, {400, 100}, sf::Color::White, assets->getFont("kill"), "stand", sf::Color::Black, 50);
        JUI::EventListener standEvent = AddEvent(standButton, sf::Event::MouseButtonReleased()){
            sf::Vector2i clickPos = sf::Mouse::getPosition();

            if(standButton.rect.bounds.contains(window.mapPixelToCoords(clickPos))){
                this->isPlayerTurn = false;
            }
        });
        this->addToScene(standButton);
        this->events.push_back(std::make_unique<JUI::EventListener>(standEvent));

        
    }

    void BlackJack::onExpire(){

    }

    void BlackJack::onUpdate(sf::Time deltaTime){
        
        FPSCounter.setText("FPS: " + std::to_string((int)(1/deltaTime.asSeconds())));

        if(isPlayerTurn){
            if(playerCards.size() == 0){
                draw();
                draw();
            }
            return;
        };
        
        if(dealerCards.size() == 0)
        {
            draw();
            isPlayerTurn = true;
            return;
        }  
        else while(dealerTotal < 17 && this->isGameFinished == false)
        {
            draw();
        } 
        isPlayerTurn = true;
        this->end();
    }

    void BlackJack::draw(){
        if(this -> isGameFinished) return;

        currentDeck[0].IsHidden = false;

        if(this->isPlayerTurn){
            this->playerTotal += (int)currentDeck[0].rank;

            if((int)currentDeck[0].rank == 1 && playerTotal <= 10) this->playerTotal += 10;

            currentDeck[0].show({window.getSize().x/2 + playerCards.size() * 200 ,window.getSize().y*6/10}, assets->getFont("comic"));
            this->sceneUI.push_back(std::move(currentDeck[0].body));
            this->sceneUI.push_back(std::move(currentDeck[0].text));

            this->playerCards.push_back(std::move(currentDeck[0]));

            if(playerTotal > 21) end();
        } else {
            this->dealerTotal += (int)currentDeck[0].rank;

            if((int)currentDeck[0].rank == 1 && dealerTotal <= 10) this->dealerTotal += 10;

            currentDeck[0].show({window.getSize().x/8 + dealerCards.size()* 200 ,window.getSize().y/10}, assets->getFont("comic"));
            this->sceneUI.push_back(std::move(currentDeck[0].body));
            this->sceneUI.push_back(std::move(currentDeck[0].text));

            this->dealerCards.push_back(std::move(currentDeck[0]));
            if(dealerTotal > 21) end();
            
        }
        currentDeck.erase(currentDeck.begin());
        
    }

    void BlackJack::end(){

        this->isGameFinished = true;

        JUI::TextElement resultText = JUI::TextElement({window.getSize().x/2, window.getSize().y/4}, assets->getFont("comic"), "", sf::Color::Black, 50);
        if(dealerTotal > 21 || (playerTotal > dealerTotal && playerTotal <= 21)){
            
            resultText.setText("You Win!");
            this->money += this->bet;
        }  else {
            resultText.setText("You Lose!");
            this->money -= this->bet;
        }
        this->addToScene(resultText);

        moneyCounter.setText("Money: " + std::to_string(this->money));

        JUI::Button replayButton = JUI::Button({window.getSize().x/2, window.getSize().y/2 - 20}, {400, 100}, sf::Color::White, assets->getFont("kill"), "play again", sf::Color::Black, 50);
        JUI::EventListener replayEvent = AddEvent(replayButton, sf::Event::MouseButtonReleased()){
            if(replayButton.rect.bounds.contains(window.mapPixelToCoords(sf::Mouse::getPosition()))){
                this->needsReload = true;
            }
        });

        this->addToScene(replayButton);
        this->events.push_back(std::make_unique<JUI::EventListener>(replayEvent));
    }   


    Card::Card(Rank r, SuitType sT) : rank(r), suit(sT){
    }

    void Card::show(sf::Vector2f position,  sf::Font& f){

        std::string rankStr;
        std::string suitStr;

        switch((int)(this->suit)){
            case 0:
                suitStr = "Heart";
                break;
            case 1:
                suitStr = "Diamond";
                break;
            case 2:
                suitStr = "Spade";
                break;
            case 3:
                suitStr = "Club";
                break;
        }

        switch((int)(this->rank)){
            case 1:
                rankStr = "Ace";
                break;
            case 11:
                rankStr = "Jack";
                break;
            case 12:
                rankStr = "Queen";
                break;
            case 13:
                rankStr = "King";
                break;
            default:
                rankStr = std::to_string(rank); 
        }

        if(this->IsHidden == false){
            this->body = std::make_unique<JUI::Rectangle>(JUI::Rectangle(position, {150,210}, sf::Color::White));
            this->text = std::make_unique<JUI::TextElement>(JUI::TextElement(position, f, rankStr + " of " + suitStr +"s", sf::Color::Black, 20));
        } else {
            this->body = std::make_unique<JUI::Rectangle>(JUI::Rectangle(position, {150,210}, sf::Color::Red));
        }
    }

    deck::deck(){
        for(int suit = 0; suit < 4; suit ++){
            for(int rank = 1; rank < 14; rank++){
                this->push_back(Card((Rank)rank, (SuitType)suit));
            }
        }
    }

    void deck::shuffle(){
        for(int i = 0; i < this->size(); i++){

            std::vector<Card>& Deck = *this;
   
            auto CurrentTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

           short RandPos = CurrentTime % this->size();

           std::swap(Deck[i], Deck[RandPos]);
        }
    }
}