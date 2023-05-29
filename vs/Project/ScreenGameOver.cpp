#include "ScreenGameOver.h"

Engine::ScreenGameOver::ScreenGameOver(Game* game, ScreenManager* manager) : Screen(game, manager)
{
}

Engine::ScreenGameOver::~ScreenGameOver()
{
}

void Engine::ScreenGameOver::Init()
{
	//Selection Texture
	Texture* texture = new Texture("Asset/UI/button_over.png");

	//Selection Sprite
	Sprite* tryAgainSprite = new Sprite(texture, game->defaultSpriteShader, game->defaultQuad);
	tryAgainSprite->SetNumXFrames(6);
	tryAgainSprite->SetNumYFrames(1);
	tryAgainSprite->AddAnimation("normal", 0, 0);
	tryAgainSprite->AddAnimation("hover", 1, 2);
	//tryAgainSprite->AddAnimation("press", 3, 4);
	tryAgainSprite->SetAnimationDuration(400);
	tryAgainSprite->SetBoundToCamera(true);

	Sprite* giveUpSprite = new Sprite(texture, game->defaultSpriteShader, game->defaultQuad);
	giveUpSprite->SetNumXFrames(6);
	giveUpSprite->SetNumYFrames(1);
	giveUpSprite->AddAnimation("normal", 3, 3);
	giveUpSprite->AddAnimation("hover", 4, 5);
	//giveUpSprite->AddAnimation("press", 0, 1);
	giveUpSprite->SetAnimationDuration(400);
	giveUpSprite->SetBoundToCamera(true);

	//Create Buttons
	Button* tryAgainButton = new Button(tryAgainSprite, "tryAgain");
	tryAgainButton->SetPosition(game->setting->screenWidth / 2 - 190, game->setting->screenHeight / 2 - 200);
	buttons.push_back(tryAgainButton);
	Button* giveUpButton = new Button(giveUpSprite, "giveUp");
	giveUpButton->SetPosition(game->setting->screenWidth / 2 + 70, game->setting->screenHeight / 2 - 200);
	buttons.push_back(giveUpButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Add input mappings
	game->inputManager->AddInputMapping("press", SDLK_RETURN);

	//Score Text
	scoreText = new Text("PressStart2P.ttf", 15, game->defaultTextShader);
	scoreText->SetScale(1.0f);
	scoreText->SetColor(255, 255, 255);

	//Game Over Text
	gameText = new Text("PressStart2P.ttf", 96, game->defaultTextShader);
	gameText->SetScale(1.0f);
	gameText->SetColor(255, 255, 255);
	overText = new Text("PressStart2P.ttf", 96, game->defaultTextShader);
	overText->SetScale(1.0f);
	overText->SetColor(255, 255, 255);

	gameText->SetText("GAME");
	gameText->SetPosition(game->setting->screenWidth / 2 - 225, game->setting->screenHeight / 2 + 200);
	overText->SetText("OVER");
	overText->SetPosition(game->setting->screenWidth / 2 - 125, game->setting->screenHeight / 2 + 100);

	//Ghost Sprite
	ghostTexture = new Texture("Asset/Character/ghost.png");
	ghostSprite = new Sprite(ghostTexture, game->defaultSpriteShader, game->defaultQuad);

	ghostSprite->SetNumXFrames(4);
	ghostSprite->SetNumYFrames(1);
	ghostSprite->AddAnimation("idle", 0, 3);

	ghostSprite->PlayAnim("idle");
	ghostSprite->SetScale(2);
	ghostSprite->SetAnimationDuration(175);
	ghostSprite->SetFlipHorizontal(false);
	ghostSprite->SetBoundToCamera(true);

	ghostSprite->SetPosition(game->setting->screenWidth/2 - 20, game->setting->screenHeight / 2 - 30);

	//White Screen
	whiteTexture = new Texture("Asset/white.png");
	whiteSprite = new Sprite(whiteTexture, game->defaultSpriteShader, game->defaultQuad);

	whiteSprite->SetNumXFrames(1);
	whiteSprite->SetNumYFrames(1);
	whiteSprite->AddAnimation("idle", 0, 0);
	
	whiteSprite->PlayAnim("idle");
	whiteSprite->SetScale(2);
	whiteSprite->SetAnimationDuration(175);
	whiteSprite->SetFlipHorizontal(false);
	whiteSprite->SetBoundToCamera(true);
	
	whiteSprite->SetPosition(0, 0);
	//bg color
	game->SetBackgroundColor(29, 38, 59);
}

void Engine::ScreenGameOver::Update()
{
	ghostSprite->Update(game->GetGameTime());
	whiteSprite->Update(game->GetGameTime());

	//Score Text
	scoreText->SetText("Score: " + std::to_string(game->setting->score));
	scoreText->SetPosition(game->setting->screenWidth / 2 - 75, game->setting->screenHeight / 2 - 90);

	if (game->inputManager->IsKeyReleased("walk-right")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Next Button
		currentButtonIndex = currentButtonIndex < buttons.size() - 1 ? currentButtonIndex + 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (game->inputManager->IsKeyReleased("walk-left")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Prev Button
		currentButtonIndex = currentButtonIndex > 0 ? currentButtonIndex - 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}


	if (game->inputManager->IsKeyReleased("press")) {
		// Set current button to press state
		Button* b = buttons[currentButtonIndex];
		b->SetButtonState(Engine::ButtonState::PRESS);
		// If play button then go to InGame, exit button then exit
		if ("tryAgain" == b->GetButtonName()) {
			manager->switchScreen(ScreenState::IN_GAME);
		}
		else if ("giveUp" == b->GetButtonName()) {
			manager->switchScreen(ScreenState::MAIN_MENU);
		}
	}

	// Update All buttons
	for (Button* b : buttons) {
		b->Update(game->GetGameTime());
	}
	
}

void Engine::ScreenGameOver::Render()
{
	ghostSprite->Draw();

	if (whiteCounter < 250) {
		whiteSprite->Draw();
		whiteCounter += game->GetGameTime();
	}

	//Draw Text
	gameText->Draw();
	overText->Draw();
	scoreText->Draw();

	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
	
}
