#include "ScreenGame.h"

Engine::ScreenGame::ScreenGame(Game* game, ScreenManager* manager) : Screen(game, manager)
{

}



void Engine::ScreenGame::Init()
{
	//Came Init
	game->defaultSpriteShader->cameraPos = { 0,0 };

	//Wave System
	wave = new Wave(this->game);

	//Impact Effect
	textureImpact = new Texture("Asset/Weapon/Impact/impact01.png");
	spriteImpact = new Sprite(textureImpact, game->defaultSpriteShader, game->defaultQuad);
	spriteImpact->SetNumXFrames(5);
	spriteImpact->SetNumYFrames(1);
	spriteImpact->AddAnimation("default", 0, 4);
	spriteImpact->PlayAnim("default");
	spriteImpact->SetScale(1);
	spriteImpact->SetAnimationDuration(150);

	//UI SECTION
	textureHP = new Texture("Asset/UI/Health/HealthBar.png");
	spriteHP = new Sprite(textureHP, game->defaultSpriteShader, game->defaultQuad);

	spriteHP->SetNumXFrames(1);
	spriteHP->SetNumYFrames(1);
	spriteHP->AddAnimation("default", 0, 0);
	spriteHP->PlayAnim("default");
	spriteHP->SetScale(2.5);
	spriteHP->SetAnimationDuration(30);
	spriteHP->SetPosition(30, 650);
	spriteHP->SetBoundToCamera(true);

	//Text
	enemiesLeftText = new Text("lucon.ttf", 24, game->defaultTextShader);
	enemiesLeftText->SetScale(1.0f);
	enemiesLeftText->SetColor(255, 255, 255);
	enemiesLeftText->SetPosition(10, game->setting->screenHeight - 150);

	//Wave Text
	waveText = new Text("lucon.ttf", 24, game->defaultTextShader);
	waveText->SetScale(1.0f);
	waveText->SetColor(255, 255, 255);
	waveText->SetPosition(game->setting->screenWidth/2, game->setting->screenHeight - 50);

	//Cooin Text
	coinText = new Text("lucon.ttf", 24, game->defaultTextShader);
	coinText->SetScale(1.0f);
	coinText->SetColor(255, 255, 255);
	coinText->SetPosition(game->setting->screenWidth - 200, game->setting->screenHeight - 50);

	//Enemies
	enemiesTexture = new Texture("Warrior_Sheet-Effect.png");

	//PLayer Class
	player = new Player(game);
	player->Init();
	player->SetPosition(game->setting->screenWidth / 2 - 50, game->setting->screenHeight / 2);
	
	//Weapon Class
	weapon = new WeaponManager(game, player);
	weapon->Init();

	//Create background
	Texture* bgTexture = new Texture("Asset/Map/MapV2.png");
	backgroundSprite = new Sprite(bgTexture, game->defaultSpriteShader, game->defaultQuad);
	backgroundSprite->SetNumXFrames(1);
	backgroundSprite->SetNumYFrames(1);
	backgroundSprite->SetSize(game->setting->screenWidth+750, game->setting->screenHeight+750);
	backgroundSprite->SetPosition(-400, -350);


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
	//Weapon Selection
	game->inputManager->AddInputMapping("Pistol", SDLK_1);
	game->inputManager->AddInputMapping("Rifle", SDLK_2);

	//Set the background color
	//game->SetBackgroundColor(102, 195, 242);
	
}

void Engine::ScreenGame::Update()
{
	//std::cout << player->GetPosition().x << "\n";
	// If user press "Quit" key then exit
	if (game->inputManager->IsKeyReleased("Quit")) {
		game->state = State::EXIT;
		return;
	}

	//Wave System
	if (wave->GetSpawnStatus()) {
		enemies = wave->SpawnEnemies();
		//wave->WaveStart();
	}
	
	wave->Update();

	//Update UI
	spriteHP->Update(game->GetGameTime());
	enemiesLeftText->SetText("Enemies : " + std::to_string(enemies.size()));
	waveText->SetText("Wave | " + std::to_string(wave->GetCurrentWave()));
	coinText->SetText("Score : " + std::to_string(score));

	//std::cout << objectX << " " << objectY << "\n";

	//Ingput Calkulason
	float x = player->GetPosition().x;
	float y = player->GetPosition().y;

	//Wolk
	float velocity = 0.10f;

	//Player Update
	player->Update();

	//Weapon (bullet, weapon, and aim system) Update
	weapon->Update();

	//Walk Management
	if (game->inputManager->IsKeyPressed("walk-right")) {
		x += velocity * game->GetGameTime();
		//player->sprite->SetFlipHorizontal(true);
		player->sprite->PlayAnim("Walk-Horizontal");
		isPlayerMoving = true;
		game->defaultSpriteShader->cameraPos.x -= velocity * game->GetGameTime();
	}

	if (game->inputManager->IsKeyPressed("walk-left")) {
		x -= velocity * game->GetGameTime();
		//player->sprite->SetFlipHorizontal(false);
		player->sprite->PlayAnim("Walk-Horizontal");
		isPlayerMoving = true;
		game->defaultSpriteShader->cameraPos.x += velocity * game->GetGameTime();
	}

	if (game->inputManager->IsKeyPressed("walk-up")) {
		y += velocity * game->GetGameTime();
		//sprite2->SetFlipHorizontal(true);
		player->sprite->PlayAnim("Walk-Up");
		isPlayerMoving = true;
		game->defaultSpriteShader->cameraPos.y -= velocity * game->GetGameTime();
	}

	if (game->inputManager->IsKeyPressed("walk-down")) {
		y -= velocity * game->GetGameTime();
		//sprite2->SetFlipHorizontal(true);
		player->sprite->PlayAnim("Walk-Down");
		isPlayerMoving = true;
		game->defaultSpriteShader->cameraPos.y += velocity * game->GetGameTime();
	}

	player->sprite->SetPosition(x, y);
	bool kirikanan = false;

	//Collision: Bullet -> Enemy
	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i]->Update();

		for (size_t j = 0; j < weapon->weapons.size(); j++) {
			for (size_t x = 0; x < weapon->weapons[j]->GetProjectilesSize(); x++) {
				if (enemies[i]->sprite->GetBoundingBox()->CollideWith(weapon->weapons[j]->GetProjectileBoundingBoxByIndex(x))) {

					//Impact Effect
					vec2 posImpact = weapon->weapons[j]->GetProjectilePositionByIndex(x);
					//Sprite* si = spriteImpact;

					Sprite*  si = new Sprite(textureImpact, game->defaultSpriteShader, game->defaultQuad);
					si->SetNumXFrames(5);
					si->SetNumYFrames(1);
					si->AddAnimation("default", 0, 4);
					si->PlayAnim("default");
					si->SetScale(2);
					si->SetAnimationDuration(50);

					si->SetPosition(posImpact.x, posImpact.y);
					bulletImpacts.push_back(si);

					// Define knockback force
					float KNOCKBACK_FORCE = 10.0f;

					// Apply knockback force
					vec2 knockbackDirection = normalize((enemies[i]->GetBoundingBoxCenterPoint() - weapon->weapons[j]->GetProjectilePositionByIndex(x)));
					vec2 knockbackForce = knockbackDirection * KNOCKBACK_FORCE;
					enemies[i]->SetPosition(enemies[i]->GetPosition().x + knockbackForce.x, enemies[i]->GetPosition().y + knockbackForce.y);

					//std::cout << "HITTT!1!1";
					weapon->weapons[j]->RemoveProjectileByIndex(x);
					enemies[i]->takeDamage(weapon->weapons[j]->GetDamage());

				}
			}			
		}

		if (enemies[i]->getHealth() <= 0) {
			enemies[i]->sprite->PlayAnim("dies");
			if (enemies[i]->sprite->isSpriteLastFrame()) {
				enemies.erase(enemies.begin() + i);
				wave->RemoveEnemiesByOne(i);
				score += 10;
				game->setting->score += 10;
				break;
			}
			//std::cout << enemies[i]->sprite->frameIndex << "\n";
		}
		
	}
	
	impactAnimTime += game->GetGameTime();

	//Bullet Impact
	for (size_t i = 0; i < bulletImpacts.size(); i++) {
		bulletImpacts[i]->Update(game->GetGameTime());

		if (bulletImpacts[i]->isSpriteLastFrame()) {
			bulletImpacts.erase(bulletImpacts.begin() + i); //Hapus sprite di vector
		}
		
	}

	//Collision Enemy -> player
	for (size_t i = 0; i < enemies.size(); i++) {
		if (enemies[i]->sprite->GetBoundingBox()->CollideWith(player->sprite->GetBoundingBox())) {
			//std::cout << "HIT";
			player->takeDamage(enemies[i]->GetDamage());
			
			if (player->getHealth() <= 0) {
				manager->switchScreen(ScreenState::GAME_OVER);
			}

			//PLay enemies anim
			//enemies[i]->sprite->PlayAnim("attack");


		}
	}

	duration += game->GetGameTime();

	//std::cout << duration<<"\n";
	// FOr Debug
	forDebug();

	//SUPER SIMPLE PATHFINDING FROM ENEMY TO PLAYER
	for (auto i = 0; i < enemies.size(); i++) {
		// Calculate the direction from the enemy to the player
		vec2 direction = player->GetPosition() - vec2(10, 0) - enemies[i]->GetPosition();
		
		//std::cout << enemies[i]->GetDirection().x << "\n";
		// Normalize the direction vector
		float mag = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction.x /= mag;
		direction.y /= mag;

		float distance = mag;
		
		if (enemies[i]->getHealth() <= 0) {
			enemies[i]->SetDirection(0, 0);
		}
		else {
			enemies[i]->SetDirection(direction.x, direction.y);
			enemies[i]->sprite->PlayAnim("moving");
		}

		

		float rawAimAngle = atan2(direction.y, direction.x) * 180 / M_PI;

		//Setting rotation for Enemies
		if (rawAimAngle > 90 || rawAimAngle < -90) {
			enemies[i]->SetFlipHorizontal(true);
		}
		else {
			enemies[i]->SetFlipHorizontal(false);
		}

		// If the player is moving, move the enemy towards the player at the specified speed
		if (isPlayerMoving && distance > enemies[i]->GetSpeed() * game->deltaTime) {		
			enemies[i]->move(enemies[i]->GetDirection() * enemies[i]->GetSpeed() * game->deltaTime);
		}
	}

	//std::cout << player->getHealth() << "\n";

	//ENEMY SPAWN TESTING - RANDOM
	/*if (enemies.size() < 10) {
		// spawn enemy
		int x = std::rand() % (game->setting->screenWidth + 50 * 2) - 50;
		int y = std::rand() % (game->setting->screenHeight + 50 * 2) - 50;

		// check if enemy is out of screen
		if (x < 0 || x > game->setting->screenWidth || y < 0 || y > game->setting->screenHeight) {
			//std::cout << "Enemy spawned out of screen at (" << x << ", " << y << ")" << std::endl;

			Enemy* e = new Enemy(game);
			e->Init();
			e->SetPosition(x, y);
			e->setDebug(false);

			enemies.push_back(e);
		}
		/*else {
			std::cout << "Enemy spawned at (" << x << ", " << y << ")" << std::endl;
		}
	}*/

	//SCREEN SHAKE


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

	//Render Bullet Impact
	for (size_t i = 0; i < bulletImpacts.size(); i++) {
		bulletImpacts[i]->Draw();
	}

	//Render UI HARUS PALING BAWAH
	//spriteHP->Draw();
	enemiesLeftText->Draw();
	waveText->Draw();
	coinText->Draw();
}

void Engine::ScreenGame::forDebug()
{
	
	if (duration >= 1000) {
		//std::cout << mouseWorldPos.x;
		//std::cout << playerPos.y;
		duration = 0;
	}
}

void Engine::ScreenGame::avoidCollision(Enemy* collidingEnemy, Enemy* otherEnemy)
{
	float collisionVectorX = otherEnemy->GetDirection().x - collidingEnemy->GetDirection().x;
	float collisionVectorY = otherEnemy->GetDirection().y - collidingEnemy->GetDirection().y;

	float perpendicularVectorX = -collisionVectorY;
	float perpendicularVectorY = collisionVectorX;

	float dotProduct = collidingEnemy->GetDirection().x * perpendicularVectorX + collidingEnemy->GetDirection().y * perpendicularVectorY;

	float clearDirectionX = perpendicularVectorX;
	float clearDirectionY = perpendicularVectorY;

	if (dotProduct > 0) {
		clearDirectionX *= -1;
		clearDirectionY *= -1;
	}

	float clearDirectionLength = sqrtf(clearDirectionX * clearDirectionX + clearDirectionY * clearDirectionY);
	//std::cout << clearDirectionX / clearDirectionLength * collidingEnemy->GetSpeed() << "\n";
	vec2 todo = { clearDirectionX / clearDirectionLength * collidingEnemy->GetSpeed() , clearDirectionY / clearDirectionLength * collidingEnemy->GetSpeed() };
	collidingEnemy->SetDirection(todo.x,todo.y);
}





