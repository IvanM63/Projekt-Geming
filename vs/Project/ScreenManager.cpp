#include "ScreenManager.h"

Engine::ScreenManager::ScreenManager(Game* game)
{
	this->game = game;
	screenMenu = new ScreenMenu(game, this);
	screenGame = new ScreenGame(game, this);
	screenGameOver = new ScreenGameOver(game, this);
	screenHowToPlay = new ScreenHowToPlay(game, this);
	screenHowToPlay2 = new ScreenHowToPlay2(game, this);
	//Screen Awal Masuk game ganti di sini
	screenState = ScreenState::HOW_TO_PLAY2;
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
	else if (state == ScreenState::HOW_TO_PLAY) {
		screenHowToPlay = new ScreenHowToPlay(game, this);
		screenHowToPlay->Init();
	}
	else if (state == ScreenState::HOW_TO_PLAY2) {
		screenHowToPlay2 = new ScreenHowToPlay2(game, this);
		screenHowToPlay2->Init();
	}
	screenState = state;
}

void Engine::ScreenManager::Init()
{
	screenMenu->Init();
	screenGame->Init();
	screenGameOver->Init();
	screenHowToPlay->Init();
	screenHowToPlay2->Init();
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
	else if (screenState == ScreenState::HOW_TO_PLAY) {
		screenHowToPlay->Update();
	}
	else if (screenState == ScreenState::HOW_TO_PLAY2) {
		screenHowToPlay2->Update();
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
	else if (screenState == ScreenState::HOW_TO_PLAY) {
		screenHowToPlay->Render();
	}
	else if (screenState == ScreenState::HOW_TO_PLAY2) {
		screenHowToPlay2->Render();
	}
}


