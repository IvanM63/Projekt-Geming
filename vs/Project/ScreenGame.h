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


namespace Engine {

	//Kalo di Base classnya ada include Game.h, harus forward Declaration di sini
	class Enemy;

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

	private:
		Texture* dotTexture = NULL;
		Sprite* dotSprite1 = NULL;
		Sprite* dotSprite2 = NULL;
		Sprite* dotSprite3 = NULL;
		Sprite* dotSprite4 = NULL;

		int currentButtonIndex = 0;

		Sprite* backgroundSprite = NULL;

		Engine::Texture* texture = NULL;
		Engine::Sprite* sprite = NULL;

		Engine::Texture* texture2 = NULL;
		Engine::Sprite* sprite2 = NULL;

		//Bullet Texture
		Engine::Texture* textureBullet = NULL;
		Engine::Sprite* spriteBullet = NULL;

		std::vector<Projectile*> projectiles;
		Projectile* proj = NULL;

		std::vector<Enemy*> enemies;
		Enemy* enemy = NULL;
		Enemy* enemy2 = NULL;

		unsigned int duration = 0;
		unsigned int lastTime = 0, numFrame = 0;

		//SPEEED
		float posX = 0;
		float posY = 0;
		float direction = 1;
		float speed = 0.5;

		//Buat RGB
		int r = 255;
		int g = 0;
		int b = 0;

		//x = 980
		//y = 720


		//Jump Section
		bool isJumping = false;

		vec2 playerPos = { 0,0 };

		// Get the mouse position in screen coordinates
		POINT mousePos;

		float bulletSpeed = 10.5f;

		vec2 characterOffSet = { 42, 18 };
		vec2 aimDirNow = { 0,0 };

	};

}

#endif


