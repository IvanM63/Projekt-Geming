#include "ScreenGame.h"

Engine::ScreenGame::ScreenGame(Game* game, ScreenManager* manager) : Screen(game, manager)
{


}



void Engine::ScreenGame::Init()
{
	//PLayer Class
	player = new Player(game);
	player->Init();

	//Weapon Class
	weapon = new Weapon(game, player);
	weapon->Init();

	//Create background
	Texture* bgTexture = new Texture("0.png");
	backgroundSprite = new Sprite(bgTexture, game->defaultSpriteShader, game->defaultQuad);
	backgroundSprite->SetSize(game->setting->screenWidth, game->setting->screenHeight);

	//x = 980 || y = 720	

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
	//It's Reload time
	game->inputManager->AddInputMapping("Reload", SDLK_r);

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

	//Ingput Calkulason
	float x = player->GetPosition().x;
	float y = player->GetPosition().y;

	//Wolk
	float velocity = 0.15f;

	//Player Update
	player->Update();

	//Weapon (bullet, weapon, and aim system) Update
	weapon->Update();

	//Walk Management
	if (game->inputManager->IsKeyPressed("walk-right")) {
		x += velocity * game->GetGameTime();
		//player->sprite->SetFlipHorizontal(true);
		player->sprite->PlayAnim("walk");
		isPlayerMoving = true;
	}

	if (game->inputManager->IsKeyPressed("walk-left")) {
		x -= velocity * game->GetGameTime();
		//player->sprite->SetFlipHorizontal(false);
		player->sprite->PlayAnim("walk");
		isPlayerMoving = true;
	}

	if (game->inputManager->IsKeyPressed("walk-up")) {
		y += velocity * game->GetGameTime();
		//sprite2->SetFlipHorizontal(true);
		player->sprite->PlayAnim("walk");
		isPlayerMoving = true;
	}

	if (game->inputManager->IsKeyPressed("walk-down")) {
		y -= velocity * game->GetGameTime();
		//sprite2->SetFlipHorizontal(true);
		player->sprite->PlayAnim("walk");
		isPlayerMoving = true;
	}

	player->sprite->SetPosition(x, y);
	bool kirikanan = false;

	//Collision: Bullet -> Enemy
	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i]->Update();

		for (size_t x = 0; x < weapon->pistol->GetProjectilesSize(); x++) {
			if (enemies[i]->sprite->GetBoundingBox()->CollideWith(weapon->pistol->GetProjectileBoundingBoxByIndex(x))) {
				//std::cout << "HITTT!1!1";
				weapon->pistol->RemoveProjectileByIndex(x);
				enemies[i]->takeDamage(15);

				if (enemies[i]->getHealth() <= 0) {
					enemies.erase(enemies.begin() + i);			
					break;
				}			
			}
		}
	}

	// FOr Debug
	forDebug();

	//SUPER SIMPLE PATHFINDING FROM ENEMY TO PLAYER
	for (size_t i = 0; i < enemies.size(); i++) {
		// Calculate the direction from the enemy to the player
		vec2 direction = player->GetPosition() - enemies[i]->GetPosition();
		// Normalize the direction vector
		float mag = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction.x /= mag;
		direction.y /= mag;

		float distance = mag;

		// If the player is moving, move the enemy towards the player at the specified speed
		if (isPlayerMoving && distance > speedd * game->deltaTime) {
			enemies[i]->move(direction * speedd * game->deltaTime);
		}
	}

	//std::cout << player->getHealth() << "\n";

	//ENEMY SPAWN TESTING - RANDOM
	if (enemies.size() < 3) {
		// spawn enemy
		int x = std::rand() % (game->setting->screenWidth + 200) - 200;
		int y = std::rand() % (game->setting->screenHeight + 200) - 200;

		// check if enemy is out of screen
		if (x < 0 || x > game->setting->screenWidth || y < 0 || y > game->setting->screenHeight) {
			std::cout << "Enemy spawned out of screen at (" << x << ", " << y << ")" << std::endl;
		}
		else {
			std::cout << "Enemy spawned at (" << x << ", " << y << ")" << std::endl;
		}

		Enemy* e = new Enemy(game);
		e->Init();
		e->SetPosition(x, y);
		e->setDebug(true);

		enemies.push_back(e);
	}
}

void Engine::ScreenGame::Render()
{
	//Render Background
	backgroundSprite->Draw();
	
	//Render Enemies
	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i]->Render();
	}

	//Render Player
	player->Render();
	
	//Render Weapon and Bullet
	weapon->Render();

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





