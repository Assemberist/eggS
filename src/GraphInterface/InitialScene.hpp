#pragma once

#include "../EngineBase/Scene.hpp"

#include "../EngineBase/Components/Sprite.hpp"
#include "../EngineBase/Components/PopUpButtonGroup.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cstdint>

#define NO_OBJECT UINT16_MAX

class InitialScene : public Scene{
	enum ResourceNames{
		Texture_Gabi,
		Font_Arial
	};

	enum SceneState{
		LEFT_HOLD,
		IDLE,
		DRAG,
		MENU
	};

protected:
	sf::Sprite* my_sp;
	uint32_t on_move(sf::Event& e);
	uint32_t on_click(sf::Event& e);
	uint32_t on_release(sf::Event& e);

	uint16_t pointedObject;
	uint16_t dragTarget;

	//bool dragFlag;

// Interface components
	enum InitialSceneComponentId{
		//GRP_START_GAME,
		//GRP_CHOOSE_SESSION,
		SPR_GABI,
		BTN_SETTINGS,
		BTN_EXIT,
		// UINT16_MAX = NO_OBJECT
	};

	//PopUpButtonGroup grpStartGame;
	//PopUpButtonGroup grpChooseSession;
	Button btnSettings;
	Button btnExit;
	Sprite sprGabi;

	sf::Font font;

public:
	InitialScene(int h, int w, const char* header);

	void resourceLoad();
	void resourceRelease();
};