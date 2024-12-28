#include "InitialScene.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <cstdint>

static std::vector<Object*>* SceneObjects;
static std::vector<Resource>* SceneStuff;

InitialScene::InitialScene(int h, int w, const char* header){
	sf::VideoMode mod(h, w);
	screen.create(mod, header, sf::Style::Close);
	pointedObject = NO_OBJECT;
	//screen.setFramerateLimit(60);

	resourceLoad();

	objects.resize(4);

	grpStartGame.borders = {250, 50, 100, 60};
	grpStartGame.buttons = new Button[4];
	for(int i = 0; i < 4; i++){
		grpStartGame.buttons[i].borders = {250, 50, 100, 60};
		grpStartGame.buttons[i].text.setFont(*resources[Font_Arial].font);
        grpStartGame.buttons[i].text.setCharacterSize(18);
		grpStartGame.buttons[i].text.setFillColor(sf::Color(0,0,0));
	}
	grpStartGame.buttons[0].text.setString("New gaem");
	grpStartGame.buttons[0].text.setPosition(265, 65);
	grpStartGame.buttons[1].text.setString("Share PC");
	grpStartGame.buttons[2].text.setString("Local net");
	grpStartGame.buttons[3].text.setString("Internet");
	grpStartGame.button_num = 4;
	objects[POP_UP_NEW_GAME] = &grpStartGame;

	grpChooseSession.borders = {250, 130, 100, 60};
	grpChooseSession.buttons = new Button[3];
	for(int i = 0; i < 3; i++){
		grpChooseSession.buttons[i].borders = {250, 130, 100, 60};
		grpChooseSession.buttons[i].text.setFont(*resources[Font_Arial].font);
        grpChooseSession.buttons[i].text.setCharacterSize(18);
		grpChooseSession.buttons[i].text.setFillColor(sf::Color(0,0,0));
	}
	grpChooseSession.buttons[0].text.setString("Continue");
	grpChooseSession.buttons[0].text.setPosition(265, 145);
	grpChooseSession.buttons[1].text.setString("Load game");
	grpChooseSession.buttons[2].text.setString("Connect\nsession");
	grpChooseSession.button_num = 3;
	objects[POP_UP_CONTINUE] = &grpChooseSession;

	btnSettings.borders = {250, 210, 100, 60};
	btnSettings.state = BTN_IDLE;
	btnSettings.text.setFont(*resources[Font_Arial].font);
    btnSettings.text.setCharacterSize(18);
	btnSettings.text.setFillColor(sf::Color(0,0,0));
	btnSettings.text.setString("Settings");
	btnSettings.text.setPosition(265, 225);
	objects[BTN_SETTINGS] = &btnSettings;

	btnExit.borders = {250, 290, 100, 60};
	btnExit.state = BTN_IDLE;
	btnExit.text.setFont(*resources[Font_Arial].font);
    btnExit.text.setCharacterSize(18);
	btnExit.text.setFillColor(sf::Color(0,0,0));
	btnExit.text.setString("Exit");
	btnExit.text.setPosition(265, 305);
	objects[BTN_EXIT] = &btnExit;

	SceneObjects = &objects;
	SceneStuff = &resources;
}

void InitialScene::resourceLoad(){
	resources.resize(1);
	resources[Font_Arial].font = &font;
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
		if(objects[pointedObject]->isPointableAndClickable()){
			uint32_t result = objects[pointedObject]->on_release(e);
			if(result == BUTTON_CLICK){
				switch(objects[pointedObject]->getType()){
					case BUTTON:
						printf("Button #%d\n", pointedObject);
						break;

					case POPUP_BUTTON_GROUP:
						printf("Button #%d from group\n", ((PopUpButtonGroup*)(objects[pointedObject]))->get_pointed_btn_id());
						break;

					default:
						break;
				}
			}
			return result;
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