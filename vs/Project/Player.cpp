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
	texture = new Texture("Asset/Character/CharacterV2.png");
	sprite = new Sprite(texture, game->defaultSpriteShader, game->defaultQuad);

	sprite->SetNumXFrames(7);
	sprite->SetNumYFrames(4);
	sprite->AddAnimation("Walk-Horizontal", 21, 24);
	sprite->AddAnimation("Walk-Up", 7, 13);
	sprite->AddAnimation("Walk-Down", 14, 20);

	sprite->AddAnimation("idle", 0, 0);
	sprite->PlayAnim("idle");
	sprite->SetScale(1);
	sprite->SetAnimationDuration(175);
	sprite->SetFlipHorizontal(false);
	//sprite->SetBoundToCamera(true);
	sprite->SetBoundingBoxSize(sprite->GetScaleWidth() - 15, sprite->GetScaleHeight() - 18);

	SetPosition(0, 0);

	// This dot sprite is for visual debugging (to see the actual bounding box) 
	dotTexture = new Texture("dot.png");
	dotSprite1 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);
	dotSprite2 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);
	dotSprite3 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);
	dotSprite4 = new Sprite(dotTexture, game->defaultSpriteShader, game->defaultQuad);

	//Displaying UI
	//Text
	healthText = new Text("lucon.ttf", 24, game->defaultTextShader);
	healthText->SetScale(1.0f);
	healthText->SetColor(255, 255, 255);
	healthText->SetPosition(10, game->setting->screenHeight - 100);

	//Debug
	isDebug = false;
}

void Engine::Player::Update()
{
	sprite->Update(game->GetGameTime());

	if (isDebug) {
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

	//Text Info
	healthText->SetText("HP : " + std::to_string(currentHealth));
	//healthText->SetPosition(game->setting->screenWidth / 2, game->setting->screenHeight / 2 + 100);

	//Time Counter Get Hit
	if (isHit) {
		currentHitCounter += game->GetGameTime();
		sprite->coloradjusment = { 255,255,255 };
	}
	if (currentHitCounter > 100) {
		sprite->coloradjusment = { 1.0f,1.0f,1.0f };
		currentHitCounter = 0;
		isHit = false;
	}
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

	//Render Text
	healthText->Draw();
}

