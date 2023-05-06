#include "Lesson03.h"

Engine::Lesson03::Lesson03(Setting* setting) :Engine::Game(setting)
{

}

Engine::Lesson03::~Lesson03()
{
	
}

void Engine::Lesson03::Init()
{
	screenmanager->Init();
}


void Engine::Lesson03::Update()
{

	screenmanager->Update();
	
}

void Engine::Lesson03::Render()
{
	screenmanager->Render();
	
}





int main(int argc, char** argv) {
	Engine::Setting* setting = new Engine::Setting();
	setting->windowTitle = "Jombi-Jombian";
	setting->screenWidth = 1366;
	setting->screenHeight = 768;
	setting->windowFlag = Engine::WindowFlag::WINDOWED;
	setting->vsync = false;
	setting->targetFrameRate = 0;
	Engine::Game* game = new Engine::Lesson03(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}

