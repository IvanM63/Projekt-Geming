#include "ScreenGame.h"

Engine::ScreenGame::ScreenGame(Game* game, ScreenManager* manager) : Screen(game, manager)
{

}



void Engine::ScreenGame::Init()
{
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

	spriteHP->SetNumXFrames(11);
	spriteHP->SetNumYFrames(1);
	spriteHP->AddAnimation("100", 0, 0);
	spriteHP->AddAnimation("90", 1, 1);
	spriteHP->AddAnimation("80", 2, 2);
	spriteHP->AddAnimation("70", 3, 3);
	spriteHP->AddAnimation("60", 4, 4);
	spriteHP->AddAnimation("50", 5, 5);
	spriteHP->AddAnimation("40", 6, 6);
	spriteHP->AddAnimation("30", 7, 7);
	spriteHP->AddAnimation("20", 8, 8);
	spriteHP->AddAnimation("10", 9, 9);
	spriteHP->AddAnimation("0", 10, 10);
	spriteHP->PlayAnim("100");
	spriteHP->SetScale(2.5);
	spriteHP->SetAnimationDuration(30);
	spriteHP->SetPosition(30, 650);
	spriteHP->SetBoundToCamera(true);

	//Border
	border = new Texture("Asset/UI/border.png");
	borderwave = new Sprite(border, game->defaultSpriteShader, game->defaultQuad);
	borderwave->SetNumXFrames(1);
	borderwave->SetNumYFrames(1);
	borderwave->AddAnimation("default", 0, 0);
	borderwave->PlayAnim("default");
	borderwave->SetScale(0.5);
	borderwave->SetAnimationDuration(30);
	float borderwavepos[2] = { game->setting->screenWidth / 2 - 75, game->setting->screenHeight - 70 };
	borderwave->SetPosition(borderwavepos[0], borderwavepos[1]);
	borderwave->SetBoundToCamera(true);

	borderscore = new Sprite(border, game->defaultSpriteShader, game->defaultQuad);
	borderscore->SetNumXFrames(1);
	borderscore->SetNumYFrames(1);
	borderscore->AddAnimation("default", 0, 0);
	borderscore->PlayAnim("default");
	borderscore->SetScale(0.5);
	borderscore->SetAnimationDuration(30);
	float borderscorepos[2] = { game->setting->screenWidth - 200, game->setting->screenHeight - 70 };
	borderscore->SetPosition(borderscorepos[0], borderscorepos[1]);
	borderscore->SetBoundToCamera(true);

	borderammo = new Sprite(border, game->defaultSpriteShader, game->defaultQuad);
	borderammo->SetNumXFrames(1);
	borderammo->SetNumYFrames(1);
	borderammo->AddAnimation("default", 0, 0);
	borderammo->PlayAnim("default");
	borderammo->SetScale(0.5);
	borderammo->SetAnimationDuration(30);
	float borderammopos[2] = { game->setting->screenWidth - 200, 0 };
	borderammo->SetPosition(borderammopos[0], borderammopos[1]);
	borderammo->SetBoundToCamera(true);

	//HPBorder
	borderHP = new Texture("Asset/UI/healthbarborder.png");
	border2HP = new Sprite(borderHP, game->defaultSpriteShader, game->defaultQuad);
	border2HP->SetNumXFrames(1);
	border2HP->SetNumYFrames(1);
	border2HP->AddAnimation("default", 0, 0);
	border2HP->PlayAnim("default");
	border2HP->SetScale(0.5);
	border2HP->SetAnimationDuration(30);
	float border2HPpos[2] = { 0, game->setting->screenHeight - 70 };
	border2HP->SetPosition(border2HPpos[0], border2HPpos[1]);
	border2HP->SetBoundToCamera(true);

	//HP Bar
	textureHPbar = new Texture("Asset/UI/healthbar.png");
	spriteHPbar = new Sprite(textureHPbar, game->defaultSpriteShader, game->defaultQuad);
	spriteHPbar->SetNumXFrames(11);
	spriteHPbar->SetNumYFrames(1);
	spriteHPbar->AddAnimation("100", 0, 0);
	spriteHPbar->AddAnimation("90", 1, 1);
	spriteHPbar->AddAnimation("80", 2, 2);
	spriteHPbar->AddAnimation("70", 3, 3);
	spriteHPbar->AddAnimation("60", 4, 4);
	spriteHPbar->AddAnimation("50", 5, 5);
	spriteHPbar->AddAnimation("40", 6, 6);
	spriteHPbar->AddAnimation("30", 7, 7);
	spriteHPbar->AddAnimation("20", 8, 8);
	spriteHPbar->AddAnimation("10", 9, 9);
	spriteHPbar->AddAnimation("0", 10, 10);
	spriteHPbar->PlayAnim("100");
	spriteHPbar->SetScale(0.5);
	spriteHPbar->SetAnimationDuration(30);
	spriteHPbar->SetPosition(border2HPpos[0], border2HPpos[1]);
	spriteHPbar->SetBoundToCamera(true);

	//Gun UI
	texturegunUI = new Texture("Asset/UI/gunhud.png");
	spritegunUI = new Sprite(texturegunUI, game->defaultSpriteShader, game->defaultQuad);

	spritegunUI->SetNumXFrames(2);
	spritegunUI->SetNumYFrames(1);
	spritegunUI->AddAnimation("default", 0, 0);
	spritegunUI->AddAnimation("rifle", 1, 0);
	spritegunUI->PlayAnim("default");
	spritegunUI->SetScale(2);
	spritegunUI->SetAnimationDuration(30);
	spritegunUI->SetPosition(game->setting->screenWidth - 200, 70);
	spritegunUI->SetBoundToCamera(true);

	//Text
	enemiesLeftText = new Text("lucon.ttf", 24, game->defaultTextShader);
	enemiesLeftText->SetScale(1.0f);
	enemiesLeftText->SetColor(255, 255, 255);
	enemiesLeftText->SetPosition(10, game->setting->screenHeight - 150);

	//Wave Text
	waveText = new Text("lucon.ttf", 24, game->defaultTextShader);
	waveText->SetScale(1.0f);
	waveText->SetColor(255, 255, 255);
	float wavetextpos[2] = { borderwavepos[0] + 10, borderwavepos[1] + 35 };
	waveText->SetPosition(wavetextpos[0], wavetextpos[1]);

	//Cooin Text
	coinText = new Text("lucon.ttf", 24, game->defaultTextShader);
	coinText->SetScale(1.0f);
	coinText->SetColor(255, 255, 255);
	float scoretextpos[2] = { borderscorepos[0] + 10, borderscorepos[1] + 35 };
	coinText->SetPosition(scoretextpos[0], scoretextpos[1]);

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
	Texture* bgTexture = new Texture("Asset/Map/Map.png");
	backgroundSprite = new Sprite(bgTexture, game->defaultSpriteShader, game->defaultQuad);
	backgroundSprite->SetSize(game->setting->screenWidth+750, game->setting->screenHeight+750);
	backgroundSprite->SetPosition(-200, 0);

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
	coinText->SetText("Score : " + std::to_string(coin));

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

					if (enemies[i]->getHealth() <= 0) {
						enemies.erase(enemies.begin() + i);
						wave->RemoveEnemiesByOne(i);
						coin += 10;
						break;
					}

					
				
				}
			}			
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
		vec2 direction = player->GetPosition() - enemies[i]->GetPosition();
		
		//std::cout << enemies[i]->GetDirection().x << "\n";
		// Normalize the direction vector
		float mag = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction.x /= mag;
		direction.y /= mag;

		float distance = mag;
		
		enemies[i]->SetDirection(direction.x, direction.y);

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

			//AVOID COLLISION
			/*for (int j = i + 1; j < enemies.size(); j++)
			{
				//Enemy* enemy1 = enemies[i];
				//Enemy* enemy2 = enemies[j];

				if (enemies[i]->sprite->GetBoundingBox()->CollideWith(enemies[j]->sprite->GetBoundingBox()))
				{
					avoidCollision(enemies[i], enemies[j]);
					avoidCollision(enemies[j], enemies[i]);
					enemies[i]->move(enemies[i]->GetDirection()* enemies[i]->GetSpeed()* game->deltaTime);
					enemies[j]->move(enemies[j]->GetDirection()* enemies[j]->GetSpeed()* game->deltaTime);
				}
			}*/
			
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
	borderwave->Draw();
	borderscore->Draw();
	borderammo->Draw();
	border2HP->Draw();
	spritegunUI->Draw();
	spriteHPbar->Draw();

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





