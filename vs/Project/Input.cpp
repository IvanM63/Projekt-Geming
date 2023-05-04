#include "Input.h"

using namespace Engine;

bool Input::IsKeyPressed(string name)
{
	auto it = pressedKeyMap.find(name);
	if (it != pressedKeyMap.end()) {
		// Found the key
		return it->second;
	}
	// Didn't find the key
	return false;
}

bool Input::IsKeyReleased(string name)
{
	for (auto& val : releasedKeys) // access by reference to avoid copying
	{
		if (val == name)
		{
			return true;
		}
	}
	// Didn't find
	return false;
}

vec2 Input::GetMouseCoords()
{
	return this->mouseCoords;
}

void Input::AddInputMapping(string mapName, unsigned int keyId)
{
	keyCodeNameMap.insert(pair<unsigned int, string>(keyId, mapName));
}

void Engine::Input::Reset()
{
	releasedKeys.clear();
}

void Input::PressKey(unsigned int keyID)
{
	// Here we are treating _keyMap as an associative array.
	// if keyID doesn't already exist in _keyMap, it will get added
	auto it = keyCodeNameMap.find(keyID);
	if (it != keyCodeNameMap.end()) {
		string mapName = it->second;
		pressedKeyMap[mapName] = true;
		return;
	}
}

void Input::ReleaseKey(unsigned int keyID)
{
	auto it = keyCodeNameMap.find(keyID);
	if (it != keyCodeNameMap.end()) {
		string mapName = it->second;
		pressedKeyMap[mapName] = false;
		releasedKeys.push_back(mapName);
	}
}

void Input::SetMouseCoords(float x, float y)
{
	mouseCoords.x = x;
	mouseCoords.y = y;
}

void Input::OpenGameController()
{
	if (SDL_NumJoysticks() > 0) {
		if (SDL_IsGameController(0))
		{
			controller = SDL_GameControllerOpen(0);
			if (controller != nullptr)
				cout << "Game Controller is Detected" << endl;
		}
	}
}

void Input::CloseGameController()
{
	if (controller != nullptr) {
		SDL_GameControllerClose(0);
		cout << "Game Controller is Removed" << endl;
	}
}
