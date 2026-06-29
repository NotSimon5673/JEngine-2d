#include "BlackJack.hpp"
#include "../ui/UIElement.hpp"
#include "../ui/Rectangle.hpp"
#include "../ui/Text.hpp"
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

        this->isGameFinished = true;

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
       
        JUI::Button exitButton = JUI::Button({100, 100}, {100, 100}, sf::Color::White, assets->getFont("comic"), "Menu", [this]() {SuggestForQueue(std::make_unique<Scenes::Menu>(window,assets));}, sf::Color::Black, 30);
        this->sceneInteractables.push_back(std::make_unique<JUI::Button>(exitButton));


        JUI::Button hitButton = JUI::Button({window.getSize().x/4, 900}, {400, 100}, sf::Color::White, assets->getFont("kill"), "hit", [this]() {if(this->isPlayerTurn) draw();}, sf::Color::Black, 50);
        this->sceneInteractables.push_back(std::make_unique<JUI::Button>(hitButton));

        JUI::Button standButton = JUI::Button({window.getSize().x*3/4, 900}, {400, 100}, sf::Color::White, assets->getFont("kill"), "stand", [this]() {this->isPlayerTurn = false;}, sf::Color::Black, 50);
        this->sceneInteractables.push_back(std::make_unique<JUI::Button>(standButton));

        
    }

    void BlackJack::onExpire(){

    }

    void BlackJack::onUpdate(){

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
        else while(dealerTotal < 17)
        {
            draw();
        } 
        isPlayerTurn = true;
        this->end();
    }



    void BlackJack::draw(){
        if(this -> isGameFinished) return;

        int temp = (int)currentDeck[0].rank;

        if(temp > 10) temp = 10;

        currentDeck[0].IsHidden = false;

        if(this->isPlayerTurn){
            this->playerTotal += temp;

            currentDeck[0].show({window.getSize().x/2 + playerCards.size() * 200 ,window.getSize().y*6/10}, assets->getFont("comic"));
            this->sceneInteractables.push_back(move(currentDeck[0].body));

            this->playerCards.push_back(std::move(currentDeck[0]));

            if(playerTotal > 21) end();
        } else {
            this->dealerTotal += temp;

            currentDeck[0].show({window.getSize().x/8 + dealerCards.size()* 200 ,window.getSize().y/10}, assets->getFont("comic"));
            this->sceneInteractables.push_back(move(currentDeck[0].body));

            this->dealerCards.push_back(std::move(currentDeck[0]));
            if(playerTotal > 21) end();
            
        }
        currentDeck.erase(currentDeck.begin());
        
    }

    void BlackJack::end(){

        this->isGameFinished = true;

        if(dealerTotal > 21 || (playerTotal > dealerTotal && playerTotal <= 21)){
            std::cout << "you win!";
            this->money -= 100;
        }  else {
            std::cout << "you lose!";
            this->money += 100;
        }

        
        JUI::Button standButton = JUI::Button({window.getSize().x/2, window.getSize().y/2}, {400, 100}, sf::Color::White, assets->getFont("kill"), "play again", [this]() {this->needsReload = true;}, sf::Color::Black, 50);
        this->sceneInteractables.push_back(std::make_unique<JUI::Button>(standButton));        
    }


    Card::Card(Rank r, SuitType sT) : rank(r), suit(sT){}

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
            this->body = std::make_unique<JUI::Button>(JUI::Button(position, {150,210}, sf::Color::White, f, rankStr + " of " + suitStr +"s",[](){return;}, sf::Color::Black,20));
        } else {
            this->body = std::make_unique<JUI::Button>(JUI::Button(position, {150,210}, sf::Color::Red, f, "",[](){return;}));
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