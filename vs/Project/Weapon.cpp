#include "Weapon.h"
#include "../../../../backup/Projekt/Projekt-Geming/vs/Project/Projectile.h"

Engine::Weapon::Weapon(Game* game, Player* player)
{
	this->game = game;
	this->player = player;
	this->totalAmmo = 12;
	this->currentAmmo = 12;
	this->reloadTime = 1;
	this->fireRate = 1;
}

Engine::Weapon::~Weapon()
{
}

void Engine::Weapon::Init()
{
	//Bullet Sprite
	textureBullet = new Texture("bullet.png");
}

void Engine::Weapon::Update()
{
	Fire();
}

void Engine::Weapon::Render()
{
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
}

void Engine::Weapon::Fire()
{
	duration += game->GetGameTime();
	if (duration >= 1000) {
		//std::cout << mouseWorldPos.x;
		//std::cout << playerPos.y;
		duration = 0;
	}

	//Ingput Calkulason
	float x = player->GetPosition().x;
	float y = player->GetPosition().y;

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

	//Fire Management
	if (game->inputManager->IsKeyPressed("Fire") && duration >= 400) {
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
}

int Engine::Weapon::GetProjectilesSize()
{
	return projectiles.size();
}

void Engine::Weapon::RemoveProjectileByIndex(int i)
{
	projectiles.erase(projectiles.begin() + i);
}

Engine::BoundingBox* Engine::Weapon::GetProjectileBoundingBoxByIndex(int i)
{
	return projectiles[i]->sprite->GetBoundingBox();
}






