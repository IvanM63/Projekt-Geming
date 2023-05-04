#ifndef LESSON02_H
#define LESSON01_H

#include "Game.h"
#include "Setting.h"

namespace Engine {
	class Lesson02 :public Engine::Game
	{
	public:
		Lesson02(Setting* setting);
		~Lesson02();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		float color_duration, f;
		int mul, r_y, g_y, b_y, r_p, g_p, b_p;
		int lerp(float a, float b, float f);
	};
}

#endif

