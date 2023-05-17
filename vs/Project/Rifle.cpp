#include "Rifle.h"

Engine::Rifle::Rifle(Game* game) : Weapon(game)
{
	this->game = game;

	//Ammo Purpose
	this->totalAmmo = 30;
	this->currentAmmo = 30;

	//DPS Purpose
	this->reloadTime = 2000; //2000 berart 2 detik
	this->fireRate = 100; //Normal 400
	this->damage = 15;

	//Accuracy Purpose
	accuracy = 0.5f; //0 Perfect, 1 Inaccurate
	MAX_ACCURACY_OFFSET = 0.2f; //to 0.2 to represent a maximum deviation of 20% of the total distance
}

Engine::Rifle::~Rifle()
{
}

void Engine::Rifle::Init()
{
	textureWeapon = new Texture("Pistol.png");
	spriteWeapon = new Sprite(textureWeapon, game->defaultSpriteShader, game->defaultQuad);

	spriteWeapon->SetNumXFrames(4);
	spriteWeapon->SetNumYFrames(2);
	spriteWeapon->AddAnimation("idle", 0, 0);
	spriteWeapon->AddAnimation("fire", 4, 7);

	spriteWeapon->PlayAnim("idle");
	spriteWeapon->SetScale(0.75);
	spriteWeapon->SetAnimationDuration(75);

	//Rotation Tes
	spriteWeapon->SetRotation(30);

	spriteWeapon->SetPosition(300, 300);

}

void Engine::Rifle::Update()
{
	duration += game->GetGameTime();

	spriteWeapon->Update(game->GetGameTime());

	if (game->inputManager->IsKeyPressed("Fire") && !isReload) {
		spriteWeapon->PlayAnim("fire");
	}
	else {
		spriteWeapon->PlayAnim("idle");
	}

	if (game->inputManager->IsKeyPressed("Reload") && currentAmmo < totalAmmo) {
		Reload();
	}
}

void Engine::Rifle::Render()
{
	spriteWeapon->Draw();
}

void Engine::Rifle::UpdateProjectiles()
{
	for (size_t i = 0; i < projectiles.size(); i++) {
		projectiles[i]->SetPosition(projectiles[i]->GetPosition().x + projectiles[i]->getCurrVelo().x * bulletSpeed, projectiles[i]->GetPosition().y + projectiles[i]->getCurrVelo().y * bulletSpeed);
		projectiles[i]->Update();
	}
}

void Engine::Rifle::RenderProjectiles()
{
	//Render Bullet
	for (size_t i = 0; i < projectiles.size(); i++) {
		projectiles[i]->Render();
		if (projectiles[i]->GetPosition().x > game->setting->screenWidth - game->defaultSpriteShader->cameraPos.x||
			projectiles[i]->GetPosition().y > game->setting->screenHeight - game->defaultSpriteShader->cameraPos.y||
			projectiles[i]->GetPosition().x < -game->defaultSpriteShader->cameraPos.x ||
			projectiles[i]->GetPosition().y < -game->defaultSpriteShader->cameraPos.y) {
			projectiles.erase(projectiles.begin() + i);
		}
	}
}



void Engine::Rifle::RemoveProjectileByIndex(int i)
{
	projectiles.erase(projectiles.begin() + i);
}

int Engine::Rifle::GetProjectilesSize()
{
	return projectiles.size();
}

Engine::BoundingBox* Engine::Rifle::GetProjectileBoundingBoxByIndex(int i)
{
	return projectiles[i]->GetBoundingBox();
}

vec2 Engine::Rifle::GetProjectilePositionByIndex(int i)
{
	return projectiles[i]->GetPosition();
}

void Engine::Rifle::Fire(vec2 playerPos, vec2 aimDir, float angleNoNegative, float rawAimAngle)
{
	//Fire Management
	if (currentAmmo <= 0 || isReload) {
		//Reload();
	}

	if (game->inputManager->IsKeyPressed("Fire") && duration >= fireRate && !isReload) {
		//Play sound if nembak
		//sound->Play(false);

		//Calculate Accuracy
		float offset = accuracy * MAX_ACCURACY_OFFSET;
		angleNoNegative += rand() * offset / RAND_MAX - offset / 2.0f;
		aimDir = vec2(cos(angleNoNegative), sin(angleNoNegative));
		aimDir = normalize(aimDir);

		//Bullet Sprite
		projectile = new BulletRifle(game);
		projectile->Init();

		projectile->spriteBullet->SetRotation(rawAimAngle);
		projectile->SetPosition(playerPos.x + 42, playerPos.y + 18);
		projectile->setCurrVelo(aimDir.x, aimDir.y);

		projectiles.push_back(projectile);

		ReduceBulletInChamberByOne();

		//Reset the duration
		duration = 0;
	}

}

void Engine::Rifle::Reload()
{
	isReload = true;

	currentReloadTime += game->GetGameTime();

	if (currentReloadTime >= reloadTime) {
		currentReloadTime = 0;
		currentAmmo = totalAmmo;
		isReload = false;
	}
}


