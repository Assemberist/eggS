#include "InitialScene.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <cstdint>

std::vector<Object*>* SceneObjects;
std::vector<Resource>* SceneStuff;

InitialScene::InitialScene(int h, int w, const char* header){
	sf::VideoMode mod(h, w);
	screen.create(mod, header, sf::Style::Close);
	pointedObject = NO_OBJECT;
	//screen.setFramerateLimit(60);

	resourceLoad();

	objects.resize(5);

	btnSettings.borders = {10, 10, 100, 100};
	btnSettings.state = BTN_IDLE;
	btnSettings.text.setFont(*resources[Font_Arial].font);
	btnSettings.text.setFillColor(sf::Color(0,0,0));
	btnSettings.text.setString("Settings");
	btnSettings.text.setPosition(15, 15);
	objects[BTN_SETTINGS] = &btnSettings;

	btnExit.borders = {120, 100, 100, 100};
	btnExit.state = BTN_IDLE;
	btnExit.text.setFont(*resources[Font_Arial].font);
	btnExit.text.setFillColor(sf::Color(0,0,0));
	btnExit.text.setString("Exit");
	btnExit.text.setPosition(135, 115);
	objects[BTN_EXIT] = &btnExit;

	sprGabi.sprite.setTexture(*resources[Texture_Gabi].texture);
	objects[SPR_GABI] = &sprGabi;

	lbl.text.setFont(*resources[Font_Arial].font);
	lbl.text.setPosition({200, 15});
	lbl.text.setString("Pidaras!!!\nPI-DA-RA-SI-NA!!!");
	lbl.text.setFillColor({255, 0, 255});
	objects[LABEL_SHIT] = &lbl;

	grp.borders = {200, 200, 100, 60};
	grp.animation_steps = 20;
	grp.buttons = new Button[4];
	for(int i = 0; i < 4; i++){
		grp.buttons[i].borders = {200, 200, 100, 60};
		grp.buttons[i].text.setFont(*resources[Font_Arial].font);
		grp.buttons[i].text.setFillColor(sf::Color(0,0,0));
	}
	grp.buttons[0].text.setString("Init");
	grp.buttons[0].text.setPosition(210, 210);
	grp.buttons[1].text.setString("One");
	grp.buttons[2].text.setString("Two");
	grp.buttons[3].text.setString("Three");
	grp.button_num = 4;
	objects[POP_UP_GRP] = &grp;

	SceneObjects = &objects;
	SceneStuff = &resources;
}

void InitialScene::resourceLoad(){
	resources.resize(2);
	resources[Texture_Gabi].texture = new sf::Texture();
	resources[Texture_Gabi].texture->loadFromFile("resource/gabi.png");
	resources[Font_Arial].font = new sf::Font();
	resources[Font_Arial].font->loadFromFile("resource/arial.ttf");
}

void InitialScene::resourceRelease(){

}

uint32_t InitialScene::on_click(sf::Event& e){
	if(pointedObject != NO_OBJECT){
		switch(objects[pointedObject]->on_click(e)){
			case BUTTON_CLICK:
			default:
				break;
		}
	}
	return 0;	
}

uint32_t InitialScene::on_release(sf::Event& e){
	//dragFlag = false;
	if(pointedObject != NO_OBJECT){
		switch(objects[pointedObject]->getType()){
			case BUTTON:
				switch(((Button*)objects[pointedObject])->on_release(e)){
					case BUTTON_CLICK:
					default:
						break;
				}
			default:
				break;
		}		
	}
	return 0;
}

uint32_t InitialScene::on_move(sf::Event& e){
	if(pointedObject != NO_OBJECT){
		switch((objects[pointedObject])->on_move(e)){
			case ANIMATION_START:
			case MOUSE_LEFT:
				pointedObject = NO_OBJECT;
				break;
			default:
				return 0;
		}		
	}
	for(size_t i = 0; i<objects.size(); i++){
		if(objects[i]->isPointableAndClickable()){
			switch(objects[i]->on_move(e)){
				case MOUSE_ENTRY:
					pointedObject = i;
					break;

				case MOUSE_LEFT:
					pointedObject = NO_OBJECT;
			}
		}
	}
	return 0;
}