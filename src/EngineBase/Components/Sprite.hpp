#pragma once

#include "../Object.hpp"

struct Sprite : public Object, public IPrintable{
	sf::Sprite sprite;

	ObjectType getType(){ return SPRITE; }
	void print(sf::RenderWindow& win){
		win.draw(sprite);
	}
};