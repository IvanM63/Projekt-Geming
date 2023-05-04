#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Sprite.h"

namespace Engine {
	enum class GameObjectState {
		SPAWN,
		GROUND,
		DIE
	};
	class GameObject
	{
	public:
		GameObject(Sprite* sprite);
		~GameObject();
		void Update(float deltaTime);
		void Draw();
		void SetPosition(float x, float y);
		void SetSpawn();
		float GetWidth();
		float GetHeight();
		bool IsDie();
		float GetX();
		float GetY();
	protected:
		Sprite* sprite = NULL;
		GameObjectState state;
		float groundDur = 0, groundTime = 0, x = 0, y = 0;
	};

}

#endif