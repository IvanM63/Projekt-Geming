#include "Pistol.h"

Engine::Pistol::Pistol(Game* game)
{
	this->game = game;
	this->totalAmmo = 12;
	this->currentAmmo = 12;
	this->reloadTime = 1;
	this->fireRate = 1;
}

Engine::Pistol::~Pistol()
{
}

void Engine::Pistol::Init()
{
	texturePistol = new Texture("turtle.png");
	spritePistol = new Sprite(texturePistol, game->defaultSpriteShader, game->defaultQuad);

	spritePistol->SetNumXFrames(14);
	spritePistol->SetNumYFrames(4);
	spritePistol->AddAnimation("idle", 1, 2);
	spritePistol->AddAnimation("fire", 42, 49);
	
	spritePistol->PlayAnim("fire");
	spritePistol->SetScale(2);
	spritePistol->SetAnimationDuration(175);

	spritePistol->SetPosition(300, 300);
}

void Engine::Pistol::Update()
{
	spritePistol->Update(game->GetGameTime());
}

void Engine::Pistol::Render()
{
	spritePistol->Draw();
}
