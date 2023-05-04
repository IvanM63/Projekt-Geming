#ifndef BASEGAME_H
#define BASEGAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <GL/glew.h>
#include <iostream>
#include "Setting.h"
#include "Shader.h"
#include "Quad.h"
#include "Input.h"
#include <GLM/gtc/matrix_transform.hpp>

using namespace std;

namespace Engine {
	enum class State {
		RUNNING,
		EXIT
	};

	class Game
	{
	public:
		Game(Setting* setting);
		~Game();
		void SetBackgroundColor(int r, int g, int b);
		void Run();
		SDL_Window* getWindows();
		unsigned int duration = 0;
		float deltaTime = 0;
		unsigned int lastTime = 0, numFrame = 0;
	
	protected:
		Setting* setting = NULL;
		State state;
		unsigned int currentFrameRate = 0;
		mat4 defaultProjection;
		Shader* defaultSpriteShader = NULL;
		Shader* defaultTextShader = NULL;
		Quad* defaultQuad = NULL;
		Input* inputManager = NULL;
		
		mat4 CreateDefaultProjection();
		Shader* CreateDefaultSpriteShader();
		Shader* CreateDefaultTextShader();
		float GetGameTime();

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;

		
	
	private:
		mat4 projection;
		float targetFrameTime = 16;
		SDL_Window* windowz;
		
		
		SDL_Window* InitInternal();
		void GameLoop(SDL_Window* window);
		void CalcDeltaTimeAndFramerate();
		void PollInput();
		int r = 255;
		int g = 0;
		int b = 0;
	};
}

#endif
