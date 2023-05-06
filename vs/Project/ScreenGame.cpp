#include "ScreenGame.h"

Engine::ScreenGame::ScreenGame(Game* game, ScreenManager* manager) : Screen(game, manager)
{


}



void Engine::ScreenGame::Init()
{
	texture = new Texture("flying_eye.png");
	sprite = new Sprite(texture, game->defaultSpriteShader, game->defaultQuad);

	texture3 = new Texture("Warrior_Sheet-Effect.png");
	sprite3 = new Sprite(texture3, game->defaultSpriteShader, game->defaultQuad);

	//sprite2
	texture2 = new Texture("turtles.png");
	sprite2 = new Sprite(texture2, game->defaultSpriteShader, game->defaultQuad);

	//Bullet Sprite
	textureBullet = new Texture("bullet.png");

	//Create background
	Texture* bgTexture = new Texture("0.png");
	backgroundSprite = new Sprite(bgTexture, game->defaultSpriteShader, game->defaultQuad);
	backgroundSprite->SetSize(game->setting->screenWidth, game->setting->screenHeight);


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
	game->inputManager->AddInputMapping("walk-left", SDLK_LEFT);
	game->inputManager->AddInputMapping("walk-left", SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	game->inputManager->AddInputMapping("walk-left", SDL_CONTROLLER_AXIS_LEFTX);
	game->inputManager->AddInputMapping("walk-left", SDLK_a);
	//Wolk righ
	game->inputManager->AddInputMapping("walk-right", SDLK_RIGHT);
	game->inputManager->AddInputMapping("walk-right", SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	game->inputManager->AddInputMapping("walk-right", SDLK_d);
	//Wolk up
	game->inputManager->AddInputMapping("walk-up", SDLK_w);
	//Wolk don
	game->inputManager->AddInputMapping("walk-down", SDLK_s);
	//Quit
	game->inputManager->AddInputMapping("Quit", SDLK_ESCAPE);
	game->inputManager->AddInputMapping("Quit", SDL_CONTROLLER_BUTTON_Y);
	//fire
	game->inputManager->AddInputMapping("Fire", SDL_BUTTON_LEFT);


	//Set the background color
	game->SetBackgroundColor(102, 195, 242);

	//bezier
	bezierInit();

}

void Engine::ScreenGame::Update()
{
	// If user press "Quit" key then exit
	if (game->inputManager->IsKeyReleased("Quit")) {
		game->state = State::EXIT;
		return;
	}

	sprite2->PlayAnim("spikes-out");

	sprite->Update(game->GetGameTime());
	sprite2->Update(game->GetGameTime());
	sprite3->Update(game->GetGameTime());
	//spriteBullet->Update(GetGameTime());



	//Ingput Calkulason
	float x = sprite2->GetPosition().x;
	float y = sprite2->GetPosition().y;

	//Wolk
	float velocity = 0.15f;

	//Aiming With Mouse
	GetCursorPos(&mousePos);
	HWND windowHandle = FindWindow(NULL, "Jombi-Jombian");

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

	//Walk Management
	if (game->inputManager->IsKeyPressed("walk-right")) {
		x += velocity * game->GetGameTime();
		sprite2->SetFlipHorizontal(true);
		sprite2->PlayAnim("walk");
	}

	if (game->inputManager->IsKeyPressed("walk-left")) {
		x -= velocity * game->GetGameTime();
		sprite2->SetFlipHorizontal(false);
		sprite2->PlayAnim("walk");
	}

	if (game->inputManager->IsKeyPressed("walk-up")) {
		y += velocity * game->GetGameTime();
		//sprite2->SetFlipHorizontal(true);
		sprite2->PlayAnim("walk");
	}

	if (game->inputManager->IsKeyPressed("walk-down")) {
		y -= velocity * game->GetGameTime();
		//sprite2->SetFlipHorizontal(true);
		sprite2->PlayAnim("walk");
		//sprite3->SetPosition(sprite3->GetPosition().x + aimDir.x, sprite3->GetPosition().y + aimDir.y);
	}


	//Fire Management
	if (game->inputManager->IsKeyPressed("Fire") && duration >= 50) {
		//Bullet Sprite
		spriteBullet = new Sprite(textureBullet, game->defaultSpriteShader, game->defaultQuad);

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
		proj->sprite->Update(game->GetGameTime());

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
	forDebug();

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

void Engine::ScreenGame::Render()
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

void Engine::ScreenGame::forDebug()
{
	duration += game->GetGameTime();
	if (duration >= 1000) {
		//std::cout << mouseWorldPos.x;
		//std::cout << playerPos.y;
		duration = 0;
	}
}

void Engine::ScreenGame::bezierInit()
{
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


