#pragma once

#include "Object.hpp"
#include "Resource.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/Window/Event.hpp>
#include <vector>

// window.setFramerateLimit(60);

class Scene{
protected:
	sf::RenderWindow screen;
	std::vector<Resource> resources;
	std::vector<Object*> objects;

	unsigned int state;
	bool dragFlag;

	virtual unsigned int on_move(sf::Event& e);
	virtual unsigned int on_drag_n_drop(sf::Event& e);
	virtual unsigned int on_key_type(sf::Event& e);
	virtual unsigned int on_click(sf::Event& e);
	virtual unsigned int on_release(sf::Event& e);

	virtual void cycle_start();
	virtual void cycle_post_input();
	virtual void cycle_preprint();
	virtual void cycle_end();

public:
	void activate();
	virtual void resourceLoad() = 0;
	virtual void resourceRelease() = 0;
};