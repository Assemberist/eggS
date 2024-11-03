#pragma once

#include <SFML/Graphics/Rect.hpp>
#include "../Object.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdint>

struct Label : public Object{
    sf::Vector2f pos;
    sf::Text text;

    Label(){
        flags.flagPrintable = true;
        text.setString("");
    }

    uint32_t show();
    uint32_t hide();

    ObjectType getType(){ return LABEL; }

    void print(sf::RenderWindow& win){
        win.draw(text);
    }
};