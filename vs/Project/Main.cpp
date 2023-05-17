#include "Main.h"

Engine::Main::Main(Setting* setting) :Engine::Game(setting)
{

}

Engine::Main::~Main()
{
	
}

void Engine::Main::Init()
{
	screenmanager->Init();
}


void Engine::Main::Update()
{

	screenmanager->Update();
	
}

void Engine::Main::Render()
{
	screenmanager->Render();
	
}


int main(int argc, char** argv) {

	Engine::Setting* setting = new Engine::Setting();
	setting->windowTitle = "Jombi-Jombian";
	setting->screenWidth = 1366;
	setting->screenHeight = 768;
	setting->windowFlag = Engine::WindowFlag::WINDOWED;
	setting->vsync = true;
	Engine::Game* game = new Engine::Main(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}

