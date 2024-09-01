#pragma once

#include <SFML/Graphics/Rect.hpp>
#include "../Object.hpp"
#include <SFML/Window/Event.hpp>
#include <cstdint>

enum ButtonState{
    BTN_POINTED,
    BTN_PRESSED,
    BTN_INACTIVE,
    BTN_INVISIBLE,
    BTN_IDLE
};

struct Button : public Object,
                public IPointAndClicable,
                public IPrintable{
    sf::IntRect borders;
    const char* text;
    ButtonState state;

	uint32_t on_move(sf::Event& e);
	uint32_t on_click(sf::Event& e);
	uint32_t on_release(sf::Event& e);

    uint32_t activate();
    uint32_t deactivate();

    uint32_t show();
    uint32_t hide();

    ObjectType getType(){ return BUTTON; }

    void print(sf::RenderWindow& win);
};