#ifndef WEAPON_H
#define WEAPON_H

#include <Windows.h>
#include "Texture.h"
#include "Sprite.h"
#include "Sound.h"
#include "Text.h"
#include "Game.h"

#include "Projectile.h"
#include "Player.h"
#include "Pistol.h"

namespace Engine {

    //Semua Include yang di dalemnya ada Game.h harus di Forward Declaration di Sini..
    class Player;
    class Pistol;

    class Weapon {
    public:
        Weapon(Game* game, Player* player);
        ~Weapon();

        //Basic Function
        virtual void Init();
        virtual void Update();
        virtual void Render();

        void Fire();

        //Weapon List
        Pistol* pistol = NULL;
    protected:
        Engine::Game* game = NULL;
        
        //Player Attach
        Player* player = NULL;
        vec2 playerPos = { 0,0 };

        //Pistol Sound
        Sound* sound = NULL;

        //Hitbox Debug
        bool isDebug;
        Texture* dotTexture = NULL;
        Sprite* dotSprite1 = NULL;
        Sprite* dotSprite2 = NULL;
        Sprite* dotSprite3 = NULL;
        Sprite* dotSprite4 = NULL;

        // Get the mouse position in screen coordinates
        POINT mousePos;

        vec2 characterOffSet = { 42, 18 };
        float aimAngle = 0;

        unsigned int duration = 0;

        //Text Info
        Text* ammoText = NULL;
    };
}

#endif