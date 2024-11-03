#include "Scene.hpp"
#include "Object.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

struct{
	bool mouseLeftPressed:1;
	bool dradAndDrop:1;
	bool mouseRightPressed:1;
} eventFlags;

void Scene::activate(){

    while(screen.isOpen()){
		cycle_start();

        // Check input events
		sf::Event e;
		if(screen.pollEvent(e)){
			switch(e.type){
				case sf::Event::Closed:
					screen.close();
                    continue;

                case sf::Event::MouseMoved:
                    state = on_move(e);
                    break;

				case sf::Event::EventType::MouseButtonPressed:
					if(e.mouseButton.button == sf::Mouse::Button::Left)
						state = on_click(e);
					break;

				case sf::Event::EventType::MouseButtonReleased:
					if(e.mouseButton.button == sf::Mouse::Button::Left)
						state = on_release(e);
					break;

				default:
                    break;
			}
		}

		cycle_post_input();

		for(auto i = objects.begin(); i != objects.end(); i++)
			if((*i)->isAnimated())
				(*i)->play_animation(screen);

		cycle_preprint();

        // Display scene components
        screen.clear();
		for(auto i = objects.begin(); i != objects.end(); i++)
			if((*i)->isPrintable())
					(*i)->print(screen);
			//screen.draw(((Sprite*)*i)->sprite);
		screen.display();

		cycle_end();
	}
}

unsigned int Scene::on_key_type(sf::Event& e){ return state; }

unsigned int Scene::on_drag_n_drop(sf::Event& e){ return state; }

unsigned int Scene::on_move(sf::Event& e){ return state; }
unsigned int Scene::on_click(sf::Event& e){ return state; }
unsigned int Scene::on_release(sf::Event& e){ return state; }

void Scene::cycle_start(){}
void Scene::cycle_post_input(){}
void Scene::cycle_preprint(){}
void Scene::cycle_end(){}
