#ifndef MAIN_H
#define MAIN_H


#include "Game.h"
#include "Setting.h"
#include <Windows.h>
#include <math.h>

#pragma comment(lib, "User32.lib") // Link against User32.lib

namespace Engine {
	class Main :public Engine::Game
	{
	public:
		Main(Setting* setting);
		~Main();
		void Init();
		void Update();
		void Render();
		
	private:

	};
	
}

#endif

