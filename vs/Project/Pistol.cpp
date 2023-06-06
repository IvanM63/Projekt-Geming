#include "Pistol.h"

Engine::Pistol::Pistol(Game* game) : Weapon(game)
{
	this->game = game;

	//Ammmo Purpose
	this->totalAmmo = 12;
	this->currentAmmo = 12;
	
	//DPS Purpose
	this->fireRate = 600; //Normal 400
	this->damage = 40; //Normal 25
	this->reloadTime = 1500; //2000 berart 2 detik

	//Accuracy Purpose
	accuracy = 0.9f; //0 Perfect, 1 Inaccurate
	MAX_ACCURACY_OFFSET = 0.2f; //to 0.2 to represent a maximum deviation of 20% of the total distance
}

Engine::Pistol::~Pistol()
{
}

void Engine::Pistol::Init()
{
	textureWeapon = new Texture("Asset/Weapon/Pistol/Pistol.png");
	spriteWeapon = new Sprite(textureWeapon, game->defaultSpriteShader, game->defaultQuad);

	spriteWeapon->SetNumXFrames(4);
	spriteWeapon->SetNumYFrames(2);
	spriteWeapon->AddAnimation("idle", 0, 0);
	spriteWeapon->AddAnimation("fire", 4, 7); //4 Frame
	
	spriteWeapon->PlayAnim("idle");
	spriteWeapon->SetScale(0.4);
	spriteWeapon->SetAnimationDuration(102);

	spriteWeapon->SetBoundToCamera(false);

	//Rotation Tes
	spriteWeapon->SetRotation(30);

	spriteWeapon->SetPosition(300, 300);

}

void Engine::Pistol::Update()
{
	duration += game->GetGameTime();

	spriteWeapon->Update(game->GetGameTime());

	if (game->inputManager->IsKeyPressed("Fire") && !isReload) {
		spriteWeapon->PlayAnim("fire");
		fireAnimTime = 0;
	}
	else {

	}
	fireAnimTime += game->GetGameTime();
	//std::cout << fireAnimTime << "\n";
	if (fireAnimTime > 400) {
		spriteWeapon->PlayAnim("idle");
		fireAnimTime = 400;
	}

	if (game->inputManager->IsKeyPressed("Reload") && currentAmmo < totalAmmo) {
		Reload();
	}
}

void Engine::Pistol::Render()
{
	spriteWeapon->Draw();

}

void Engine::Pistol::SetPositionToPlayer(vec2 playerPos)
{
	SetPosition(playerPos.x+6, playerPos.y+12);
}

void Engine::Pistol::SetRotation(float rawAimAngle)
{
	spriteWeapon->SetRotation(rawAimAngle);
	//if (rawAimAngle > 90 || rawAimAngle < -90) {
	//	SetPosition(spriteWeapon->GetPosition().x + 20, spriteWeapon->GetPosition().y);
	//}
	//else {
	//	//spriteWeapon->SetFlipVertical(false);
	//}
}

void Engine::Pistol::UpdateProjectiles()
{
	for (size_t i = 0; i < projectiles.size(); i++) {
		projectiles[i]->SetPosition(projectiles[i]->GetPosition().x + projectiles[i]->getCurrVelo().x * bulletSpeed, projectiles[i]->GetPosition().y + projectiles[i]->getCurrVelo().y * bulletSpeed);
		projectiles[i]->Update();
	}
}

void Engine::Pistol::RenderProjectiles()
{
	//Render Bullet
	for (size_t i = 0; i < projectiles.size(); i++) {
		projectiles[i]->Render();
		if (projectiles[i]->GetPosition().x > game->setting->screenWidth - game->defaultSpriteShader->cameraPos.x ||
			projectiles[i]->GetPosition().y > game->setting->screenHeight - game->defaultSpriteShader->cameraPos.y ||
			projectiles[i]->GetPosition().x < -game->defaultSpriteShader->cameraPos.x ||
			projectiles[i]->GetPosition().y < -game->defaultSpriteShader->cameraPos.y) {
			projectiles.erase(projectiles.begin() + i);
		}
	}
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

vec2 Engine::Pistol::GetProjectilePositionByIndex(int i)
{
	return projectiles[i]->GetPosition();
}


void Engine::Pistol::Fire(vec2 playerPos, vec2 aimDir, float angleNoNegative, float rawAimAngle)
{
	//Fire Management
	if (currentAmmo <= 0 || isReload) {
		Reload();
	}

	//game->inputManager->

	if (game->inputManager->IsKeyPressed("Fire") && duration >= fireRate && !isReload) {
		//Play sound if nembak
		//sound->Play(false);

		//Calculate Accuracy		
		float offset = accuracy * MAX_ACCURACY_OFFSET;
		angleNoNegative += rand() * offset / RAND_MAX - offset / 2.0f;
		aimDir = vec2(cos(angleNoNegative), sin(angleNoNegative));
		aimDir = normalize(aimDir);

		//Bullet Sprite
		projectile = new Projectile(game);
		projectile->Init();

		//projectile->SetPosition(playerPos.x + 42, playerPos.y + 18);
		projectile->SetPosition(spriteWeapon->GetPosition().x, spriteWeapon->GetPosition().y);
		projectile->setCurrVelo(aimDir.x, aimDir.y);

		projectiles.push_back(projectile);

		ReduceBulletInChamberByOne();

		//Reset the duration
		duration = 0;
	}

	
}

void Engine::Pistol::Reload()
{
	isReload = true;

	currentReloadTime += game->GetGameTime();
	reloadPercentage = currentReloadTime / reloadTime;

	if (currentReloadTime >= reloadTime) {
		currentReloadTime = 0;
		currentAmmo = totalAmmo;
		isReload = false;
	}
}


