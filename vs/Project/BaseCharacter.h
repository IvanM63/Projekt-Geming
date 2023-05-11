#ifndef BASECHARACTER_H
#define BASECHARACTER_H

#include <Windows.h>
#include "Texture.h"
#include "Sprite.h"

namespace Engine {

    class Game;

    class BaseCharacter {
    public:
        BaseCharacter(Game* game);
        ~BaseCharacter();

        //Basic Function
        virtual void Init();
        virtual void Update();
        virtual void Render();

        void attack();
        void takeDamage(int damage);

        //Setter Getter this variable
        void setHealth(int health);
        int getHealth();

        //Setter Getter Sprite-nya
        void SetRotation(float degree);
        void SetFlipVertical(bool tf);
        void SetFlipHorizontal(bool tf);
        void SetPosition(float x, float y);
        vec2 GetPosition();
        void move(vec2 location);

        //For Debuging purpose
        void setDebug(bool is);

        Engine::Texture* texture = NULL;
        Engine::Sprite* sprite = NULL;

    protected:
       
        Engine::Game* game = NULL;

        //Hitbox Debug
        bool isDebug;
        Texture* dotTexture = NULL;
        Sprite* dotSprite1 = NULL;
        Sprite* dotSprite2 = NULL;
        Sprite* dotSprite3 = NULL;
        Sprite* dotSprite4 = NULL;

        //This chara Stat
        int health;
        int damage;

    };
}

#endif



