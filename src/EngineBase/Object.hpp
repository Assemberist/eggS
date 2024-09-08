#pragma once	

#include <cstdint>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <sys/types.h>

bool isInRect(sf::Vector2i dot, sf::IntRect& rect);

enum ObjectEvent{
	NO_EVENT,
	MOUSE_ENTRY,
	MOUSE_LEFT,
	ANIMATION_START,
	ANIMATION_END,
	BUTTON_CLICK,
};

enum ObjectType{
	BUTTON,
	SPRITE,
	POPUP_BUTTON_GROUP
};

struct Object{
protected:
	struct{
		uint32_t flagAnimated : 1;
		uint32_t flagPointableAndClickable : 1;
		uint32_t flagPrintable : 1;
	} flags;

public:
	Object(){ *(uint32_t*)&flags = 0; }
	virtual ObjectType getType() = 0;

	// Pointable & Clickable
	bool isPointableAndClickable(){ return flags.flagPointableAndClickable; }
	virtual uint32_t on_move(sf::Event& e){ return NO_EVENT; }
	virtual uint32_t on_click(sf::Event& e){ return NO_EVENT; }
	virtual uint32_t on_release(sf::Event& e){ return NO_EVENT; }

	// Printable
	bool isPrintable(){ return flags.flagPrintable; }
	virtual void print(sf::RenderWindow& win){};

	// Animated
	bool isAnimated(){ return flags.flagAnimated; }
	virtual uint32_t play_animation(){ return NO_EVENT; };
};
