#include "Player.h"

Engine::Player::Player(Game* game) : BaseCharacter(game)
{
}

Engine::Player::~Player()
{
}

void Engine::Player::Init()
{
	//Player Sprite
	texture = new Texture("turtles.png");
	sprite = new Sprite(texture, game->defaultSpriteShader, game->defaultQuad);

	sprite->SetNumXFrames(14);
	sprite->SetNumYFrames(4);
	sprite->AddAnimation("spikes-out", 42, 49);

	sprite->AddAnimation("walk", 28, 41);
	sprite->PlayAnim("spikes-out");
	sprite->SetScale(2);
	sprite->SetAnimationDuration(175);
	//sprite2->SetFlipHorizontal(true);

	SetPosition(0, 0);
}

void Engine::Player::Update()
{
	sprite->Update(game->GetGameTime());
}

void Engine::Player::Render()
{
	sprite->Draw();
}

