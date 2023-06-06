#ifndef AMMO_H
#define AMMO_H

#include <Windows.h>
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"

#include <iostream>
#include <iomanip>

namespace Engine {

	class Game;

	class Ammo {
	public:
		Ammo(Game* game);
		~Ammo();

		//Basic Function
		void Init();
		void Update();
		void Render();

		//Setter Getter
		void SetPosition(float x, float y);
		int GetAmount();

		Engine::Sprite* spriteAmmo = NULL;
	protected:
		Engine::Game* game = NULL;

		//Pistol Texture and Sprite
		Engine::Texture* textureAmmo = NULL;
		

		//Ammo Stat
		int amount;

	};
}


#endif