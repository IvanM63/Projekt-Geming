#ifndef WAVE_H
#define WAVE_H

#include <Windows.h>
#include "Texture.h"
#include "Sprite.h"
#include "Text.h"
#include "Game.h"
#include "BaseCharacter.h"

#include "Enemy.h"

#include <iostream>
#include <random>

namespace Engine {

    class Enemy;

    class Wave {
    public:
        Wave(Game* game);
        ~Wave();

        void NextWave();
        void SpawnStart();
        void SpawnEnd();
        std::vector<Enemy*> SpawnEnemies();

        void RemoveEnemiesByOne(int i);

        //Setter & Getter
        bool GetSpawnStatus();
        int GetCurrentWave();

        //Basic Function
        //virtual void Init();
        void Update();
        //virtual void Render();

    protected:
        Engine::Game* game = NULL;

        //Sound Effect
        Sound* soundBrains = NULL;

        float x;
        int currentWave; //currentWave : wave, x : tambah 0.5 tiap 5n -> tiap lawan boss;
        int numEnemies;
        int enemiesLeft;
        int maxAvailEnemies;

        bool isSpawning = true;

        int enemyHealth;
        float enemySpeed;

        std::vector<Enemy*> enemiesWave;

        int waveTime = 0; //1000 per detik

        //UI SECTION
        Text* enemiesLeftText = NULL;
    };
}

#endif
