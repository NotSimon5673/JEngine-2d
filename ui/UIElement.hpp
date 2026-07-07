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
            //do this until SFML releases a generic parent class for drawable and transformable objects. object and transformable point to the same object but are different types.
            std::shared_ptr<sf::Drawable> objectDrawable;
            std::shared_ptr<sf::Transformable> objectTransformable;
        public:
            Transform transform;
            virtual void draw(sf::RenderWindow& window) {
                
                if(transform.position != reference.position){
                    objectTransformable->setPosition(transform.position);
                    reference.position = transform.position;
                }
                
                if(transform.rotation != reference.rotation){
                    objectTransformable->setRotation(transform.rotation);
                    reference.rotation = transform.rotation;
                }

                if(transform.scale != reference.scale){
                    objectTransformable->setScale(transform.scale);
                    reference.scale = transform.scale;
                }

                if(transform.origin != reference.origin){
                    objectTransformable->setOrigin(transform.origin);
                    reference.origin = transform.origin;
                }

                window.draw(*objectDrawable);
            };

            virtual void add(std::list<std::unique_ptr<UIElement>>& UIList){
                //Doesn't work cause of pointer nonsense 
                UIList.push_back(std::unique_ptr<UIElement>(this));
            }
        };
}