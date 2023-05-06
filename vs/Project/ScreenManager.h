#pragma once

//Base Class Screen
#include "Screen.h"

//Daftar Screen
#include "ScreenMenu.h"
#include "ScreenGame.h"

//Additional
#include "Game.h"
#include <vector>

using namespace std;


namespace Engine {

    enum class ScreenState {
        MAIN_MENU,
        IN_GAME
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
        ScreenState screenState;

        //Screen List
        Screen* screenMenu = NULL;
        Screen* screenGame = NULL;
        
    };


}

