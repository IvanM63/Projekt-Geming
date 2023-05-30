#include "Rifle.h"

Engine::Rifle::Rifle(Game* game) : Weapon(game)
{
	this->game = game;

	//Ammo Purpose
	this->totalAmmo = 30;
	this->currentAmmo = 30;

	//DPS Purpose
	this->reloadTime = 2000; //2000 berart 2 detik
	this->fireRate = 200; //Normal 400
	this->damage = 33;

	//Accuracy Purpose
	accuracy = 0.5f; //0 Perfect, 1 Inaccurate
	MAX_ACCURACY_OFFSET = 0.2f; //to 0.2 to represent a maximum deviation of 20% of the total distance
}

Engine::Rifle::~Rifle()
{
}

void Engine::Rifle::Init()
{
	textureWeapon = new Texture("Asset/Weapon/Rifle/Rifle_12F_Single.png");
	spriteWeapon = new Sprite(textureWeapon, game->defaultSpriteShader, game->defaultQuad);

	spriteWeapon->SetNumXFrames(12);
	spriteWeapon->SetNumYFrames(1);
	spriteWeapon->AddAnimation("idle", 0, 0);
	spriteWeapon->AddAnimation("fire", 0, 11);

	spriteWeapon->PlayAnim("idle");
	spriteWeapon->SetScale(1);
	spriteWeapon->SetAnimationDuration(12);

	//Rotation Tes
	spriteWeapon->SetRotation(30);
	spriteWeapon->centerX = -25;
	spriteWeapon->SetPosition(300, 300);

	// This dot sprite is for visual debugging (to see the actual bounding box) 
	dotTexture = new Texture("dot.png");
	dotSprite1 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);
	dotSprite2 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);
	dotSprite3 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);
	dotSprite4 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);

}

void Engine::Rifle::Update()
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
	if (fireAnimTime > 64) {
		spriteWeapon->PlayAnim("idle");
		fireAnimTime = 64;
	}

	if (game->inputManager->IsKeyPressed("Reload") && currentAmmo < totalAmmo) {
		Reload();
	}

	//Shape for debug
	if (isDebug) {
		BoundingBox* bb = spriteWeapon->GetBoundingBox();
		dotSprite1->SetPosition(bb->GetVertices()[0].x - (0.5f * dotSprite1->GetScaleWidth()),
			bb->GetVertices()[0].y - (0.5f * dotSprite1->GetScaleHeight()));
		dotSprite2->SetPosition(bb->GetVertices()[1].x - (0.5f * dotSprite2->GetScaleWidth()),
			bb->GetVertices()[1].y - (0.5f * dotSprite2->GetScaleHeight()));
		dotSprite3->SetPosition(bb->GetVertices()[2].x - (0.5f * dotSprite3->GetScaleWidth()),
			bb->GetVertices()[2].y - (0.5f * dotSprite3->GetScaleHeight()));
		dotSprite4->SetPosition(bb->GetVertices()[3].x - (0.5f * dotSprite4->GetScaleWidth()),
			bb->GetVertices()[3].y - (0.5f * dotSprite3->GetScaleHeight()));
	}
}

void Engine::Rifle::Render()
{
	spriteWeapon->Draw();

	if (isDebug) {
		dotSprite1->Draw();
		dotSprite2->Draw();
		dotSprite3->Draw();
		dotSprite4->Draw();
	}
}

void Engine::Rifle::SetPositionToPlayer(vec2 playerPos)
{
	SetPosition(playerPos.x - 8, playerPos.y+3);
}

void Engine::Rifle::SetRotation(float rawAimAngle)
{
	spriteWeapon->SetRotation(rawAimAngle);
	//if (rawAimAngle > 90 || rawAimAngle < -90) {
	//	SetPosition(spriteWeapon->GetPosition().x - 20, spriteWeapon->GetPosition().y);
	//}
	//else {
	//	SetPosition(spriteWeapon->GetPosition().x + 20, spriteWeapon->GetPosition().y);
	//	//spriteWeapon->SetFlipVertical(false);
	//}
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
		Reload();
	}

	//if (game->inputManager->PressKey()

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
		projectile->SetPosition(spriteWeapon->GetPosition().x + 30, spriteWeapon->GetPosition().y+15);
		//projectile->SetPosition(spriteWeapon->GetPosition().x + 100, spriteWeapon->GetPosition().y);
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
	reloadPercentage = currentReloadTime / reloadTime;
	
	if (currentReloadTime >= reloadTime) {
		currentReloadTime = 0;
		currentAmmo = totalAmmo;
		isReload = false;
	}

	//Debug
	//std::cout << std::fixed << std::setprecision(2) << reloadPercentage << std::endl;
}


