#include "Enemy.h"

Engine::Enemy::Enemy(Game* game) : BaseCharacter(game)
{
}

Engine::Enemy::~Enemy()
{

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

	//Set Bounding Box
	//sprite->SetSize(150, 32);
	sprite->SetBoundingBoxSize(sprite->GetScaleWidth() - (16 * sprite->GetScale()),
		sprite->GetScaleHeight() - (4 * sprite->GetScale()));

	// This dot sprite is for visual debugging (to see the actual bounding box) 
	dotTexture = new Texture("dot.png");
	dotSprite1 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);
	dotSprite2 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);
	dotSprite3 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);
	dotSprite4 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);
}

void Engine::Enemy::Update()
{
	sprite->Update(game->GetGameTime());

	//Shape for debug
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
