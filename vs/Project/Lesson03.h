#ifndef LESSON03_H
#define LESSON03_H


#include "Game.h"
#include "Setting.h"
#include <Windows.h>
#include <math.h>
#



#pragma comment(lib, "User32.lib") // Link against User32.lib

namespace Engine {
	class Lesson03 :public Engine::Game
	{
	public:
		Lesson03(Setting* setting);
		~Lesson03();
		void Init();
		void Update();
		void Render();
		
	private:

	};
	
}

#endif

