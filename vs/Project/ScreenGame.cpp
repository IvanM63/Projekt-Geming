#include "ScreenGame.h"

Engine::ScreenGame::ScreenGame(Game* game, ScreenManager* manager) : Screen(game, manager)
{


}



void Engine::ScreenGame::Init()
{

	//Many Enemies
	enemy = new Enemy(game);
	enemy2 = new Enemy(game);
	
	enemy->Init();
	enemy->SetPosition(game->setting->screenWidth / 2, game->setting->screenHeight / 2);

	enemies.push_back(enemy);


	texture = new Texture("flying_eye.png");
	sprite = new Sprite(texture, game->defaultSpriteShader, game->defaultQuad);

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

		//Set Bounding Box
		spriteBullet->SetBoundingBoxSize(spriteBullet->GetScaleWidth() - (16 * spriteBullet->GetScale()) - 40,
			spriteBullet->GetScaleHeight() - (4 * spriteBullet->GetScale()));

		proj = new Projectile(spriteBullet, game);
		proj->sprite->SetPosition(x + 42, y + 18);
		aimDirNow = aimDir;
		proj->setCurrVelo(aimDirNow.x, aimDirNow.y);
		proj->sprite->Update(game->GetGameTime());

		projectiles.push_back(proj);

		duration = 0;
	}

	for (size_t i = 0; i < projectiles.size(); i++) {
		projectiles[i]->sprite->SetPosition(projectiles[i]->sprite->GetPosition().x + projectiles[i]->currVelo.x * bulletSpeed, projectiles[i]->sprite->GetPosition().y + projectiles[i]->currVelo.y * bulletSpeed);
		
	}



	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i]->Update();

		for (size_t x = 0; x < projectiles.size(); x++) {
			if (enemies[i]->sprite->GetBoundingBox()->CollideWith(projectiles[x]->sprite->GetBoundingBox())) {
				//std::cout << "HITTT!1!1";
				projectiles.erase(projectiles.begin() + x);
				enemies[i]->takeDamage(15);

				if (enemies[i]->getHealth() <= 0) {
					enemies.erase(enemies.begin() + i);
					break;
				}			
			}
		}
	}

	sprite2->SetPosition(x, y);

	// FOr Debug
	forDebug();

	bool kirikanan = false;

}

void Engine::ScreenGame::Render()
{

	backgroundSprite->Draw();
	sprite->Draw();
	sprite2->Draw();
	
	//Render Bullet
	for (size_t i = 0; i < projectiles.size(); i++) {
		projectiles[i]->sprite->Draw();
		if (projectiles[i]->sprite->GetPosition().x > game->setting->screenWidth ||
			projectiles[i]->sprite->GetPosition().y > game->setting->screenHeight ||
			projectiles[i]->sprite->GetPosition().x < 0 ||
			projectiles[i]->sprite->GetPosition().y < 0) {
			projectiles.erase(projectiles.begin() + i);
		}
	}

	//Render Enemies
	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i]->Render();
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




