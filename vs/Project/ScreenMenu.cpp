#include "ScreenMenu.h"

Engine::ScreenMenu::ScreenMenu(Game* game, ScreenManager* manager) : Screen(game, manager)
{

}



void Engine::ScreenMenu::Init()
{
	// Create a Texture
	Texture* texture = new Texture("button.png");

	// Create Sprites
	Sprite* playSprite = new Sprite(texture, game->defaultSpriteShader, game->defaultQuad);
	playSprite->SetNumXFrames(5);
	playSprite->SetNumYFrames(4);
	playSprite->AddAnimation("normal",10 , 10);
	playSprite->AddAnimation("hover", 0, 4);
	playSprite->AddAnimation("press", 4, 4);
	playSprite->SetAnimationDuration(100);
	playSprite->SetBoundToCamera(true);

	Sprite* exitSprite = new Sprite(texture, game->defaultSpriteShader, game->defaultQuad);
	exitSprite->SetNumXFrames(5);
	exitSprite->SetNumYFrames(4);
	exitSprite->AddAnimation("normal", 5, 5);
	exitSprite->AddAnimation("hover", 15, 19);
	exitSprite->AddAnimation("press", 19, 19);
	exitSprite->SetAnimationDuration(100);
	exitSprite->SetBoundToCamera(true);

	textureTitle = new Texture("Asset/title.png");
	spriteTitle = new Sprite(textureTitle, game->defaultSpriteShader, game->defaultQuad);
	spriteTitle->SetNumXFrames(1);
	spriteTitle->SetNumYFrames(1);
	spriteTitle->AddAnimation("default", 0, 0);
	spriteTitle->PlayAnim("default");
	spriteTitle->SetAnimationDuration(30);
	spriteTitle->SetPosition(game->setting->screenWidth - 968, game->setting->screenWidth - 406);
	spriteTitle->SetBoundToCamera(true);

	//Create Buttons
	Button* playButton = new Button(playSprite, "play");
	playButton->SetPosition(game->setting->screenWidth - 337, 400);
	buttons.push_back(playButton);
	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition(game->setting->screenWidth - 337, 300);
	buttons.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Create Text
	text = new Text("8-bit Arcade In.ttf", 150, game->defaultTextShader);
	text->SetText("Start");
	text->SetPosition(325, game->setting->screenHeight - 150);
	text->SetColor(194, 202, 174);

	textoutline = new Text("8-bit Arcade In.ttf", 200, game->defaultTextShader);
	textoutline->SetText("Jombi Jombian");
	textoutline->SetPosition(325, game->setting->screenHeight - 180);
	textoutline->SetColor(73, 79, 57);

	// Add input mappings
	game->inputManager->AddInputMapping("next", SDLK_DOWN);
	game->inputManager->AddInputMapping("prev", SDLK_UP);
	game->inputManager->AddInputMapping("press", SDLK_RETURN);

}

void Engine::ScreenMenu::Update()
{
	// Set background
	game->SetBackgroundColor(30, 39, 73);

	if (game->inputManager->IsKeyReleased("next")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Next Button
		currentButtonIndex = currentButtonIndex < buttons.size() - 1 ? currentButtonIndex + 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (game->inputManager->IsKeyReleased("prev")) {
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
		if ("play" == b->GetButtonName()) {
			manager->switchScreen(ScreenState::IN_GAME);
		}
		else if ("exit" == b->GetButtonName()) {
			game->state = Engine::State::EXIT;
		}
	}

	// Update All buttons
	for (Button* b : buttons) {
		b->Update(game->GetGameTime());
	}
}

void Engine::ScreenMenu::Render()
{

	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
	// Render title
	//textoutline->Draw();
	//text->Draw();
	spriteTitle->Draw();

}




