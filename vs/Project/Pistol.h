#ifndef PISTOL_H
#define PISTOL_H

#include <Windows.h>
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"

namespace Engine {

	class Pistol {
	public:
		Pistol(Game* game);
		~Pistol();

		//Basic Function
		void Init();
		void Update();
		void Render();

	protected:
		Engine::Game* game = NULL;

		//Basic Stat
		int totalAmmo, currentAmmo;
		int reloadTime;
		int fireRate;
		int damage;

		//Pistol Texture and Sprite
		Engine::Texture* texturePistol = NULL;
		Engine::Sprite* spritePistol = NULL;

		float bulletSpeed = 10.5f;
	};
}


#endif
