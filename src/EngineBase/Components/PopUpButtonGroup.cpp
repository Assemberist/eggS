#include "PopUpButtonGroup.hpp"
#include "Button.hpp"
#include <cstdint>

/*    POPUP_BTN_INACTIVE,
    POPUP_BTN_INVISIBLE,
    POPUP_BTN_POPUP_ANIMATION,
    POPUP_BTN_COLLAPSED,
    POPUP_BTN_NO_ENTRY_POINTED,
    POPUP_BTN_ENTRY_POINTED,
    POPUP_BTN_ENTRY_PRESSED,
    POPUP_BTN_COLLAPSE_ANIMATION    */

uint32_t PopUpButtonGroup::on_move(sf::Event& e){
    switch(state){
        case POPUP_BTN_COLLAPSED:
            if(isInRect(sf::Vector2i{e.mouseMove.x, e.mouseMove.y}, BtnCollapsed.borders)){
                state = POPUP_BTN_POPUP_ANIMATION;
                
                return ANIMATION_START;
            }
    }
}

uint32_t PopUpButtonGroup::on_click(sf::Event& e){
    switch(state){
    }
}

uint32_t PopUpButtonGroup::on_release(sf::Event& e){
    switch(state){
    }
}

uint32_t PopUpButtonGroup::play_animation(){
    return NO_EVENT;
}

void PopUpButtonGroup::print(sf::RenderWindow& win){

}