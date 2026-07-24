#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdio.h>
#include "UIElement.hpp"

namespace JUI{
    
    class Interactable: virtual public UIElement
    {
        private:
            bool isHeld = false;
            
        public:

            ~Interactable() = default;
    };
}