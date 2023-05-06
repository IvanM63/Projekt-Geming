#include "Enemy.h"

Engine::Enemy::Enemy(Game* game)
{
	this->game = game;
}

void Engine::Enemy::Init()
{
	//Definition
	texture = new Texture("Warrior_Sheet-Effect.png");
	sprite = new Sprite(texture, game->defaultSpriteShader, game->defaultQuad);

	sprite->SetNumXFrames(6);
	sprite->SetNumYFrames(17);
	sprite->AddAnimation("moving", 6, 13);

	sprite->PlayAnim("moving");
	sprite->SetScale(2);
	sprite->SetAnimationDuration(100);

	SetPosition(100, 0);


}

void Engine::Enemy::Update()
{
	sprite->Update(game->GetGameTime());

}

void Engine::Enemy::Render()
{
	sprite->Draw();
}

void Engine::Enemy::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
	currentEnemyPos = { x, y };
}

vec2 Engine::Enemy::GetPosition()
{
	return currentEnemyPos;
	
}
