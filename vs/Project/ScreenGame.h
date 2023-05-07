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

#include <set>
#include <queue>


namespace Engine {

	//Kalo di Base classnya ada include Game.h, harus forward Declaration di sini
	class Enemy;

	class Node {
	public:
		std::vector<Node*> neighbors;
		int x, y;

		Node(int _x, int _y) {
			x = _x;
			y = _y;
		}
	};

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

		//For Astar
		float distance(Node* a, Node* b);
		std::vector<Node*> AStar(Node* start, Node* goal);

	private:
		bool isPlayerMoving = false;

		float speedd = 0.05f;

		std::vector<Node*> nodes;

		Texture* dotTexture = NULL;
		Sprite* dotSprite1 = NULL;
		Sprite* dotSprite2 = NULL;
		Sprite* dotSprite3 = NULL;
		Sprite* dotSprite4 = NULL;

		int currentButtonIndex = 0;

		Sprite* backgroundSprite = NULL;

		//Player Sprite
		Engine::Texture* playerTex = NULL;
		Engine::Sprite* playerSprite = NULL;

		//Bullet Texture
		Engine::Texture* textureBullet = NULL;
		Engine::Sprite* spriteBullet = NULL;

		std::vector<Projectile*> projectiles;
		Projectile* proj = NULL;

		std::vector<Enemy*> enemies;
		Enemy* enemy = NULL;
		Enemy* enemy2 = NULL;

		//x = 980 y = 720

		float bulletSpeed = 10.5f;

		unsigned int duration = 0;
		unsigned int lastTime = 0, numFrame = 0;

		// Get the mouse position in screen coordinates
		POINT mousePos;

		vec2 characterOffSet = { 42, 18 };
		vec2 aimDirNow = { 0,0 };

	};

}

#endif


