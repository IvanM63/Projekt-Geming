#include "Ammo.h"

Engine::Ammo::Ammo(Game* game)
{
	this->game = game;
}

void Engine::Ammo::Init()
{
	textureAmmo = new Texture("Asset/Weapon/Rifle/ammo-rifle.png");
	spriteAmmo = new Sprite(textureAmmo, game->defaultSpriteShader, game->defaultQuad);

	spriteAmmo->SetNumXFrames(1);
	spriteAmmo->SetNumYFrames(1);
	spriteAmmo->AddAnimation("default", 0, 0);
	
	spriteAmmo->PlayAnim("default");
	spriteAmmo->SetScale(1.3);
	spriteAmmo->SetAnimationDuration(100);

	//Randomly Generate ammo in range (6,15)
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(4, 12);
	amount = distribution(gen);
}

void Engine::Ammo::Update()
{
	spriteAmmo->Update(game->GetGameTime());
}

void Engine::Ammo::Render()
{
	spriteAmmo->Draw();
}

void Engine::Ammo::SetPosition(float x, float y)
{
	spriteAmmo->SetPosition(x, y);
}

int Engine::Ammo::GetAmount()
{
	return this->amount;
}
