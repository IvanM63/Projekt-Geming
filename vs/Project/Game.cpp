#include "Game.h"


using namespace Engine;

Game::Game(Setting* setting)
{
	this->setting = setting;
}

Game::~Game()
{
	delete inputManager;
	delete defaultQuad;
	delete defaultSpriteShader;
	delete defaultTextShader;
}

void Engine::Game::SetBackgroundColor(int r, int g, int b)
{
	glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}


void Game::Run()
{
	SDL_Window* window = InitInternal();
	Init();
	//SetBackgroundColor(255, 105, 180);
	GameLoop(window);
	SDL_Quit();
}

SDL_Window* Engine::Game::getWindows()
{
	return windowz;
}


mat4 Game::CreateDefaultProjection()
{
	return ortho(0.0f, static_cast<GLfloat>(setting->screenWidth), 0.0f, static_cast<GLfloat>(setting->screenHeight), -1.0f, 1.0f);
}

Shader* Engine::Game::CreateDefaultSpriteShader()
{
	Shader* defaultShader = new Shader("sprite.vert", "sprite.frag");
	defaultShader->Use();
	defaultShader->setMat4(defaultProjection, "projection");
	return defaultShader;
}

Shader* Engine::Game::CreateDefaultTextShader()
{
	Shader* defaultShader = new Shader("text.vert", "text.frag");
	defaultShader->Use();
	defaultShader->setMat4(defaultProjection, "projection");
	return defaultShader;
}

float Engine::Game::GetGameTime()
{
	return deltaTime;
}

SDL_Window* Game::InitInternal()
{
	//Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//Tell SDL that we want a double buffered window so we don't get any flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if (setting->targetFrameRate > 0) {
		targetFrameTime = 1000.0f / setting->targetFrameRate;
	}

	// Setup window mode
	Uint32 flags = SDL_WINDOW_OPENGL;

	if (WindowFlag::EXCLUSIVE_FULLSCREEN == setting->windowFlag) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	if (WindowFlag::FULLSCREEN == setting->windowFlag) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	if (WindowFlag::BORDERLESS == setting->windowFlag) {
		flags |= SDL_WINDOW_BORDERLESS;
	}

	// Setup SDL Window
	SDL_Window* window = SDL_CreateWindow(setting->windowTitle.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		setting->screenWidth, setting->screenHeight, flags);
	
	SDL_GetWindowSize(window, &setting->screenWidth, &setting->screenHeight);
	
	//cbcb
	windowz = window;


	if (window == nullptr) {
		throw "Failed to create a window.";
	}

	//Set up our OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr) {
		throw "Failed to setup OpenGL context.";
	}

	//Set up glew (optional but recommended)
	GLenum glewStat = glewInit();
	if (glewStat != GLEW_OK) {
		throw "Failed to setup OpenGL extension.";
	}

	//Set VSYNC
	SDL_GL_SetSwapInterval(setting->vsync);

	// Init Audio
	int audioFlags = MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_OGG;
	if (audioFlags != Mix_Init(audioFlags)) {
		throw ("Unable to initialize mixer: " + string(Mix_GetError()));
	}
	int audio_rate = 22050; Uint16 audio_format = AUDIO_S16SYS; int audio_channels = 2; int audio_buffers = 4096;
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		throw ("Unable to initialize audio: " + string(Mix_GetError()));
	}

	defaultProjection = CreateDefaultProjection();
	defaultSpriteShader = CreateDefaultSpriteShader();
	defaultTextShader = CreateDefaultTextShader();
	defaultQuad = new Quad();
	inputManager = new Input();

	return window;
}

void Game::GameLoop(SDL_Window* window)
{
	state = State::RUNNING;

	//Will loop until we set Game State to EXIT
	while (State::RUNNING == state) {
		// Polling input
		PollInput();
		// Update World
		Update();
		
		//Setting Viewport
		glViewport(0, 0, setting->screenWidth, setting->screenHeight);
		//Clear the color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Render World
		Render();
		// Double-buffering
		SDL_GL_SwapWindow(window);
		// Limit the FPS to the max FPS
		SDL_Delay((Uint32)(targetFrameTime));
		// Compute delta time and framerate
		CalcDeltaTimeAndFramerate();
		
	}

}

void Game::CalcDeltaTimeAndFramerate() {
	unsigned int time = SDL_GetTicks();
	unsigned delta = time - lastTime;
	lastTime = time;

	if (duration >= 1000) {
		currentFrameRate = numFrame;
		numFrame = 0;
		duration = 0;
		cout << "FPS: " << currentFrameRate << endl;
	}

	numFrame++;
	duration += delta;

	deltaTime = delta * setting->timeScale;

}

void Game::PollInput()
{
	SDL_Event evt;
	inputManager->Reset();
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evt)) {
		switch (evt.type) {
		case SDL_QUIT:
			state = State::EXIT;
			break;
		case SDL_MOUSEMOTION:
			inputManager->SetMouseCoords((float)evt.motion.x, (float)evt.motion.y);
			break;
		case SDL_KEYDOWN:
			inputManager->PressKey(evt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			inputManager->ReleaseKey(evt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			inputManager->PressKey(evt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			inputManager->ReleaseKey(evt.button.button);
			break;
		case SDL_CONTROLLERDEVICEADDED:
			inputManager->OpenGameController();
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			inputManager->CloseGameController();
			break;
		case SDL_CONTROLLERBUTTONDOWN:
			inputManager->PressKey(evt.cbutton.button);
			break;
		case SDL_CONTROLLERBUTTONUP:
			inputManager->ReleaseKey(evt.cbutton.button);
			break;
		}
	}
}


