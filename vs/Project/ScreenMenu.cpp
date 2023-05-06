#include "ScreenMenu.h"

Engine::ScreenMenu::ScreenMenu(Game* game, ScreenManager* manager) : Screen(game, manager)
{

}



void Engine::ScreenMenu::Init()
{
	// Create a Texture
	Texture* texture = new Texture("buttons.png");

	// Create Sprites
	Sprite* playSprite = new Sprite(texture, game->defaultSpriteShader, game->defaultQuad);
	playSprite->SetNumXFrames(6);
	playSprite->SetNumYFrames(1);
	playSprite->AddAnimation("normal", 5, 5);
	playSprite->AddAnimation("hover", 3, 4);
	playSprite->AddAnimation("press", 3, 4);
	playSprite->SetAnimationDuration(400);

	Sprite* exitSprite = new Sprite(texture, game->defaultSpriteShader, game->defaultQuad);
	exitSprite->SetNumXFrames(6);
	exitSprite->SetNumYFrames(1);
	exitSprite->AddAnimation("normal", 2, 2);
	exitSprite->AddAnimation("hover", 0, 1);
	exitSprite->AddAnimation("press", 0, 1);
	exitSprite->SetAnimationDuration(400);

	//Create Buttons
	Button* playButton = new Button(playSprite, "play");
	playButton->SetPosition((game->setting->screenWidth / 2) - (playSprite->GetScaleWidth() / 2),
		400);
	buttons.push_back(playButton);
	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition((game->setting->screenWidth / 2) - (exitSprite->GetScaleWidth() / 2),
		250);
	buttons.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Create Text
	text = new Text("8-bit Arcade In.ttf", 100, game->defaultTextShader);
	text->SetText("The Spawning Turtle");
	text->SetPosition(60, game->setting->screenHeight - 100);
	text->SetColor(235, 229, 52);

	// Add input mappings
	game->inputManager->AddInputMapping("next", SDLK_DOWN);
	game->inputManager->AddInputMapping("prev", SDLK_UP);
	game->inputManager->AddInputMapping("press", SDLK_RETURN);

}

void Engine::ScreenMenu::Update()
{
	// Set background
	game->SetBackgroundColor(52, 155, 235);

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
	text->Draw();


}




