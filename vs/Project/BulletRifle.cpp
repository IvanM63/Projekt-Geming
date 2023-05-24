#include "BulletRifle.h"

Engine::BulletRifle::BulletRifle(Game* game) : BaseBullet(game)
{
	this->game = game;
	textureBullet = new Texture("Asset/Bullet/bullet-rifle.png");
	currVelo = { 0,0 };
}

void Engine::BulletRifle::Init()
{
	//Bullet Impact
	textureImpact = new Texture("Asset/Weapon/Impact/impact01.png");
	spriteImpact = new Sprite(textureImpact, game->defaultSpriteShader, game->defaultQuad);
	spriteImpact->SetNumXFrames(5);
	spriteImpact->SetNumYFrames(1);
	spriteImpact->AddAnimation("default", 0, 4);
	spriteImpact->PlayAnim("default");
	spriteImpact->SetScale(2);
	spriteImpact->SetAnimationDuration(50);
	//spriteImpact->SetPosition(spriteBullet->GetPosition().x, spriteBullet->GetPosition().y);

	//Sprite Bullet
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
	spriteImpact->Update(game->GetGameTime());

	if (isHit) {
		spriteBullet->SetPosition(spriteBullet->GetPosition().x, spriteBullet->GetPosition().y);
	}
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

void Engine::BulletRifle::BulletHit()
{
	isHit = true;
	
}

Engine::BoundingBox* Engine::BulletRifle::GetBoundingBox()
{
	return spriteBullet->GetBoundingBox();
}