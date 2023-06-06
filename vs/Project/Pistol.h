#ifndef PISTOL_H
#define PISTOL_H

#include <Windows.h>
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"

#include "Weapon.h"
#include "Projectile.h"

namespace Engine {

	class Projectile;

	class Pistol: public Weapon {
	public:
		Pistol(Game* game);
		~Pistol();

		//Basic Function
		void Init();
		void Update();
		void Render();

		void SetPositionToPlayer(vec2 playerPos);
		void SetRotation(float rawAimAngle);

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

		std::vector<Projectile*> projectiles;
		Projectile* projectile = NULL;
		float bulletSpeed = 9.5f;

		unsigned int duration = 0;

		int fireAnimTime = 400;

	};
}


#endif
