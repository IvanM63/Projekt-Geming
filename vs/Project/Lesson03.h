#ifndef LESSON03_H
#define LESSON03_H

#include "Projectile.h"
#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include <Windows.h>
#include <math.h>
#include "Button.h"
#include "Text.h"

#pragma comment(lib, "User32.lib") // Link against User32.lib

namespace Engine {
	enum class ScreenState {
		MAIN_MENU,
		IN_GAME
	};
	class Lesson03 :public Engine::Game
	{
	public:
		Lesson03(Setting* setting);
		~Lesson03();
		virtual void Init();
		virtual void Update();
		virtual void Render();
		
	private:
		int currentButtonIndex = 0;
		ScreenState screenState;
		vector<Button*> buttons;
		Text* text;

		void InitMainMenu();
		void InitInGame();
		void RenderMainMenu();
		void RenderInGame();
		void UpdateMainMenu();
		void UpdateInGame();


		Sprite* backgroundSprite = NULL;

		Engine::Texture* texture = NULL;
		Engine::Sprite* sprite = NULL;

		Engine::Texture* texture2 = NULL;
		Engine::Sprite* sprite2 = NULL;

		Engine::Texture* texture3 = NULL;
		Engine::Sprite* sprite3 = NULL;

		//Bullet Texture
		Engine::Texture* textureBullet = NULL;
		Engine::Sprite* spriteBullet = NULL;

		std::vector<Projectile*> projectiles;
		Engine::Projectile* proj = NULL;

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

		//Buat Bezier
		void bezierInit();
		void ShowOnWindow();

		float p0x = 100;
		float p0z = 360;

		float p1x = 1200;
		float p1z = 800;

		float p2x = 1200;
		float p2z = 0;

		float p3x = 100;
		float p3z = 360;



		float x = 0;
		float z = 0;

		float t = 0;

		float tempX = 0;
		float tempZ = 0;

		float posisiX[750];
		float posisiZ[750];

		int p = 0;

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

