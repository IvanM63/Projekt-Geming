#include "Testosteron.h"



Testosteron::Testosteron(Engine::Setting* setting) : Game(setting)
{

}

void Testosteron::Init()
{
}

void Testosteron::Update()
{
	//ganti biru
	if (duration >= 50) {
		if (r == 255) {
			r = 0;
			b = 255;
		}
		else if (b == 255) {
			b = 0;
			g = 255;
		}
		else if (g == 255) {
			g = 0;
			r = 255;
		}
		duration = 0;
	}

	SetBackgroundColor(r, g, b);
}

void Testosteron::Render()
{
}

//int main(int argc, char** argv) {
//	Engine::Setting* setting = new Engine::Setting();
//	setting->windowTitle = "Platform Jump";
//	setting->screenWidth = 1366;
//	setting->screenHeight = 768;
//	setting->windowFlag = Engine::WindowFlag::WINDOWED;
//	setting->vsync = true;
//
//	Engine::Game* game = new Testosteron(setting);
//	//game->SetBackgroundColor(255, 105, 180);
//	game->Run();
//	
//	delete setting;
//	delete game;
//
//	return 0;
//}
