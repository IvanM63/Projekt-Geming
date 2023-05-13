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

#include <set>
#include <queue>

namespace Engine {

	//Kalo di Base classnya ada include Game.h, harus forward Declaration di sini
	class Enemy;
	class Player;
	class WeaponManager;

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

		//Impulse Resoulution
		void resolveCollision(Enemy* enemy1, Enemy* enemy2, float restitution);
		float calculatePenetrationDepth(BoundingBox* box1, BoundingBox* box2, vec2 collisionNormal);

	private:
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


