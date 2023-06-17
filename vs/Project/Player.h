#ifndef PLAYER_H
#define PLAYER_H

#include <Windows.h>
#include "Texture.h"
#include "Sprite.h"
#include "Text.h"
#include "Game.h"
#include "BaseCharacter.h"

namespace Engine {
    class Player: public BaseCharacter {
    public:
        Player(Game* game);
        ~Player();

        //Basic Function
        virtual void Init();
        virtual void Update();
        virtual void Render();


    protected:
        Text* healthText = NULL;

        //Invs
        bool isInvs = false;
        int invsTime, currentInvsTime;
    };
}

#endif
