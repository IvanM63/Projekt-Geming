#ifndef SCREENMENU_H
#define SCREENMENU_H

//Include Wajib
#include <Windows.h>
#include "Screen.h"
#include "Game.h"
#include "ScreenManager.h"

//Include Yang perlu perlu aja
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

		Engine::Texture* textureTitle = NULL;
		Engine::Sprite* spriteTitle = NULL;
	};

}

#endif


