#pragma once

//Base Class Screen
#include "Screen.h"

//Daftar Screen
#include "ScreenMenu.h"
#include "ScreenGame.h"
#include "ScreenGameOver.h"

//Additional
#include "Game.h"
#include <vector>

using namespace std;


namespace Engine {

    enum class ScreenState {
        MAIN_MENU,
        IN_GAME,
        GAME_OVER
    };
   
    // Screen Manager class
    class ScreenManager {
    public:
        ScreenManager(Game* game);
        ~ScreenManager();

        void switchScreen(ScreenState state);

        void Init();
        void Update();
        void Render();

        
    private:
        Engine::Game* game = NULL;
        ScreenState screenState;

        //Screen List
        Screen* screenMenu = NULL;
        Screen* screenGame = NULL;
        Screen* screenGameOver = NULL;
        
    };


}

