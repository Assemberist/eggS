#include "InitialScene.hpp"
#include <cstdint>

std::vector<Object*>* SceneObjects;
std::vector<Resource>* SceneStuff;

InitialScene::InitialScene(int h, int w, const char* header){
	sf::VideoMode mod(h, w);
	screen.create(mod, header, sf::Style::Close);
	pointedObject = NO_OBJECT;
	//screen.setFramerateLimit(60);

	resourceLoad();

	btnSettings.borders = {10, 10, 100, 100};
	btnSettings.state = BTN_IDLE;
	btnSettings.text.setString("Settings");
	btnSettings.text.setPosition(15, 15);
	btnExit.borders = {120, 100, 100, 100};
	btnExit.state = BTN_IDLE;
	btnExit.text.setString("Exit");
	btnExit.text.setPosition(135, 115);
	sprGabi.sprite.setTexture(*resources[Texture_Gabi].texture);

	objects.resize(3);
	objects[BTN_SETTINGS] = &btnSettings;
	objects[BTN_EXIT] = &btnExit;
	objects[SPR_GABI] = &sprGabi;

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
		switch(objects[pointedObject]->getType()){
			case BUTTON:
				switch(((Button*)objects[pointedObject])->on_click(e)){
					case BUTTON_CLICK:
					default:
						break;
				}
			case SPRITE:
			case POPUP_BUTTON_GROUP:
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
			case SPRITE:
			case POPUP_BUTTON_GROUP:
				break;
		}		
	}
	return 0;
}

uint32_t InitialScene::on_move(sf::Event& e){
	if(pointedObject != NO_OBJECT){
		switch(((Button*)objects[pointedObject])->on_move(e)){
			default:
				break;
			case MOUSE_LEFT:
				pointedObject = NO_OBJECT;
		}		
	}
	for(size_t i = 0; i<objects.size(); i++){
		switch(objects[i]->getType()){
			case BUTTON:
				switch(((Button*)objects[i])->on_move(e)){
					case MOUSE_ENTRY:
						pointedObject = i;
						break;

					case MOUSE_LEFT:
						pointedObject = NO_OBJECT;
				}
			case POPUP_BUTTON_GROUP:
			case SPRITE:
				break;
		}
	}
	return 0;
}