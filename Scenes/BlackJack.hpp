#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Scenes.hpp"
#include <cstdint>
#include "../ui/Button.hpp"


namespace Scenes{

    enum Rank: std::int8_t {Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King};

    enum SuitType :  std::int8_t {Heart,  Diamond, Spade, Club};

    struct Card
    {
    public:
        Card(Rank, SuitType);

        void show(sf::Vector2f, sf::Font&);

        std::int8_t rank;

        SuitType suit;

        std::unique_ptr<JUI::Button> body;

        bool IsHidden = true;
    };

    struct deck : public std::vector<Card> {

        deck();

        void shuffle();
    };

    class BlackJack : public Scene
    {
        private:

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

            deck currentDeck = deck();

            deck discard;

            void draw();

            void end();

        public:     
        BlackJack(sf::RenderWindow&, std::unique_ptr<Game::AssetManager>&);

        virtual void onLoad() override;         
        virtual void onExpire() override;       
        virtual void onUpdate(sf::Time deltaTime) override;    
    };
}