#include "BaseCharacter.h"

Engine::BaseCharacter::BaseCharacter(Game* game)
{
	this->game = game;
	this->health = 100;
	this->isDebug = true;
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
	this->health = this->health - damage;
}

void Engine::BaseCharacter::setHealth(int health)
{
	this->health = health;
}

int Engine::BaseCharacter::getHealth()
{
	return health;
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
