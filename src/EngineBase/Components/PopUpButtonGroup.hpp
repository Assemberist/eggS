#pragma once

#include "Button.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <sys/types.h>

enum PopUpButtonGroupState{
    POPUP_BTN_INACTIVE,
    POPUP_BTN_INVISIBLE,
    POPUP_BTN_POPUP_ANIMATION,
    POPUP_BTN_POPUP_ANIMATION_ENDED,
    POPUP_BTN_COLLAPSED,
    POPUP_BTN_NO_ENTRY_POINTED,
    POPUP_BTN_ENTRY_POINTED,
    POPUP_BTN_ENTRY_PRESSED,
    POPUP_BTN_COLLAPSE_ANIMATION,
    POPUP_BTN_COLLAPSE_ANIMATION_ENDED
};

struct PopUpButtonGroup : public Object{
protected:
    sf::IntRect* targets;
    PopUpButtonGroupState state : 8;
    uint8_t pointed_btn;

    void prepare2popup();
    void prepare2collapse();

public:
    uint8_t animation_steps;
    uint8_t button_num;
    sf::IntRect borders;
    Button* buttons;

    PopUpButtonGroup(){
        flags.flagPointableAndClickable = true;
        flags.flagAnimated = false;
        flags.flagPrintable = true;

        targets = nullptr;
        button_num = 0;
        animation_steps = 0;
        state = POPUP_BTN_COLLAPSED;
    }

	uint32_t on_move(sf::Event& e);
	uint32_t on_click(sf::Event& e);
	uint32_t on_release(sf::Event& e);

    uint8_t get_pointed_btn_id();

    uint32_t play_animation(sf::RenderWindow& win);

    void print(sf::RenderWindow& win);

    ObjectType getType(){ return POPUP_BUTTON_GROUP; }
};