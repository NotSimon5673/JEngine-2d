#include "EventListener.hpp"
#include "UIElement.hpp"

namespace JUI {

    EventListener::EventListener(sf::Event event, std::function<void()> function) : eventType(Game::getEventType(event)), func(function) {}

    EventListener::EventListener(JUI::UIElement parent, sf::Event event, std::function<void()> function) : eventType(Game::getEventType(event)), func(function) {}

    void EventListener::activate() {this->func();}
}