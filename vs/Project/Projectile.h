#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"
#include <Windows.h>
#include <math.h>

namespace Engine {
	class Projectile {
	public:
		vec2 position;
		vec2 direction;
		vec2 currVelo;
		float speed;

		Engine::Sprite* sprite = NULL;

		Projectile(Engine::Sprite* spriteBullet, Game* game) {
			this->game = game;
			this->sprite = spriteBullet;
			currVelo = { 0,0 };
		}

		void setCurrVelo(float x, float y) {
			currVelo = { x,y };
		}

		vec2 getCurrVelo() {
			return currVelo;
		}
	private:
		Engine::Game* game = NULL;
	};
}


#endif
