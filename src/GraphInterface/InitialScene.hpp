#pragma once

#include "../EngineBase/Scene.hpp"

#include "../EngineBase/Components/PopUpButtonGroup.hpp"
#include "../EngineBase/Components/Button.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cstdint>

#define NO_OBJECT UINT16_MAX

class InitialScene : public Scene{
	enum ResourceNames{
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
		POP_UP_NEW_GAME,
        POP_UP_CONTINUE,
		BTN_SETTINGS,
		BTN_EXIT,
		// UINT16_MAX = NO_OBJECT
	};

	PopUpButtonGroup grpStartGame;
	PopUpButtonGroup grpChooseSession;
	Button btnSettings;
	Button btnExit;

	sf::Font font;

public:
	InitialScene(int h, int w, const char* header);

	void resourceLoad();
	void resourceRelease();
};