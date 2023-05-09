#ifndef ENEMY_H
#define ENEMY_H

#include <Windows.h>
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"
#include "BaseCharacter.h"

namespace Engine {
    class Enemy : public BaseCharacter {
    public:
        Enemy(Game* game);
        ~Enemy();

        //Basic Function
        virtual void Init();
        virtual void Update();
        virtual void Render();
 
    protected:
        
    };
}

#endif



