#include "AssetManager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <unordered_map>
#include <filesystem>

namespace Game{
    
    AssetManager::AssetManager(){
        loadFonts();
    }

    AssetManager::~AssetManager() = default;

    void AssetManager::loadFonts(){
        std::filesystem::path FontFolder = "Fonts";
        
        for (const auto& ttsFile : std::filesystem::directory_iterator(FontFolder)){
            std::string FontID = ttsFile.path().filename().stem();

            fontCollection[FontID] = sf::Font(ttsFile.path());
        }
    }

    sf::Font& AssetManager::getFont(const std::string& ID){
        return fontCollection[ID];
    }
}