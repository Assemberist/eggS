#include "PopUpButtonGroup.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstdint>

#ifndef debich
    #define astr(A) #A
    #define frm(A) "\"" astr(A) " = %d\"\n"
    #define dbg(A) printf(frm(A), A)
#else
    #define dbg(A)
#endif

#define HORISONTAL_PAD 10

/*    POPUP_BTN_INACTIVE,
    POPUP_BTN_INVISIBLE,
    POPUP_BTN_POPUP_ANIMATION,
    POPUP_BTN_COLLAPSED,
    POPUP_BTN_NO_ENTRY_POINTED,
    POPUP_BTN_ENTRY_POINTED,
    POPUP_BTN_ENTRY_PRESSED,
    POPUP_BTN_COLLAPSE_ANIMATION    */

void PopUpButtonGroup::prepare2popup(){
    sf::Vector2i O = {buttons[0].borders.left + buttons[0].borders.width / 2,
                      buttons[0].borders.top  + buttons[0].borders.height / 2};

    // buttons[0] is reserved for initial settings.
    // targets[0] also reserved

    int Rh = buttons[1].borders.height;
    for(int i = 2; i < button_num; i++)
        if(buttons[i].borders.height > Rh)
            Rh = buttons[i].borders.height;

    int Rw = buttons[1].borders.width;
    for(int i = 2; i < button_num; i++)
        Rw += buttons[i].borders.width + HORISONTAL_PAD;

    int X0 = O.x - Rw/2;
    int Y0 = O.y - Rh/2;

    borders = {X0, Y0, Rw, Rh};

    dbg(X0);
    dbg(Y0);
    dbg(Rw);
    dbg(Rh);

    targets = new sf::IntRect[button_num];
    
    targets[1].left = X0;
    targets[1].top = O.y - buttons[1].borders.height / 2;

    for(int i = 2; i < button_num; i++){
        targets[i].left = targets[i-1].left + buttons[i].borders.width + HORISONTAL_PAD;
        targets[i].top = O.y - buttons[1].borders.height / 2;
    }
}

void PopUpButtonGroup::prepare2collapse(){

}

uint32_t PopUpButtonGroup::on_move(sf::Event& e){
    dbg(state);
    switch(state){
        case POPUP_BTN_COLLAPSED:
            if(isInRect(sf::Vector2i{e.mouseMove.x, e.mouseMove.y}, borders)){
                state = POPUP_BTN_POPUP_ANIMATION;
                flags.flagAnimated = true;
                flags.flagPointableAndClickable = false;
                prepare2popup();
                return ANIMATION_START;
            }
            break;

        case POPUP_BTN_ENTRY_POINTED:
            if(buttons[pointed_btn].on_move(e) == NO_EVENT)
                return NO_EVENT;
            else{
                state = POPUP_BTN_NO_ENTRY_POINTED;
                pointed_btn = 0;
            }

        case POPUP_BTN_NO_ENTRY_POINTED:
            if(isInRect({e.mouseMove.x, e.mouseMove.y}, borders)){
                for(int i = 1; i < button_num; i++)
                    if(buttons[i].on_move(e) == MOUSE_ENTRY){
                        state = POPUP_BTN_ENTRY_POINTED;
                        pointed_btn = i;
                        return MOUSE_ENTRY;
                    }

                return NO_EVENT;
            }

            state = POPUP_BTN_COLLAPSE_ANIMATION;
            flags.flagAnimated = true;
            flags.flagPointableAndClickable = false;
            prepare2collapse();
            return ANIMATION_START;

        default:
            break;
    }
    return NO_EVENT;
}

uint32_t PopUpButtonGroup::on_click(sf::Event& e){
    switch(state){
        default:
            return NO_EVENT;
    }
}

uint32_t PopUpButtonGroup::on_release(sf::Event& e){
    switch(state){
        default:
            return NO_EVENT;
    }
}

uint32_t PopUpButtonGroup::play_animation(sf::RenderWindow& win){
    switch(state){
        case POPUP_BTN_COLLAPSE_ANIMATION: {

            break;
        }

        case POPUP_BTN_POPUP_ANIMATION: {
            if(animation_steps == 0){
                for(int i = 1; i < button_num; i++) {
                    buttons[i].borders.left = targets[i].left;
                    buttons[i].text.setPosition(targets[i].left + 15, targets[i].top + 15);
                }
                delete[] targets;
                targets = nullptr;

                flags.flagAnimated = false;
                flags.flagPointableAndClickable = true;

                state = POPUP_BTN_NO_ENTRY_POINTED;

                sf::Vector2i pos = sf::Mouse::getPosition(win);
                sf::Event e;
                e.mouseMove.x = pos.x;
                e.mouseMove.y = pos.y;
                
                state = POPUP_BTN_NO_ENTRY_POINTED;
                break;
            }

            for(int i = 1; i < button_num; i++)
                buttons[i].borders.left = targets[i].left + (targets[i].left - buttons[i].borders.left) / animation_steps;

            animation_steps--;
            break;
        }

        default:
            break;
    }

    return NO_EVENT;
}

void PopUpButtonGroup::print(sf::RenderWindow& win){
    switch(state){
        case POPUP_BTN_COLLAPSED:
            buttons[0].print(win);
            break;

        default:
            for(int i = 1; i < button_num; i++)
                buttons[i].print(win);
            break;
    }
}