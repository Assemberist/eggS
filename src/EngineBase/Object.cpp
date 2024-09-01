#include "Object.hpp"

bool isInRect(sf::Vector2i dot, sf::IntRect& rect){
    return  dot.x >= rect.left && dot.x <= rect.left + rect.height &&
            dot.y >= rect.top && dot.y <= rect.top + rect.height;
}