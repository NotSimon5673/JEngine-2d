#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Scenes.hpp"
#include <cstdint>
#include "../ui/Button.hpp"


namespace Scenes{

    class BlackJack;

    enum Rank: std::int8_t {Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack = 10, Queen = 10, King = 10};

    enum SuitType :  std::int8_t {Heart,  Diamond, Spade, Club};

    class Card
    {
    public:
        Card(Rank, SuitType);

        void show(sf::Vector2f, sf::Font&);

        std::int8_t rank;

        SuitType suit;

        bool IsHidden = true;

        std::unique_ptr<JUI::Rectangle> body;

        std::unique_ptr<JUI::TextElement> text;
    };

    struct deck : public std::vector<Card> {

        deck();

        void shuffle();
    };

    class Player{
        private:
            bool isDealer;
            bool isHuman;

            BlackJack& game;

            std::uint_least64_t funds = 500;
            std::uint_least64_t bet = 100;

            std::vector<Card> hand;

            

        public:

        std::uint_fast8_t cardTotal;
        
        Player(BlackJack& gameScene, bool IsDealer, bool IsPlayer);
        
        
        void newGame();

        void Draw();
    };

    class BlackJack : public Scene
    {
        public:

        Player *winner;

        Player dealer = Player(*this, false, true);
        Player player = Player(*this, true, false);

        JUI::TextElement FPSCounter = JUI::TextElement({900, 50}, assets->getFont("comic"), "FPS: 0", sf::Color::Black, 30);  

        JUI::TextElement moneyCounter = JUI::TextElement({window.getSize().x - 200, 50}, assets->getFont("comic"), "Money: 500", sf::Color::Black, 30);

        JUI::TextElement betCounter = JUI::TextElement({window.getSize().x - 200, 100}, assets->getFont("comic"), "Bet: 100", sf::Color::Black, 30);

        std::uint_least64_t money = 500;
        std::uint_least64_t bet = 100;

        std::uint_fast8_t dealerTotal;
        std::vector<Card> dealerCards;

        std::uint_fast8_t playerTotal;
        std::vector<Card> playerCards;

        bool isGameFinished = false;

        bool isPlayerTurn = false;

        deck discard;

        void draw();

        void end();

        BlackJack(sf::RenderWindow&, std::unique_ptr<Game::AssetManager>&);

        deck currentDeck = deck();

        virtual void onLoad() override;         
        virtual void onExpire() override;       
        virtual void onUpdate(sf::Time deltaTime) override;    
    };
}