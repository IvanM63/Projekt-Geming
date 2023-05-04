#include "Lesson06.h"

Engine::Lesson06::Lesson06(Setting* setting) :Engine::Game(setting)
{

}

Engine::Lesson06::~Lesson06()
{
	delete texture;
}

void Engine::Lesson06::Init()
{
	// Spawn setting
	maxSpawnTime = 300;
	numObjectPerSpawn = 1;
	numObjectsInPool = 100;

	// Load a texture
	texture = new Texture("turtles.png");
	for (int i = 0; i < numObjectsInPool; i++) {
		GameObject* o = new GameObject(CreateSprite());
		objects.push_back(o);
	}
	// Set background
	SetBackgroundColor(235, 229, 52);

	// Add input
	inputManager->AddInputMapping("quit", SDLK_ESCAPE);
}

void Engine::Lesson06::Update()
{
	if (inputManager->IsKeyReleased("quit")) {
		state = Engine::State::EXIT;
	}
	// Time to spawn objects
	if (spawnDuration >= maxSpawnTime) {
		SpawnObjects();
		spawnDuration = 0;
	}
	// Update all objects
	for (GameObject* o : objects) {
		o->Update(GetGameTime());
	}
	// Count spawn duration
	spawnDuration += GetGameTime();
}

void Engine::Lesson06::Render()
{
	// Render all objects
	for (GameObject* o : objects) {
		o->Draw();
	}
}

/*
* Helper method to create a custom sprite
*/
Engine::Sprite* Engine::Lesson06::CreateSprite()
{
	Sprite* sprite = new Sprite(texture,
		defaultSpriteShader,
		defaultQuad);
	sprite->SetNumXFrames(14);
	sprite->SetNumYFrames(4);
	sprite->AddAnimation("hit", 2, 4);
	sprite->AddAnimation("spikes", 5, 12);
	sprite->AddAnimation("idle-1", 14, 27);
	sprite->AddAnimation("idle-2", 28, 41);
	sprite->AddAnimation("spikes-out", 42, 49);
	sprite->PlayAnim("idle-1");
	sprite->SetScale(1.5);
	sprite->SetAnimationDuration(100);

	return sprite;
}

void Engine::Lesson06::SpawnObjects()
{
	//Find Die object to reuse for spawning
	int spawnCount = 0;
	for (GameObject* o : objects) {
		if (spawnCount == numObjectPerSpawn) {
			break;
		}
		if (o->IsDie()) {
			// Set state to spawn
			o->SetSpawn();
			// Random spawn position
			int min = 0;
			int max = setting->screenWidth - o->GetWidth();
			float x = rand() % (max - min + 1) + min;
			float y = setting->screenHeight + o->GetHeight();
			o->SetPosition(x, y);
			spawnCount++;
		}
	}
}


//int main(int argc, char** argv) {
//	Engine::Setting* setting = new Engine::Setting();
//	setting->windowTitle = "Spawn Demo";
//	setting->screenWidth = 1024;
//	setting->screenHeight = 768;
//	setting->windowFlag = Engine::WindowFlag::FULLSCREEN;
//	setting->vsync = false;
//	setting->targetFrameRate = 0;
//	Engine::Game* game = new Engine::Lesson06(setting);
//	game->Run();
//	delete setting;
//	delete game;
//
//	return 0;
//}


