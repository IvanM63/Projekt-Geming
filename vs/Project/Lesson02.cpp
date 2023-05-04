#include "Lesson02.h"

Engine::Lesson02::Lesson02(Setting* setting) :Engine::Game(setting)
{

}

Engine::Lesson02::~Lesson02()
{
}

void Engine::Lesson02::Init()
{
	// Yellow
	r_y = 255;
	g_y = 255;
	b_y = 0;
	// Purple
	r_p = 157;
	g_p = 3;
	b_p = 255;
	// Set mul to 1
	mul = -1;
	// Set f to 0
	f = 0.0f;
}

void Engine::Lesson02::Update()
{
	if (color_duration >= 50.0f) {
		f += (mul *= (f <= 0.0f || f >= 1.0f) ? -1 : 1) * 0.02f;
		SetBackgroundColor(lerp(r_y, r_p, f), 
			lerp(g_y, g_p, f), 
			lerp(b_y, b_p, f));
		color_duration = 0;
	}
	color_duration += GetGameTime();
}

void Engine::Lesson02::Render()
{

}

int Engine::Lesson02::lerp(float a, float b, float f)
{
	return (int)((1 - f) * a + f * b);
}
/*
int main(int argc, char** argv) {
	Engine::Setting* setting = new Engine::Setting();
	setting->windowTitle = "Lerp Demo";
	setting->screenWidth = 1024;
	setting->screenHeight = 768;
	setting->windowFlag = Engine::WindowFlag::WINDOWED;
	setting->vsync = false;
	setting->targetFrameRate = 0;
	Engine::Game* game = new Engine::Lesson02(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}*/
