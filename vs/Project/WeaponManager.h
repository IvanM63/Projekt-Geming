#ifndef WEAPONMANAGER_H
#define WEAPONMANAGER_H

#include <Windows.h>
#include "Texture.h"
#include "Sprite.h"
#include "Sound.h"
#include "Text.h"
#include "Game.h"

//#include "Projectile.h"
#include "Player.h"
#include "Pistol.h"
#include "Rifle.h"

namespace Engine {

    //Semua Include yang di dalemnya ada Game.h harus di Forward Declaration di Sini..
    class Player;
    class Pistol;
    class Rifle;

    class WeaponManager {
    public:
        WeaponManager(Game* game, Player* player);
        ~WeaponManager();

        //Basic Function
        virtual void Init();
        virtual void Update();
        virtual void Render();

        void Fire(Weapon* weapon);
        void RenderAmmoText();

        //Weapon List
        std::vector<Weapon*> weapons;
        Pistol* pistol = NULL;
        Rifle* rifle = NULL;

        Weapon* activeWeapon = NULL;
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
        float rawAimAngle = 0;

        unsigned int duration = 0;

        // || USER INTERFACE SECTION || \\

        //Text Info
        Text* ammoText = NULL;
        Text* ammoText2 = NULL;

        //Crosshair
        Texture* textureCrosshair = NULL;
        Sprite* spriteCrosshair = NULL;

        //Reload Bar
        Texture* reloadTexture = NULL;
        std::vector<Sprite*> reloadSprites;
    };
}

#endif