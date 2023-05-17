#include "BaseCharacter.h"

Engine::BaseCharacter::BaseCharacter(Game* game)
{
	this->game = game;
	this->maxHealth = 100;
	this->currentHealth = maxHealth;
	//this->isDebug = true;
}

Engine::BaseCharacter::~BaseCharacter()
{
}

void Engine::BaseCharacter::Init()
{

}

void Engine::BaseCharacter::Update()
{
	
}

void Engine::BaseCharacter::Render()
{
	
}

void Engine::BaseCharacter::attack()
{
}

void Engine::BaseCharacter::takeDamage(int damage)
{
	this->currentHealth = this->currentHealth - damage;
}

void Engine::BaseCharacter::setHealth(int maxHealth)
{
	this->maxHealth = maxHealth;
}

int Engine::BaseCharacter::getHealth()
{
	return currentHealth;
}

void Engine::BaseCharacter::SetRotation(float degree)
{
	sprite->SetRotation(degree);
}

void Engine::BaseCharacter::SetFlipVertical(bool tf)
{
	sprite->SetFlipVertical(tf);
}

void Engine::BaseCharacter::SetFlipHorizontal(bool tf)
{
	sprite->SetFlipHorizontal(tf);
}

void Engine::BaseCharacter::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
}

vec2 Engine::BaseCharacter::GetPosition()
{
	return sprite->GetPosition();
}

void Engine::BaseCharacter::move(vec2 location)
{
	sprite->SetPosition(sprite->GetPosition().x + location.x, sprite->GetPosition().y + location.y);
}

void Engine::BaseCharacter::setDebug(bool is)
{
	this->isDebug = is;
}
