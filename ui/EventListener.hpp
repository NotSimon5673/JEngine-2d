#pragma once
#include  <SFML/Graphics.hpp>
#include  <SFML/Window.hpp>
#include "../Game/Events.hpp"

//#define AddEvent(Event) JUI::EventListener(Event, [this]()
#define AddEvent(Parent, Event) JUI::EventListener(Event, [this, Parent]()


namespace JUI {

    class UIElement;

    class EventListener {
    protected:
        std::function<void()> func;
        
    public:
        const Game::EventType eventType;
        
        EventListener(sf::Event, std::function<void()>);

        EventListener(JUI::UIElement, sf::Event, std::function<void()>);

        void activate();
    };
}