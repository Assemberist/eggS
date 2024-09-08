#pragma once

#include "Button.hpp"
#include <cstddef>

enum PopUpButtonGroupState{
    POPUP_BTN_INACTIVE,
    POPUP_BTN_INVISIBLE,
    POPUP_BTN_POPUP_ANIMATION,
    POPUP_BTN_COLLAPSED,
    POPUP_BTN_NO_ENTRY_POINTED,
    POPUP_BTN_ENTRY_POINTED,
    POPUP_BTN_ENTRY_PRESSED,
    POPUP_BTN_COLLAPSE_ANIMATION
};

struct PopUpButtonGroup : public Object{
    Button* buttons;
    uint8_t button_num;
    PopUpButtonGroupState state;

    Button BtnCollapsed;
    struct{
        Button* buttons;
        size_t num;
    } ButtonsInGroup;

    PopUpButtonGroup(){
        flags.flagPointableAndClickable = true;
        flags.flagAnimated = true;
        flags.flagPrintable = true;
    }

	uint32_t on_move(sf::Event& e);
	uint32_t on_click(sf::Event& e);
	uint32_t on_release(sf::Event& e);

    uint32_t play_animation();

    void print(sf::RenderWindow& win);

    ObjectType getType(){ return POPUP_BUTTON_GROUP; }
};