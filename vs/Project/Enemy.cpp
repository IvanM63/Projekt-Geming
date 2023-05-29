#include "Enemy.h"

Engine::Enemy::Enemy(Game* game) : BaseCharacter(game)
{
	
}

Engine::Enemy::~Enemy()
{

}

void Engine::Enemy::Init()
{
	//Definition Sprite
	texture = new Texture("Asset/Enemy/Zombie.png");
	sprite = new Sprite(texture, game->defaultSpriteShader, game->defaultQuad);

	sprite->SetNumXFrames(13);
	sprite->SetNumYFrames(6);
	sprite->AddAnimation("moving", 26, 33);
	sprite->AddAnimation("idle", 0, 7);
	sprite->AddAnimation("attack", 13, 19);
	sprite->AddAnimation("dies", 65, 74);

	sprite->PlayAnim("idle");
	sprite->SetScale(3);
	sprite->SetAnimationDuration(100);

	//Set Bounding Box
	//sprite->SetSize(150, 32);
	sprite->SetBoundingBoxSize(sprite->GetScaleWidth()-100, sprite->GetScaleHeight()-20);

	// This dot sprite is for visual debugging (to see the actual bounding box) 
	dotTexture = new Texture("dot.png");
	dotSprite1 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);
	dotSprite2 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);
	dotSprite3 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);
	dotSprite4 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);

	isDebug = false;

	//Enemy Stat Init()
	//Health
	maxHealth = 120;
	currentHealth = maxHealth;
	//DPS
	int fireRate = 500;
	int currentFireRate = fireRate;

}

void Engine::Enemy::Update()
{
	sprite->Update(game->GetGameTime());

	//Shape for debug
	if (isDebug) {
		BoundingBox* bb = sprite->GetBoundingBox();
		dotSprite1->SetPosition(bb->GetVertices()[0].x - (0.5f * dotSprite1->GetScaleWidth()),
			bb->GetVertices()[0].y - (0.5f * dotSprite1->GetScaleHeight()));
		dotSprite2->SetPosition(bb->GetVertices()[1].x - (0.5f * dotSprite2->GetScaleWidth()),
			bb->GetVertices()[1].y - (0.5f * dotSprite2->GetScaleHeight()));
		dotSprite3->SetPosition(bb->GetVertices()[2].x - (0.5f * dotSprite3->GetScaleWidth()),
			bb->GetVertices()[2].y - (0.5f * dotSprite3->GetScaleHeight()));
		dotSprite4->SetPosition(bb->GetVertices()[3].x - (0.5f * dotSprite4->GetScaleWidth()),
			bb->GetVertices()[3].y - (0.5f * dotSprite3->GetScaleHeight()));
	}
	

	//CalcFireRate
	if (currentFireRate >= fireRate) {
		currentFireRate = 0;
	}

	currentFireRate += game->deltaTime;
}

void Engine::Enemy::Render()
{
	sprite->Draw();

	if (isDebug) {
		dotSprite1->Draw();
		dotSprite2->Draw();
		dotSprite3->Draw();
		dotSprite4->Draw();
	}

}

void Engine::Enemy::SetDirection(float x, float y)
{
	this->direction.x = x;
	this->direction.y = y;
}

vec2 Engine::Enemy::GetDirection()
{
	return this->direction;
}

void Engine::Enemy::SetSpeed(float speed)
{
	this->speed = speed;
}

float Engine::Enemy::GetSpeed()
{
	return this->speed;
}

void Engine::Enemy::SetVelocity(float x, float y)
{
	this->velocity.x = x;
	this->velocity.y = y;
}

vec2 Engine::Enemy::GetVelocity()
{
	return velocity;
}

void Engine::Enemy::MoveWithVelocity()
{
	sprite->SetPosition(sprite->GetPosition().x + velocity.x * game->deltaTime, sprite->GetPosition().y + velocity.y * game->deltaTime);
}

Engine::BoundingBox* Engine::Enemy::GetBoundingBox()
{
	return sprite->GetBoundingBox();
}

vec2 Engine::Enemy::GetBoundingBoxCenterPoint()
{
	return sprite->GetBoundingBoxCenter();
}

int Engine::Enemy::GetDamage()
{
	if (currentFireRate >= fireRate) {
		currentFireRate = 0;
		return damage;
	}
	else {
		return 0;
	}
}
