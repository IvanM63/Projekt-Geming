#ifndef SCREENMENU_H
#define SCREENMENU_H

//Include Wajib
#include <Windows.h>
#include "Screen.h"
#include "Game.h"
#include "ScreenManager.h"

//Include Yang perlu perlu aja
#include "Music.h"
#include "Sound.h"
#include "Button.h"
#include "Text.h"
#include "GameObject.h"

namespace Engine {


	class ScreenMenu : public Screen {
	public:
		ScreenMenu(Game* game, ScreenManager* manager);
		~ScreenMenu();

		void Init();
		void Update();
		void Render();

	private:
		int currentButtonIndex = 0;
		vector<Button*> buttons;
		Text* text;
		Text* textoutline;

		Button* b = NULL;

		bool isFirstInit = false;

		//Music
		Music* bgm = NULL;

		//Sound Effect
		Sound* soundSelection = NULL;
		Sound* soundComplete = NULL;
		Sound* soundConfirm = NULL;

		//Switch Screen Purpose
		Engine::Texture* textureTitle = NULL;
		Engine::Sprite* spriteTitle = NULL;

		Engine::Texture* textureIn = NULL;
		Engine::Sprite* spriteIn = NULL;
		
		Engine::Texture* textureOut = NULL;
		Engine::Sprite* spriteOut = NULL;

		Engine::Texture* texturekuru = NULL;
		Engine::Sprite* spritekuru = NULL;

		Engine::Texture* texturejombi = NULL;
		Engine::Sprite* spritejombi = NULL;
		Engine::Sprite* spritejombi2 = NULL;
		Engine::Sprite* spritejombi3 = NULL;

		int currentSwitchTime = 0;
		bool isSwitching = false;
	};

}

#endif


