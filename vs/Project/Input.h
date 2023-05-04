#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <iostream>
#include <SDL/SDL.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <unordered_map>

using namespace std;
using namespace glm;

namespace Engine {
	class Input
	{
	public:
		bool IsKeyPressed(string name);
		bool IsKeyReleased(string name);
		vec2 GetMouseCoords();
		void PressKey(unsigned int keyID);
		void ReleaseKey(unsigned int keyID);
		void SetMouseCoords(float x, float y);
		void OpenGameController();
		void CloseGameController();
		void AddInputMapping(string mappingName, unsigned int keyId);
		void Reset();
	
	private:
		vec2 mouseCoords;
		SDL_GameController* controller;
		unordered_map<unsigned int, string> keyCodeNameMap;
		unordered_map<string, bool> pressedKeyMap;
		vector<string> releasedKeys;
	};
}

#endif
