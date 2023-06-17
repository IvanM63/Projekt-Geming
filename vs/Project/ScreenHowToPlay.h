#ifndef SCREENHOWTOPLAY_H
#define SCREENHOWTOPLAY_H

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

	class ScreenHowToPlay : public Screen {
	public:
		ScreenHowToPlay(Game* game, ScreenManager* manager);
		~ScreenHowToPlay();

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

		//UI SECTION
			int currentButtonIndex = 0;
			vector<Button*> buttons;

			Button* b = NULL;

			Texture* howtoplayButton = NULL;
			Sprite* MainMenuSprite = NULL;
			Sprite* NextSprite = NULL;
			Sprite* PrevSprite = NULL;
			Sprite* HowToPlaySprite = NULL;

		bool isPlayerMoving = false;

		Texture* enemiesTexture = NULL;

		Sprite* backgroundSprite = NULL;

		unsigned int duration = 0;
		unsigned int lastTime = 0, numFrame = 0;

		//HowToPlay1 move
			Texture* Player1 = NULL;
			Sprite* Player1Sprite = NULL;
			Texture* KeyBoardMove = NULL;
			Sprite* KeyBoardMoveSprite = NULL;
			int currentloop = 0;
			float gametime1;

		//HowToPlay2 aim n shoot

			Texture* Mouse = NULL;
			Sprite* MouseSprite = NULL;

			Sprite* player2sprite = NULL;
			Sprite* pistol2Sprite = NULL;

			float gametime2;
			//Bullet Texture
			Engine::Texture* textureBullet = NULL;
			Engine::Sprite* spriteBullet = NULL;

			std::vector<Projectile*> projectiles;
			Projectile* proj = NULL;

			float bulletSpeed = 10.5f;

			//Bullet Impact
			std::vector<Sprite*> bulletImpacts;
			Engine::Texture* textureImpact = NULL;
			Engine::Sprite* spriteImpact = NULL;
			float impactAnimTime = 100;

		//HowToPlay3 switch
			//Weapon Objek
			Sprite* player3sprite = NULL;
			Texture* pistol3 = NULL;
			Sprite* pistol3Sprite = NULL;
			Texture* rifle3 = NULL;
			Sprite* rifle3Sprite = NULL;
			int currentweapon = 1;
			float gametime3;

			//keyboard
			Texture* KeyBoardSwitch = NULL;
			Sprite* KeyBoardSwitchSprite = NULL;
	};

}

#endif


