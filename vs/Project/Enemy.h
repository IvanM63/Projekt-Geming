#ifndef ENEMY_H
#define ENEMY_H

#include <Windows.h>
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"

namespace Engine {
    class Enemy {
    public:
        Enemy(Game* game);
        ~Enemy();

        //Basic Function
        void Init();
        void Update();
        void Render();

        void attack();
        void takeDamage(int damage);
        bool isDead() const;

        //Setter Getter Sprite-nya
        void SetPosition(float x, float y);
        vec2 GetPosition();

        int getHealth();

        
        Engine::Sprite* sprite = NULL;

    private:
        Texture* dotTexture = NULL;

        Engine::Game* game = NULL;
        Engine::Texture* texture = NULL;

        Sprite* dotSprite1 = NULL;
        Sprite* dotSprite2 = NULL;
        Sprite* dotSprite3 = NULL;
        Sprite* dotSprite4 = NULL;

        int health;
        int damage;

        vec2 currentEnemyPos = { 0,0 };
    };
}

#endif



