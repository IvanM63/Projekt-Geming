#include "ScreenManager.h"

Engine::ScreenManager::ScreenManager(Game* game)
{
	screenMenu = new ScreenMenu(game, this);
	screenGame = new ScreenGame(game, this);

	//Screen Awal Masuk game ganti di sini
	screenState = ScreenState::IN_GAME;
}

Engine::ScreenManager::~ScreenManager()
{
}

void Engine::ScreenManager::switchScreen(ScreenState state)
{
	screenState = state;
}

void Engine::ScreenManager::Init()
{
	screenMenu->Init();
	screenGame->Init();
	
}

void Engine::ScreenManager::Update()
{

	if (screenState == ScreenState::MAIN_MENU) {
		screenMenu->Update();
	}
	else if (screenState == ScreenState::IN_GAME) {
		screenGame->Update();
	}

}

void Engine::ScreenManager::Render()
{

	if (screenState == ScreenState::MAIN_MENU) {
		screenMenu->Render();
	}
	else if (screenState == ScreenState::IN_GAME) {
		screenGame->Render();
	}

}


