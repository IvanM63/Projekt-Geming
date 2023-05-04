#ifndef LESSON01_H
#define LESSON01_H

#include "Game.h"
#include "Setting.h"

namespace Engine {
	class Lesson01 :public Engine::Game
	{
	public:
		Lesson01(Setting* setting);
		~Lesson01();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		float color_duration;
		int r, g, b;
		int mul;
	};
}

#endif

