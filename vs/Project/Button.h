#ifndef BUTTON_H
#define BUTTON_H

#include "Sprite.h"

namespace Engine {
	enum class ButtonState {
		PRESS,
		HOVER,
		NORMAL
	};
	class Button
	{
	public:
		Button(Sprite* sprite, string name);
		~Button();
		void Update(float deltaTime);
		void Draw();
		void SetPosition(float x, float y);
		vec2 GetPosition();
		ButtonState GetButtonState();
		void SetButtonState(ButtonState state);
		string GetButtonName();
	private:
		ButtonState state;
		Sprite* sprite;
		string name;
	};
}

#endif