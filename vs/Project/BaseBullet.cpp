#include "BaseBullet.h"

Engine::BaseBullet::BaseBullet(Game* game)
{
	this->game = game;
	textureBullet = new Texture("Asset/Bullet/bullet-pistol.png");
	currVelo = { 0,0 };
}

void Engine::BaseBullet::Init()
{

}

void Engine::BaseBullet::Update()
{
	
}

void Engine::BaseBullet::Render()
{
	spriteBullet->Draw();
}

void Engine::BaseBullet::setCurrVelo(float x, float y) {
	currVelo = { x,y };
}

void Engine::BaseBullet::SetPosition(float x, float y)
{
	spriteBullet->SetPosition(x, y);
}

vec2 Engine::BaseBullet::getCurrVelo() {
	return currVelo;
}

vec2 Engine::BaseBullet::GetPosition()
{
	return spriteBullet->GetPosition();
}

void Engine::BaseBullet::BulletHit()
{
}

Engine::BoundingBox* Engine::BaseBullet::GetBoundingBox()
{
	return spriteBullet->GetBoundingBox();
}

