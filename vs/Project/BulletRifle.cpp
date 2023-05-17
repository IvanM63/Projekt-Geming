#include "BulletRifle.h"

Engine::BulletRifle::BulletRifle(Game* game) : BaseBullet(game)
{
	this->game = game;
	textureBullet = new Texture("Asset/Bullet/bullet-rifle.png");
	currVelo = { 0,0 };
}

void Engine::BulletRifle::Init()
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

void Engine::BulletRifle::Update()
{
	spriteBullet->Update(game->GetGameTime());
}

void Engine::BulletRifle::Render()
{
	spriteBullet->Draw();
}

void Engine::BulletRifle::setCurrVelo(float x, float y) {
	currVelo = { x,y };
}

void Engine::BulletRifle::SetPosition(float x, float y)
{
	spriteBullet->SetPosition(x, y);
}

vec2 Engine::BulletRifle::getCurrVelo() {
	return currVelo;
}

vec2 Engine::BulletRifle::GetPosition()
{
	return spriteBullet->GetPosition();
}

Engine::BoundingBox* Engine::BulletRifle::GetBoundingBox()
{
	return spriteBullet->GetBoundingBox();
}