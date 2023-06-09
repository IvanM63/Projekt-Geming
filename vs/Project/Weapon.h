#ifndef WEAPON_H
#define WEAPON_H

#include <Windows.h>
#include "Texture.h"
#include "Sprite.h"

#include <iostream>
#include <iomanip>

namespace Engine {

	class Game;

	class Weapon {
	public:
		Weapon(Game* game);
		~Weapon();

		//Basic Function
		virtual void Init();
		virtual void Update();
		virtual void Render();

		//Setter Getter
		int GetDamage();

		//Basic Function for Projectile
		virtual void UpdateProjectiles();
		virtual void RenderProjectiles();

		//Setter Getter for its own Sprite (Weapon Sprite)
		void SetPosition(float x, float y);
		virtual void SetPositionToPlayer(vec2 playerPos);
		virtual void SetRotation(float degree);
		void SetFlipVertical(bool tf);

		//Setter Getter Ammo
		int GetCurrentAmmo();
		int GetTotalAmmo();
		void AddTotalAmmo(int ammo);

		virtual int GetProjectilesSize();
		virtual BoundingBox* GetProjectileBoundingBoxByIndex(int i);
		virtual vec2 GetProjectilePositionByIndex(int i);
		virtual void RemoveProjectileByIndex(int i);

		//Funtion for Shooting Mechanic
		void ReduceBulletInChamberByOne();
		virtual void Fire(vec2 playerPos, vec2 aimDir, float angleNoNegative, float rawAimAngle);
		
		//Reload
		bool isReload = false;
		float reloadPercentage = 0.0f;
		float currentReloadTime;
		float reloadTime;
	protected:
		Engine::Game* game = NULL;

		//Basic Stat
		int totalAmmo, currentAmmo;
		int fireRate;
		int damage;

		//Accuracy Purpose
		float accuracy = 0.0f; //0 Perfect, 1 Inaccurate
		float MAX_ACCURACY_OFFSET = 0.2f; //to 0.2 to represent a maximum deviation of 20% of the total distance

		//Pistol Texture and Sprite
		Engine::Texture* textureWeapon = NULL;
		Engine::Sprite* spriteWeapon = NULL;
		
		//Reload
		
		
	};
}


#endif