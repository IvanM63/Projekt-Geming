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

	sprite->SetBoundingBoxSize(sprite->GetScaleWidth() - 35, sprite->GetScaleHeight() - 18);

	SetPosition(0, 0);

	// This dot sprite is for visual debugging (to see the actual bounding box) 
	dotTexture = new Texture("dot.png");
	dotSprite1 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);
	dotSprite2 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);
	dotSprite3 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);
	dotSprite4 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);

}

void Engine::Player::Update()
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

void Engine::Player::Render()
{
	sprite->Draw();

	if (isDebug) {
		dotSprite1->Draw();
		dotSprite2->Draw();
		dotSprite3->Draw();
		dotSprite4->Draw();
	}
}

