#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdio.h>
#include "UIElement.hpp"

namespace JUI{
    
    class Interactable: public UIElement
    {
        private:
            bool isHeld = false;
            
        public:
            virtual void onPress(sf::Vector2i ClickPosition) = 0;

            virtual void onRelease(sf::Vector2i ClickPosition) = 0;
    };
}