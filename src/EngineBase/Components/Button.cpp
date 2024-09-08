#include "Button.hpp"
#include <SFML/Graphics/Color.hpp>

uint32_t Button::on_move(sf::Event& e){
    switch(state){
        case BTN_IDLE:
            if(isInRect(sf::Vector2i{e.mouseMove.x, e.mouseMove.y}, borders)){
                state = BTN_POINTED;
                return MOUSE_ENTRY;
            }
            break;

        case BTN_POINTED:
        case BTN_PRESSED:
            if(!isInRect(sf::Vector2i{e.mouseMove.x, e.mouseMove.y}, borders)){
                state = BTN_IDLE;
                return MOUSE_LEFT;
            }

        default:
            break;
    }

    return NO_EVENT;
}
uint32_t Button::on_click(sf::Event& e){
    state = BTN_PRESSED;
    return 0;
}    
uint32_t Button::on_release(sf::Event& e){
    state = isInRect(sf::Vector2i{e.mouseButton.x, e.mouseButton.y}, borders) ? BTN_POINTED : BTN_IDLE;
    return BUTTON_CLICK;
}

uint32_t Button::activate(){
    state = BTN_IDLE;
    return 0;
}
uint32_t Button::deactivate(){
    state = BTN_INACTIVE;
    return 0;
}

uint32_t Button::show(){
    state = BTN_INVISIBLE;
    return 0;
}

uint32_t Button::hide(){
    state = BTN_INVISIBLE;
    return 0;
}

void Button::print(sf::RenderWindow& win){
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(borders.width, borders.height));
    shape.setPosition(borders.left, borders.top);
    switch(state){
        case BTN_IDLE:
            shape.setFillColor(sf::Color(100, 250, 50));
            break;

        case BTN_PRESSED:
            shape.setFillColor(sf::Color(200, 200, 200));
            break;

        //case BTN_INVISIBLE:
        //case BTN_INACTIVE:

        case BTN_POINTED:
            shape.setFillColor(sf::Color(10, 25, 250));
            break;

        default:
            break;
    }
    win.draw(shape);
    if(!text.getString().isEmpty()) win.draw(text);
}