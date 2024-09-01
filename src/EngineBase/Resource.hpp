#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>

/*enum ResourceType{
	TEXTURE,
	SOUND,
    MUSIC
};*/

union Resource{
    sf::Sound* sound;
    sf::Texture* texture;
    sf::Font* font;
};

