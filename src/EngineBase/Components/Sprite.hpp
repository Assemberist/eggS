#pragma once

#include "../Object.hpp"

struct Sprite : public Object{
	sf::Sprite sprite;

	Sprite(){ flags.flagPrintable = 1; }

	ObjectType getType(){ return SPRITE; }
	void print(sf::RenderWindow& win){
		win.draw(sprite);
	}
};