#ifndef RIFLE_H
#define RIFLE_H

#include <Windows.h>
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"

#include "Weapon.h"
#include "Projectile.h"

namespace Engine {

	class Projectile;

	class Rifle : public Weapon {
	public:
		Rifle(Game* game);
		~Rifle();

		//Basic Function
		void Init();
		void Update();
		void Render();

		//Basic Function for Projectile
		void UpdateProjectiles();
		void RenderProjectiles();

		//Setter Getter Projectile
		int GetProjectilesSize();
		void RemoveProjectileByIndex(int i);
		BoundingBox* GetProjectileBoundingBoxByIndex(int i);
		vec2 GetProjectilePositionByIndex(int i);

		//Funtion for Shooting Mechanic
		void Fire(vec2 playerPos, vec2 aimDir, float angleNoNegative);
		void Reload();

	protected:
		Engine::Game* game = NULL;

		//Bullet Texture
		Engine::Texture* textureBullet = NULL;
		Engine::Sprite* spriteBullet = NULL;

		std::vector<Projectile*> projectiles; 
		Projectile* projectile = NULL;
		float bulletSpeed = 18.5f;

		unsigned int duration = 0;
		bool isReload = false;
		int currentReloadTime;

	};
}


#endif
