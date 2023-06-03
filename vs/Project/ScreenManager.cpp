#include "ScreenManager.h"

Engine::ScreenManager::ScreenManager(Game* game)
{
	this->game = game;
	screenMenu = new ScreenMenu(game, this);
	screenGame = new ScreenGame(game, this);
	screenGameOver = new ScreenGameOver(game, this);

	//Screen Awal Masuk game ganti di sini
	screenState = ScreenState::MAIN_MENU;
}

Engine::ScreenManager::~ScreenManager()
{
}

void Engine::ScreenManager::switchScreen(ScreenState state)
{
	if (state == ScreenState::MAIN_MENU) {
		screenMenu = new ScreenMenu(game, this);
		screenMenu->Init();
	}
	else if (state == ScreenState::IN_GAME) {
		screenGame = new ScreenGame(game, this);
		screenGame->Init();
	}
	else if (state == ScreenState::GAME_OVER) {
		screenGameOver = new ScreenGameOver(game, this);
		screenGameOver->Init();
	}
	screenState = state;
}

void Engine::ScreenManager::Init()
{
	screenMenu->Init();
	screenGame->Init();
	screenGameOver->Init();
	
}

void Engine::ScreenManager::Update()
{

	if (screenState == ScreenState::MAIN_MENU) {
		screenMenu->Update();
	}
	else if (screenState == ScreenState::IN_GAME) {
		screenGame->Update();
	}
	else if (screenState == ScreenState::GAME_OVER) {
		screenGameOver->Update();
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
	else if (screenState == ScreenState::GAME_OVER) {
		screenGameOver->Render();
	}

}


