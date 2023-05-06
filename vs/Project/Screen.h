#ifndef SCREEN_H
#define SCREEN_H

#include <Windows.h>


namespace Engine {
    //Base Class dari Screen harus ada Forward Declaration dari kelas Game
    class Game;
    class ScreenManager;

    class Screen {
    public:
        Screen(Game* game, ScreenManager* manager);
        ~Screen();

        virtual void Init();
        virtual void Update();
        virtual void Render();

        Engine::Game* game = NULL;
        ScreenManager* manager = NULL;
    };
}



#endif