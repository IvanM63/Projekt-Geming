#include "Weapon.h"

Engine::Weapon::Weapon(Game* game)
{
	this->game = game;

	this->totalAmmo = 12;
	this->currentAmmo = 12;
	this->reloadTime = 2000; //2000 berart 2 detik
	this->fireRate = 200; 
	this->damage = 20;
}

Engine::Weapon::~Weapon()
{
}

void Engine::Weapon::Init()
{
}

void Engine::Weapon::Update()
{
}

void Engine::Weapon::Render()
{
}

int Engine::Weapon::GetDamage()
{
	return damage;
}

void Engine::Weapon::UpdateProjectiles()
{
}

void Engine::Weapon::RenderProjectiles()
{
}

void Engine::Weapon::SetPosition(float x, float y)
{
	spriteWeapon->SetPosition(x, y);
}

void Engine::Weapon::SetRotation(float degree)
{
	spriteWeapon->SetRotation(degree);
}

void Engine::Weapon::SetFlipVertical(bool tf)
{
	spriteWeapon->SetFlipVertical(tf);
}

int Engine::Weapon::GetCurrentAmmo()
{
	return currentAmmo;
}



int Engine::Weapon::GetProjectilesSize()
{
	return 0;
}

Engine::BoundingBox* Engine::Weapon::GetProjectileBoundingBoxByIndex(int i)
{
	return 0;
}

vec2 Engine::Weapon::GetProjectilePositionByIndex(int i)
{
	return vec2(0);
}

void Engine::Weapon::RemoveProjectileByIndex(int i)
{
}

void Engine::Weapon::ReduceBulletInChamberByOne()
{
	this->currentAmmo -= 1;
}

void Engine::Weapon::Fire(vec2 playerPos, vec2 aimDir, float angleNoNegative)
{
}
