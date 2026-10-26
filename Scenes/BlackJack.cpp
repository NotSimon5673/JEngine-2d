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

        this->isPlayerTurn = false;

        player.newGame();
        dealer.newGame();

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
                player.Draw();
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

        
        player.Draw();
        player.Draw();

        dealer.Draw();

        this->isPlayerTurn = true;

    }

    void BlackJack::onExpire(){

    }

    void BlackJack::onUpdate(sf::Time deltaTime){

        FPSCounter.setText("FPS: " + std::to_string((int)(1/deltaTime.asSeconds())));

        if(isGameFinished == true) end();

        else if(isPlayerTurn == false){
            dealer.Draw();
        }

    }

    void BlackJack::end(){

        JUI::TextElement resultText = JUI::TextElement({window.getSize().x/2, window.getSize().y/4}, assets->getFont("comic"), "", sf::Color::Black, 50);
        if(dealer.cardTotal > 21 || (player.cardTotal > dealer.cardTotal && player.cardTotal <= 21)){
            
            resultText.setText("You Win!");
            this->money += this->bet;
        }  
        else if(dealer.cardTotal == player.cardTotal){
            resultText.setText("Tie");
        }
        else {
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

    Player::Player(BlackJack& BJScene, bool isD, bool isP) : game(BJScene), isDealer(isP), isHuman(isP) {
        
        if(isDealer){
            this->funds = 1'000'000'000;
            this->bet = 100;
        }

        if(isHuman){ 
            this->funds = 500;
            this->bet = 100;
        }
    }

    void Player::Draw(){
        deck& Deck  = this->game.currentDeck;
        Deck[0].IsHidden = false;
        this->cardTotal += (int)Deck[0].rank;
        float yPos;
        float xPos;

        if(this->isDealer){
            yPos = 0.1f;
            xPos = 0.125f;
        }
        else{
            yPos = 0.6f;
            xPos = 0.5f;
        }

        if((int)Deck[0].rank == 1 && this->cardTotal <= 10) this->cardTotal += 10;

        Deck[0].show({game.window.getSize().x*xPos + this->hand.size() * 200 , game.window.getSize().y*yPos}, game.assets->getFont("comic"));
        game.sceneUI.push_back(std::move(Deck[0].body));
        game.sceneUI.push_back(std::move(Deck[0].text));

        this->hand.push_back(std::move(Deck[0]));

        Deck.erase(Deck.begin());

        if(this->cardTotal >= 21 || (isDealer == true && cardTotal >= 17)){
            this->game.isGameFinished = true;
        }
        
    }

    void Player::newGame(){
        this->cardTotal = 0;

        for(auto& card : this->hand){
            this->game.discard.push_back(std::move(card));
        }
        hand.clear();
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