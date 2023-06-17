#ifndef SCREENHOWTOPLAY_H2
#define SCREENHOWTOPLAY_H2

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
#include "Ammo.h"
#include "Sound.h"

#include <set>
#include <queue>
#include <thread>

namespace Engine {

	//Kalo di Base classnya ada include Game.h, harus forward Declaration di sini
	class Enemy;
	class Player;
	class WeaponManager;
	class Wave;
	class Ammo;

	class ScreenHowToPlay2 : public Screen {
	public:
		ScreenHowToPlay2(Game* game, ScreenManager* manager);
		~ScreenHowToPlay2();

		//Override Function
		void Init();
		void Update();
		void Render();

		//Another Function
		void forDebug();

		//AVOID COLLISION
		void avoidCollision(Enemy* collidingEnemy, Enemy* otherEnemy);

		//Randomly Return Boolean
		bool getRandomBoolean(double truePercentage);

		//Impulse Resoulution
		void resolveCollision(Enemy* enemy1, Enemy* enemy2, float restitution);
		float calculatePenetrationDepth(BoundingBox* box1, BoundingBox* box2, vec2 collisionNormal);

		int currentpage = 1;
	private:
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

		int currentSwitchTime = 0;
		bool isSwitching = true;
		string screenName = "";
		int currentloop;
		int duration = 0;

		//UI SECTION
		int currentButtonIndex = 0;
		vector<Button*> buttons;

		Button* b = NULL;

		Texture* howtoplayButton = NULL;
		Sprite* MainMenuSprite = NULL;
		Sprite* NextSprite = NULL;
		Sprite* PrevSprite = NULL;
		Sprite* HowToPlaySprite = NULL;

		Texture* Player1 = NULL;
		Texture* pistol3 = NULL;
		Texture* rifle3 = NULL;
		
		//HowToPlay4 reload

		//keyboard
		std::vector<Sprite*> ReloadSprite;
		Texture* Reload = NULL;
		Sprite* player4sprite = NULL;
		Sprite* rifle4Sprite = NULL;
		Texture* KeyBoardReload = NULL;
		Sprite* KeyBoardReloadSprite = NULL;
		float gametime4;
		float reloadtime4;
		boolean isReload = true;

		////HowToPlay5 damage

		Sprite* player5sprite = NULL;
		Sprite* enemy5sprite = NULL;
		Texture* enemy = NULL;
		float gametime5;
		float isHittime5;
		boolean isHit = false;
		int health = 100;
		float currentHitCounter;
		Engine::Texture* textureHPbar = NULL;
		Engine::Sprite* spriteHPbar = NULL;

		//HowToPlay6 ammo

		Texture* ammo = NULL;
		Sprite* ammo6sprite = NULL;
		Sprite* enemy6sprite = NULL;
		float gametime6;
		boolean isDrop = false;
	};

}

#endif

#pragma once
