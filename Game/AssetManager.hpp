#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <unordered_map>

namespace Game{
    
    class AssetManager
    {
    private:
        std::unordered_map<std::string, sf::Font> fontCollection;
    public:
        AssetManager();
        ~AssetManager();
        
        void loadFonts();

        sf::Font& getFont(const std::string&);
    
    };
}
