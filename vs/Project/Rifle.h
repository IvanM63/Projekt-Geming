#ifndef RIFLE_H
#define RIFLE_H

#include <Windows.h>
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"

#include "Weapon.h"
#include "BulletRifle.h"

namespace Engine {

	class BulletRifle;

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
		void Fire(vec2 playerPos, vec2 aimDir, float angleNoNegative, float rawAimAngle);
		void Reload();

	protected:
		Engine::Game* game = NULL;

		//Bullet Texture
		Engine::Texture* textureBullet = NULL;
		Engine::Sprite* spriteBullet = NULL;

		std::vector<BulletRifle*> projectiles; 
		BulletRifle* projectile = NULL;
		float bulletSpeed = 20.0f;

		unsigned int duration = 0;
		bool isReload = false;
		int currentReloadTime;

	};
}


#endif