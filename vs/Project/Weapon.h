#ifndef WEAPON_H
#define WEAPON_H

#include <Windows.h>
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"
#include "Projectile.h"
#include "Player.h"


namespace Engine {

    class Player;

    class Weapon {
    public:
        Weapon(Game* game, Player* player);
        ~Weapon();

        //Basic Function
        virtual void Init();
        virtual void Update();
        virtual void Render();

        void Fire();

        //Projectile Setter Getter
        int GetProjectilesSize();
        void RemoveProjectileByIndex(int i);
        BoundingBox* GetProjectileBoundingBoxByIndex(int i);

        Engine::Texture* texture = NULL;
        Engine::Sprite* sprite = NULL;

    protected:
        Engine::Game* game = NULL;
        Player* player = NULL;

        int totalAmmo, currentAmmo;
        int reloadTime;
        int fireRate;
        int damage;

        //Bullet Texture
        Engine::Texture* textureBullet = NULL;
        Engine::Sprite* spriteBullet = NULL;

        std::vector<Projectile*> projectiles;
        Projectile* proj = NULL;
        float bulletSpeed = 10.5f;

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
        vec2 aimDirNow = { 0,0 };

        unsigned int duration = 0;

    };
}

#endif