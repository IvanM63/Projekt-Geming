#include "Lesson03.h"

Engine::Lesson03::Lesson03(Setting* setting) :Engine::Game(setting)
{

}

Engine::Lesson03::~Lesson03()
{
	delete texture;
	delete sprite;
}

void Engine::Lesson03::Init()
{

	InitMainMenu();
	InitInGame();

	
}

void Engine::Lesson03::bezierInit() {

	int segmentCount = 750;

	//rumus bezier curve jika empat waypoint

	for (int i = 0; i < segmentCount; i++) {
		t = (float)i / segmentCount;
		x = ((1 - t) * (1 - t) * (1 - t) * p0x) + (3 * (1 - t) * (1 - t) * t * p1x) + (3 * (1 - t) * (1 - t) * t * t * p2x) + (t * t * t * p3x);
		z = ((1 - t) * (1 - t) * (1 - t) * p0z) + (3 * (1 - t) * (1 - t) * t * p1z) + (3 * (1 - t) * (1 - t) * t * t * p2z) + (t * t * t * p3z);

		posisiX[i] = x;
		posisiZ[i] = z;

		//std::cout << posisiX[i];
		//std::cout << " ";
		//std::cout << posisiZ[i];
	}
}

void Engine::Lesson03::Update()
{

	if (Engine::ScreenState::MAIN_MENU == screenState) {
		UpdateMainMenu();
	}
	else if (Engine::ScreenState::IN_GAME == screenState) {
		UpdateInGame();
	}
	

}

void Engine::Lesson03::Render()
{
	
	if (Engine::ScreenState::MAIN_MENU == screenState) {
		RenderMainMenu();
	}
	else if (Engine::ScreenState::IN_GAME == screenState) {
		RenderInGame();
	}
	
	
}


void Engine::Lesson03::InitMainMenu()
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

void Engine::Lesson03::InitInGame()
{

	texture = new Texture("flying_eye.png");
	sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);

	texture3 = new Texture("Warrior_Sheet-Effect.png");
	sprite3 = new Sprite(texture3, defaultSpriteShader, defaultQuad);

	//sprite2
	texture2 = new Texture("turtles.png");
	sprite2 = new Sprite(texture2, defaultSpriteShader, defaultQuad);

	//Bullet Sprite
	textureBullet = new Texture("bullet.png");




	//Create background
	Texture* bgTexture = new Texture("0.png");
	backgroundSprite = new Sprite(bgTexture, defaultSpriteShader, defaultQuad);
	backgroundSprite->SetSize(setting->screenWidth, setting->screenHeight);


	sprite->SetNumXFrames(6);
	sprite->SetNumYFrames(1);
	sprite->AddAnimation("moving", 1, 6);

	sprite->PlayAnim("moving");
	sprite->SetScale(2);
	sprite->SetAnimationDuration(100);


	//sprite3
	sprite3->SetNumXFrames(6);
	sprite3->SetNumYFrames(17);
	sprite3->AddAnimation("moving", 6, 13);

	sprite3->PlayAnim("moving");
	sprite3->SetScale(2);
	sprite3->SetAnimationDuration(100);

	sprite3->SetPosition(0, 0);


	//TEst
	sprite->SetFlipHorizontal(false);
	//x = 980
	//y = 720

	sprite2->SetNumXFrames(14);
	sprite2->SetNumYFrames(4);
	sprite2->AddAnimation("spikes-out", 42, 49);

	sprite2->AddAnimation("walk", 28, 41);
	sprite2->SetScale(2);
	sprite2->SetAnimationDuration(175);
	sprite2->SetPosition(0, 0);
	//sprite2->SetFlipHorizontal(true);


	//___________Input Manajer_______________//

	//Wolk Lef
	inputManager->AddInputMapping("walk-left", SDLK_LEFT);
	inputManager->AddInputMapping("walk-left", SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	inputManager->AddInputMapping("walk-left", SDL_CONTROLLER_AXIS_LEFTX);
	inputManager->AddInputMapping("walk-left", SDLK_a);
	//Wolk righ
	inputManager->AddInputMapping("walk-right", SDLK_RIGHT);
	inputManager->AddInputMapping("walk-right", SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	inputManager->AddInputMapping("walk-right", SDLK_d);
	//Wolk up
	inputManager->AddInputMapping("walk-up", SDLK_w);
	//Wolk don
	inputManager->AddInputMapping("walk-down", SDLK_s);
	//Quit
	inputManager->AddInputMapping("Quit", SDLK_ESCAPE);
	inputManager->AddInputMapping("Quit", SDL_CONTROLLER_BUTTON_Y);
	//fire
	inputManager->AddInputMapping("Fire", SDL_BUTTON_LEFT);


	//Set the background color
	SetBackgroundColor(102, 195, 242);

	//bezier
	bezierInit();

}

void Engine::Lesson03::RenderMainMenu()
{

	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
	// Render title 
	text->Draw();

}

void Engine::Lesson03::RenderInGame()
{

	backgroundSprite->Draw();
	sprite->Draw();
	sprite2->Draw();
	sprite3->Draw();
	//sprite4->Draw();

	for (size_t i = 0; i < projectiles.size(); i++) {
		projectiles[i]->sprite->Draw();
		if (projectiles[i]->sprite->GetPosition().x > 1000) {
			projectiles.erase(projectiles.begin() + i);
		}
	}

	//projectiles.clear();

	if (proj != NULL) {
		proj->sprite->Draw();
	}

}

void Engine::Lesson03::UpdateMainMenu()
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

void Engine::Lesson03::UpdateInGame()
{

	// If user press "Quit" key then exit
	if (inputManager->IsKeyReleased("Quit")) {
		state = State::EXIT;
		return;
	}

	sprite2->PlayAnim("spikes-out");

	sprite->Update(GetGameTime());
	sprite2->Update(GetGameTime());
	sprite3->Update(GetGameTime());
	//spriteBullet->Update(GetGameTime());



	//Ingput Calkulason
	float x = sprite2->GetPosition().x;
	float y = sprite2->GetPosition().y;

	//Wolk
	float velocity = 0.15f;
	// s = v * t;
	//sprite->PlayAnim("idle");

	//Aiming With Mouse
	GetCursorPos(&mousePos);
	HWND windowHandle = FindWindow(NULL, "Animation Demo");

	//Convert the mouse position to coordinates relative to the top-left corner of your game window
	ScreenToClient(windowHandle, &mousePos);

	int mouseX = mousePos.x - characterOffSet.x;
	int mouseY = mousePos.y + characterOffSet.y;

	vec2 mouseWorldPos = { mouseX, 768 - mouseY };
	vec2 dir = { mouseWorldPos.x - x, mouseWorldPos.y - y };

	// Normalize the direction vector
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	dir.x /= length;
	dir.y /= length;

	// Calculate the aim angle
	float aimAngle = atan2(dir.y, dir.x) * 180 / M_PI;

	// Update the aim direction
	vec2 aimDir = dir;

	//Debug Mouse Pos in X n Y
	//std::cout << mouseX << " " << 768 - mouseY << "\n";

	if (inputManager->IsKeyPressed("walk-right")) {
		x += velocity * GetGameTime();
		sprite2->SetFlipHorizontal(true);
		sprite2->PlayAnim("walk");
	}

	if (inputManager->IsKeyPressed("walk-left")) {
		x -= velocity * GetGameTime();
		sprite2->SetFlipHorizontal(false);
		sprite2->PlayAnim("walk");
	}

	if (inputManager->IsKeyPressed("walk-up")) {
		y += velocity * GetGameTime();
		//sprite2->SetFlipHorizontal(true);
		sprite2->PlayAnim("walk");
	}

	if (inputManager->IsKeyPressed("walk-down")) {
		y -= velocity * GetGameTime();
		//sprite2->SetFlipHorizontal(true);
		sprite2->PlayAnim("walk");
		//sprite3->SetPosition(sprite3->GetPosition().x + aimDir.x, sprite3->GetPosition().y + aimDir.y);
	}



	if (inputManager->IsKeyPressed("Fire") && duration >= 50) {
		//Bullet Sprite
		spriteBullet = new Sprite(textureBullet, defaultSpriteShader, defaultQuad);

		spriteBullet->SetNumXFrames(1);
		spriteBullet->SetNumYFrames(1);
		spriteBullet->AddAnimation("default", 0, 0);

		spriteBullet->PlayAnim("default");
		spriteBullet->SetScale(0.05);
		spriteBullet->SetAnimationDuration(100);


		proj = new Projectile(spriteBullet);
		proj->sprite->SetPosition(x + 42, y + 18);
		aimDirNow = aimDir;
		proj->setCurrVelo(aimDirNow.x, aimDirNow.y);
		proj->sprite->Update(GetGameTime());

		projectiles.push_back(proj);

		//sprite4->SetPosition(sprite4->GetPosition().x + aimDirNow.x * bulletSpeed, sprite4->GetPosition().y + aimDirNow.y*bulletSpeed);
		duration = 0;
	}
	else {
		//sprite4->SetPosition(x + characterOffSet.x, y + characterOffSet.y);
	}

	for (size_t i = 0; i < projectiles.size(); i++) {
		projectiles[i]->sprite->SetPosition(projectiles[i]->sprite->GetPosition().x + projectiles[i]->currVelo.x * bulletSpeed, projectiles[i]->sprite->GetPosition().y + projectiles[i]->currVelo.y * bulletSpeed);
	}


	sprite2->SetPosition(x, y);



	// FOr Debug
	duration += GetGameTime();
	if (duration >= 1000) {
		//std::cout << mouseWorldPos.x;
		//std::cout << playerPos.y;
		duration = 0;
	}


	bool kirikanan = false;


	//Bezier Curve
	if (p != 749) {
		tempX = posisiX[p];
		tempZ = posisiZ[p];
		if (posisiX[p] < posisiX[p - 1]) {
			kirikanan = true;
		}

		//ubah arah
		sprite->SetFlipHorizontal(kirikanan);
		//Ubah Posisi
		sprite->SetPosition(tempX, tempZ);

		p++;
	}
	else if (p == 749) {
		p = 0;

	}



}



int main(int argc, char** argv) {
	Engine::Setting* setting = new Engine::Setting();
	setting->windowTitle = "Animation Demo";
	setting->screenWidth = 1024;
	setting->screenHeight = 768;
	setting->windowFlag = Engine::WindowFlag::WINDOWED;
	setting->vsync = false;
	setting->targetFrameRate = 0;
	Engine::Game* game = new Engine::Lesson03(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}

