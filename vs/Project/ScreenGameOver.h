#ifndef SCREENGAMEOVER_H
#define SCREENGAMEOVER_H

//Include Wajib
#include <Windows.h>
#include "Screen.h"
#include "Game.h"

//Include yg perlu perlu aja
#include "Texture.h"
#include "Sprite.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Player.h"
#include "WeaponManager.h"
#include "Wave.h"
#include "Button.h"
#include <set>
#include <queue>
#include <thread>

namespace Engine {

	//Kalo di Base classnya ada include Game.h, harus forward Declaration di sini
	class Enemy;
	class Player;
	class WeaponManager;
	class Wave;

	class ScreenGameOver : public Screen {
	public:
		ScreenGameOver(Game* game, ScreenManager* manager);
		~ScreenGameOver();

		//Override Function
		void Init();
		void Update();
		void Render();

	private:
		Texture* ghostTexture = NULL;
		Sprite* ghostSprite = NULL;

		Texture* whiteTexture = NULL;
		Sprite* whiteSprite = NULL;
		int whiteCounter = 0;

		//Text GameOVer
		Text* gameText = NULL;
		Text* overText = NULL;
		//Text Score
		Text* scoreText = NULL;
		
		//Button Selection
		int currentButtonIndex = 0;
		vector<Button*> buttons;
	};

}

#endif


