#ifndef BASEBULLET_H
#define BASEBULLET_H

#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include <Windows.h>
#include <math.h>

namespace Engine {

	class Game;

	class BaseBullet {
	public:
		BaseBullet(Game* game);

		//Basic Function
		virtual void Init();
		virtual void Update();
		virtual void Render();

		//Setter Getter for it's Sprite
		void SetPosition(float x, float y);
		vec2 GetPosition();

		void BulletHit();

		BoundingBox* GetBoundingBox();

		void setCurrVelo(float x, float y);
		vec2 getCurrVelo();

		//Bullet Impact
		Engine::Texture* textureImpact = NULL;
		Engine::Sprite* spriteImpact = NULL;
	private:
		Engine::Game* game = NULL;

		vec2 position;
		vec2 direction;
		vec2 currVelo;
		float speed;

		//Bullet Texture
		Engine::Texture* textureBullet = NULL;
		Engine::Sprite* spriteBullet = NULL;

	protected:
		bool isHit = false;
	};
}


#endif
