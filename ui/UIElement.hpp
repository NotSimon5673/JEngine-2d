#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include<list>

namespace JUI{

    struct Transform{
            sf::Vector2f position;
            sf::Angle rotation;
            sf::Vector2f scale;
            sf::Vector2f origin;
    };

    //Template for UI elements
    class UIElement{
        private: 
            Transform reference;    //set at runtime
        protected:
            std::shared_ptr<sf::Drawable> object;
        public:
            Transform transform;
            virtual void draw(sf::RenderWindow& window) {
                //can't implement until SFML has a generic parent class for drawable and transformable
                /*
                if(transform.position != reference.position){
                    object->setPosition(transform.position);
                    reference.position = transform.position;
                }
                
                if(transform.rotation != reference.rotation){
                    object->setRotation(transform.rotation);
                    reference.rotation = transform.rotation;
                }

                if(transform.scale != reference.scale){
                    object->setScale(transform.scale);
                    reference.scale = transform.scale;
                }

                if(transform.origin != reference.origin){
                    object->setOrigin(transform.origin);
                    reference.origin = transform.origin;
                }
                */

                window.draw(*object);
            };

            virtual void add(std::list<std::unique_ptr<UIElement>>& UIList){
                //Doesn't work cause of pointer nonsense 
                UIList.push_back(std::unique_ptr<UIElement>(this));
            }
        };
}