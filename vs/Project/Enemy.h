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

        //Seter getter 
        void SetDirection(float x, float y);
        vec2 GetDirection();
        void SetSpeed(float speed);
        float GetSpeed();
        void SetVelocity(float x, float y);
        vec2 GetVelocity();

        //MOVE FUNCTION
        void MoveWithVelocity();

        //Bounding Box Stuff
        BoundingBox* GetBoundingBox();
        vec2 GetBoundingBoxCenterPoint();

        //Behaviour
        int GetDamage();

    protected:
        //PERJALANAN MUSUH
        vec2 velocity = { 0,0 };
        vec2 direction = { 0,0 };
        float speed = 0.05f;

        //ENEMY STAT
        int damage = 10;
        int fireRate = 500;
        int currentFireRate = fireRate;    
    };
}

#endif



