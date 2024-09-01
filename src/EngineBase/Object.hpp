#pragma once	

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

bool isInRect(sf::Vector2i dot, sf::IntRect& rect);

enum ObjectEvent{
	NO_EVENT,
	MOUSE_ENTRY,
	MOUSE_LEFT,
	ANIMATION_START,
	ANIMATION_END,
	BUTTON_CLICK,
};

struct IPointAndClicable{
	virtual uint32_t on_move(sf::Event& e){ return NO_EVENT; }
	virtual uint32_t on_click(sf::Event& e){ return NO_EVENT; }
	virtual uint32_t on_release(sf::Event& e){ return NO_EVENT; }
};

enum ObjectType{
	BUTTON,
	SPRITE,
	POPUP_BUTTON_GROUP
};

struct IPrintable{
	virtual void print(sf::RenderWindow& win) = 0;
};

struct IAnimated{
	virtual uint32_t play_animation() = 0;
}

struct Object{
	virtual ObjectType getType() = 0;
};
