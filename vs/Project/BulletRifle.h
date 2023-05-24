#ifndef BULLETRIFLE_H
#define BULLETRIFLE_H

#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"
#include "BaseBullet.h"

#include <Windows.h>
#include <math.h>

namespace Engine {
	class BulletRifle: public BaseBullet {
	public:
		BulletRifle(Game* game);

		//Basic Function
		void Init();
		void Update();
		void Render();

		//Setter Getter for it's Sprite
		void SetPosition(float x, float y);
		vec2 GetPosition();

		void BulletHit();

		BoundingBox* GetBoundingBox();

		void setCurrVelo(float x, float y);
		vec2 getCurrVelo();
		Engine::Sprite* spriteBullet = NULL;

	private:
		Engine::Game* game = NULL;

		vec2 position;
		vec2 direction;
		vec2 currVelo;
		float speed;

		//Bullet Texture
		Engine::Texture* textureBullet = NULL;
		
	};
}


#endif
