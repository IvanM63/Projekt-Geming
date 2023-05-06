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
        //Enemy(int health, int damage);

        //Basic Function
        void Init();
        void Update();
        void Render();

        void attack();
        void takeDamage(int damage);
        int getHealth() const;
        bool isDead() const;

        //Setter Getter Sprite-nya
        void SetPosition(float x, float y);
        vec2 GetPosition();

        

    private:
        Engine::Game* game = NULL;
        Engine::Texture* texture = NULL;
        Engine::Sprite* sprite = NULL;

        int health;
        int damage;

        vec2 currentEnemyPos = { 0,0 };
    };
}

#endif



