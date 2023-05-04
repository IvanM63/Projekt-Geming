#include "Lesson01.h"

Engine::Lesson01::Lesson01(Setting* setting) :Engine::Game(setting)
{

}

Engine::Lesson01::~Lesson01()
{
}

void Engine::Lesson01::Init()
{
	r = 255;
	mul = 1;
}

void Engine::Lesson01::Update()
{
	if (color_duration >= 50) {
		/*if (r <= 0 || r >= 255) {
			mul *= -1;
		}*/
		//mul *= (r <= 0 || r >= 255) ? -1 : 1;
		//r += mul * 5;
		r += (mul *= (r <= 0 || r >= 255) ? -1 : 1) * 5;
		SetBackgroundColor(r, g, b);
		color_duration = 0;
	}
	color_duration += GetGameTime();
}

void Engine::Lesson01::Render()
{

}

//int main(int argc, char** argv) {
//	Engine::Setting* setting = new Engine::Setting();
//	setting->windowTitle = "Project Example";
//	setting->screenWidth = 640;
//	setting->screenHeight = 480;
//	setting->windowFlag = Engine::WindowFlag::WINDOWED;
//	setting->vsync = false;
//	setting->targetFrameRate = 0;
//	Engine::Game* game = new Engine::Lesson01(setting);
//	game->Run();
//	delete setting;
//	delete game;
//
//	return 0;
//}
