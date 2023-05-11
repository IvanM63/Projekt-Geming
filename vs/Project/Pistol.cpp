#include "Pistol.h"

Engine::Pistol::Pistol(Game* game)
{
	this->game = game;
	this->totalAmmo = 12;
	this->currentAmmo = 12;
	this->reloadTime = 2000; //2000 berart 2 detik
	this->fireRate = 1;
	this->damage = 20;
}

Engine::Pistol::~Pistol()
{
}

void Engine::Pistol::Init()
{
	texturePistol = new Texture("Pistol.png");
	spritePistol = new Sprite(texturePistol, game->defaultSpriteShader, game->defaultQuad);

	spritePistol->SetNumXFrames(4);
	spritePistol->SetNumYFrames(2);
	spritePistol->AddAnimation("idle", 0, 0);
	spritePistol->AddAnimation("fire", 4, 7);
	
	spritePistol->PlayAnim("idle");
	spritePistol->SetScale(0.75);
	spritePistol->SetAnimationDuration(75);

	//Rotation Tes
	spritePistol->SetRotation(30);

	spritePistol->SetPosition(300, 300);

}

void Engine::Pistol::Update()
{
	duration += game->GetGameTime();

	spritePistol->Update(game->GetGameTime());

	if (game->inputManager->IsKeyPressed("Fire") && !isReload) {
		spritePistol->PlayAnim("fire");
	}
	else {
		spritePistol->PlayAnim("idle");
	}

	if (game->inputManager->IsKeyPressed("Reload") && currentAmmo < totalAmmo) {
		Reload();
	}
}

void Engine::Pistol::Render()
{
	spritePistol->Draw();

	//Render Bullet
	for (size_t i = 0; i < projectiles.size(); i++) {
		projectiles[i]->Render();
		if (projectiles[i]->GetPosition().x > game->setting->screenWidth ||
			projectiles[i]->GetPosition().y > game->setting->screenHeight ||
			projectiles[i]->GetPosition().x < 0 ||
			projectiles[i]->GetPosition().y < 0) {
			projectiles.erase(projectiles.begin() + i);
		}
	}
}

void Engine::Pistol::SetPosition(float x, float y)
{
	spritePistol->SetPosition(x, y);
}

void Engine::Pistol::SetRotation(float degree)
{
	spritePistol->SetRotation(degree);

}

void Engine::Pistol::SetFlipVertical(bool tf)
{
	spritePistol->SetFlipVertical(tf);
}

int Engine::Pistol::GetProjectilesSize()
{
	return projectiles.size();
}

void Engine::Pistol::RemoveProjectileByIndex(int i)
{
	projectiles.erase(projectiles.begin() + i);
}

Engine::BoundingBox* Engine::Pistol::GetProjectileBoundingBoxByIndex(int i)
{
	return projectiles[i]->GetBoundingBox();
}

int Engine::Pistol::GetCurrentAmmo()
{
	return currentAmmo;
}

void Engine::Pistol::ReduceBulletInChamberByOne()
{
	this->currentAmmo -= 1;
}

void Engine::Pistol::Fire(vec2 playerPos, vec2 aimDir)
{
	//Fire Management
	if (currentAmmo <= 0 || isReload) {
		Reload();
	}

	if (game->inputManager->IsKeyPressed("Fire") && duration >= 400 && !isReload) {
		//sound->Play(false);

		//Bullet Sprite
		projectile = new Projectile(game);
		projectile->Init();
		
		projectile->SetPosition(playerPos.x + 42, playerPos.y + 18);
		vec2 aimDirNow = aimDir;
		projectile->setCurrVelo(aimDirNow.x, aimDirNow.y);

		projectiles.push_back(projectile);

		duration = 0;

		ReduceBulletInChamberByOne();

		std::cout << currentAmmo << "\n";
	}

	for (size_t i = 0; i < projectiles.size(); i++) {
		projectiles[i]->SetPosition(projectiles[i]->GetPosition().x + projectiles[i]->getCurrVelo().x * bulletSpeed, projectiles[i]->GetPosition().y + projectiles[i]->getCurrVelo().y * bulletSpeed);
		projectiles[i]->Update();
	}
}

void Engine::Pistol::Reload()
{
	isReload = true;

	currentReloadTime += game->GetGameTime();

	if (currentReloadTime >= reloadTime) {
		currentReloadTime = 0;
		currentAmmo = totalAmmo;
		isReload = false;
	}
}


