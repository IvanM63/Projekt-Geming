#ifndef LESSON05_H
#define LESSON05_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"

namespace Engine {
	class Lesson05 :public Engine::Game
	{
	public:
		Lesson05(Setting* setting);
		~Lesson05();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Engine::Texture* texture = NULL;
		Engine::Sprite* sprite = NULL;
	};
}

#endif

