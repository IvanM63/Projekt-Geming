#ifndef SCREENGAME_H
#define SCREENGAME_H

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
#include "Music.h"

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

	class ScreenGame : public Screen {
	public:
		ScreenGame(Game* game, ScreenManager* manager);
		~ScreenGame();

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

	private:
		//Music
		Music* bgm = NULL;

		//Sound Effect
		Sound* soundAmmoPickUp = NULL;
		Sound* soundHitBullet = NULL;
		Sound* soundHitChara = NULL;

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

		//RedScreen
		Texture* redTexture = NULL;
		Sprite* redSprite = NULL;
		int currentRedCounter = 0;
		bool isRedScreen = false;
		
		int currentRedCounter2 = 0;
		bool isRedScreen2 = false;

		Texture* redTexture2 = NULL;
		Sprite* redSprite2 = NULL;

		//Currency
		int score = 0;

		//Wave System
		Wave* wave = NULL;

		//Ammo Drop
		std::vector<Ammo*> ammos;

		//Bullet Impact
		std::vector<Sprite*> bulletImpacts;
		Engine::Texture* textureImpact = NULL;
		Engine::Sprite* spriteImpact = NULL;
		float impactAnimTime = 100;

		//UI SECTION
		Engine::Texture* textureHP = NULL;
		Engine::Sprite* spriteHP = NULL;
		Engine::Texture* textureHPbar = NULL;
		Engine::Sprite* spriteHPbar = NULL;
		Text* enemiesLeftText = NULL;
		Text* waveText = NULL;
		Text* coinText = NULL;
		//Text* ammoText = NULL;

		Engine::Texture* borderHP = NULL;
		Engine::Sprite* border2HP = NULL;
		Engine::Texture* border = NULL;
		Engine::Sprite* borderwave = NULL;
		Engine::Sprite* borderscore = NULL;
		Engine::Sprite* borderammo = NULL;
		Engine::Texture* texturegunUI = NULL;
		Engine::Sprite* spritegunUI = NULL;

		//Projectile* projectile = NULL;
		//Tes ting
		int Bx = 21;
		int By = 12;

		int squareX;
		int squareY;

		int objectX;
		int objectY;

		//Weapon Objek
		WeaponManager* weapon = NULL;

		//Player Object TESTING
		Player* player = NULL;

		bool isPlayerMoving = false;

		float speedd = 0.05f;

		Texture* enemiesTexture = NULL;

		Texture* dotTexture = NULL;
		Sprite* dotSprite1 = NULL;
		Sprite* dotSprite2 = NULL;
		Sprite* dotSprite3 = NULL;
		Sprite* dotSprite4 = NULL;

		int currentButtonIndex = 0;

		Sprite* backgroundSprite = NULL;
		Sprite* borderBawah = NULL;
		Sprite* borderAtas = NULL;

		//Bullet Texture
		Engine::Texture* textureBullet = NULL;
		Engine::Sprite* spriteBullet = NULL;

		std::vector<Projectile*> projectiles;
		Projectile* proj = NULL;

		std::vector<Enemy*> enemies;


		//x = 980 y = 720

		float bulletSpeed = 10.5f;

		unsigned int duration = 0;
		unsigned int lastTime = 0, numFrame = 0;

		// Get the mouse position in screen coordinates
		//POINT mousePos;

		vec2 characterOffSet = { 42, 18 };
		vec2 aimDirNow = { 0,0 };

	};

}

#endif


