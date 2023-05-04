#ifndef LESSON06_H
#define LESSON06_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "GameObject.h"
#include <vector>

namespace Engine {
	class Lesson06 :public Engine::Game
	{
	public:
		Lesson06(Setting* setting);
		~Lesson06();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Engine::Texture* texture = NULL;
		Engine::Sprite* CreateSprite();
		void SpawnObjects();
		vector<Engine::GameObject*> objects;
		float spawnDuration = 0, maxSpawnTime = 0, numObjectsInPool = 0, numObjectPerSpawn = 0;
	};
}

#endif

