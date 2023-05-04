#include "Lesson07.h"

Engine::Lesson07::Lesson07(Setting* setting) :Engine::Game(setting)
{
	// Set to mainmenu
	screenState = Engine::ScreenState::MAIN_MENU;
	text = nullptr;
}

Engine::Lesson07::~Lesson07()
{
}

void Engine::Lesson07::Init()
{
	InitMainMenu();
	InitInGame();
}

void Engine::Lesson07::Update()
{

	if (Engine::ScreenState::MAIN_MENU == screenState) {
		UpdateMainMenu();
	}
	else if (Engine::ScreenState::IN_GAME == screenState) {
		UpdateInGame();
	}
}

void Engine::Lesson07::Render()
{
	if (Engine::ScreenState::MAIN_MENU == screenState) {
		RenderMainMenu();
	}
	else if (Engine::ScreenState::IN_GAME == screenState) {
		RenderInGame();
	}
}

void Engine::Lesson07::InitMainMenu()
{
	// Create a Texture
	Texture* texture = new Texture("buttons.png");

	// Create Sprites
	Sprite* playSprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	playSprite->SetNumXFrames(6);
	playSprite->SetNumYFrames(1);
	playSprite->AddAnimation("normal", 5, 5);
	playSprite->AddAnimation("hover", 3, 4);
	playSprite->AddAnimation("press", 3, 4);
	playSprite->SetAnimationDuration(400);

	Sprite* exitSprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	exitSprite->SetNumXFrames(6);
	exitSprite->SetNumYFrames(1);
	exitSprite->AddAnimation("normal", 2, 2);
	exitSprite->AddAnimation("hover", 0, 1);
	exitSprite->AddAnimation("press", 0, 1);
	exitSprite->SetAnimationDuration(400);

	//Create Buttons
	Button* playButton = new Button(playSprite, "play");
	playButton->SetPosition((setting->screenWidth / 2) - (playSprite->GetScaleWidth() / 2),
		400);
	buttons.push_back(playButton);
	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition((setting->screenWidth / 2) - (exitSprite->GetScaleWidth() / 2),
		250);
	buttons.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Create Text
	text = new Text("8-bit Arcade In.ttf", 100, defaultTextShader);
	text->SetText("The Spawning Turtle");
	text->SetPosition(60, setting->screenHeight - 100);
	text->SetColor(235, 229, 52);

	// Add input mappings
	inputManager->AddInputMapping("next", SDLK_DOWN);
	inputManager->AddInputMapping("prev", SDLK_UP);
	inputManager->AddInputMapping("press", SDLK_RETURN);

}

void Engine::Lesson07::InitInGame()
{
	// Spawn setting
	maxSpawnTime = 300;
	numObjectPerSpawn = 1;
	numObjectsInPool = 50;

	// Load a texture
	Texture* texture = new Texture("turtles.png");
	for (int i = 0; i < numObjectsInPool; i++) {
		GameObject* o = new GameObject(CreateSprite(texture));
		objects.push_back(o);
	}

	// Add input mappings
	inputManager->AddInputMapping("mainmenu", SDLK_ESCAPE);
}

void Engine::Lesson07::RenderMainMenu()
{
	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
	// Render title 
	text->Draw();
}

void Engine::Lesson07::RenderInGame()
{
	// Render all objects
	for (GameObject* o : objects) {
		o->Draw();
	}
}

void Engine::Lesson07::UpdateMainMenu()
{
	// Set background
	SetBackgroundColor(52, 155, 235);

	if (inputManager->IsKeyReleased("next")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Next Button
		currentButtonIndex = currentButtonIndex < buttons.size() - 1 ? currentButtonIndex + 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (inputManager->IsKeyReleased("prev")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Prev Button
		currentButtonIndex = currentButtonIndex > 0 ? currentButtonIndex - 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}


	if (inputManager->IsKeyReleased("press")) {
		// Set current button to press state
		Button* b = buttons[currentButtonIndex];
		b->SetButtonState(Engine::ButtonState::PRESS);
		// If play button then go to InGame, exit button then exit
		if ("play" == b->GetButtonName()) {
			screenState = Engine::ScreenState::IN_GAME;
		}
		else if ("exit" == b->GetButtonName()) {
			state = Engine::State::EXIT;
		}
	}

	// Update All buttons
	for (Button* b : buttons) {
		b->Update(GetGameTime());
	}
}

void Engine::Lesson07::UpdateInGame()
{
	// Back to main menu
	if (inputManager->IsKeyReleased("mainmenu")) {
		screenState = Engine::ScreenState::MAIN_MENU;
	}

	// Set background
	SetBackgroundColor(235, 229, 52);

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

Engine::Sprite* Engine::Lesson07::CreateSprite(Texture* texture)
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
	sprite->PlayAnim("spikes");
	sprite->SetScale(1.5);
	sprite->SetAnimationDuration(100);

	return sprite;
}

void Engine::Lesson07::SpawnObjects()
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
//	setting->windowTitle = "GUI Demo";
//	setting->screenWidth = 1024;
//	setting->screenHeight = 768;
//	setting->windowFlag = Engine::WindowFlag::EXCLUSIVE_FULLSCREEN;
//	setting->vsync = false;
//	setting->targetFrameRate = 0;
//	Engine::Game* game = new Engine::Lesson07(setting);
//	game->Run();
//	delete setting;
//	delete game;
//
//	return 0;
//}


