#include "Projectile.h"

Engine::Projectile::Projectile(Game* game)
{
	this->game = game;
	textureBullet = new Texture("Asset/Bullet/bullet-pistol.png");
	currVelo = { 0,0 };
}

void Engine::Projectile::Init()
{
	
	spriteBullet = new Sprite(textureBullet, game->defaultSpriteShader, game->defaultQuad);

	spriteBullet->SetNumXFrames(4);
	spriteBullet->SetNumYFrames(1);
	spriteBullet->AddAnimation("default", 0, 3);

	spriteBullet->PlayAnim("default");
	spriteBullet->SetScale(2.0);
	spriteBullet->SetAnimationDuration(100);

	//Set Bounding Box
	spriteBullet->SetBoundingBoxSize(spriteBullet->GetScaleWidth() - (16 * spriteBullet->GetScale()) - 40,
		spriteBullet->GetScaleHeight() - (4 * spriteBullet->GetScale()));
}

void Engine::Projectile::Update()
{
	spriteBullet->Update(game->GetGameTime());
}

void Engine::Projectile::Render()
{
	spriteBullet->Draw();
}

void Engine::Projectile::setCurrVelo(float x, float y) {
	currVelo = { x,y };
}

void Engine::Projectile::SetPosition(float x, float y)
{
	spriteBullet->SetPosition(x, y);
}

vec2 Engine::Projectile::getCurrVelo() {
	return currVelo;
}

vec2 Engine::Projectile::GetPosition()
{
	return spriteBullet->GetPosition();
}

Engine::BoundingBox* Engine::Projectile::GetBoundingBox()
{
	return spriteBullet->GetBoundingBox();
}
