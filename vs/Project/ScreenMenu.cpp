#include "ScreenMenu.h"

Engine::ScreenMenu::ScreenMenu(Game* game, ScreenManager* manager) : Screen(game, manager)
{

}



void Engine::ScreenMenu::Init()
{
	//BGM
	bgm = new Music("Asset/Sound/bgm.ogg");
	bgm->SetVolume(100);

	//Sound Effect
	soundSelection = new Sound("Asset/Sound/MainMenu/Bleep_05.ogg");
	soundSelection->SetVolume(100);

	soundComplete = new Sound("Asset/Sound/MainMenu/Complete_02.ogg");
	soundComplete->SetVolume(100);

	soundConfirm = new Sound("Asset/Sound/MainMenu/Confirm_01.ogg");
	soundConfirm->SetVolume(100);

	//Switch Screen Anim In
	textureIn = new Texture("Asset/UI/SwitchScreen_In.png");
	spriteIn = new Sprite(textureIn, game->defaultSpriteShader, game->defaultQuad);

	spriteIn->SetNumXFrames(1);
	spriteIn->SetNumYFrames(1);
	spriteIn->AddAnimation("normal", 0, 0);
	spriteIn->SetAnimationDuration(100);
	spriteIn->SetBoundToCamera(true);
	spriteIn->SetPosition(-600, 0);

	//Switch Screen Anim Out
	textureOut = new Texture("Asset/UI/SwitchScreen_Out.png");
	spriteOut = new Sprite(textureOut, game->defaultSpriteShader, game->defaultQuad);

	spriteOut->SetNumXFrames(1);
	spriteOut->SetNumYFrames(1);
	spriteOut->AddAnimation("normal", 0, 0);
	spriteOut->SetAnimationDuration(100);
	spriteOut->SetBoundToCamera(true);
	spriteOut->SetPosition(-2100, 0);

	b = NULL;
	isSwitching = false;

	// Create a Texture
	Texture* texture = new Texture("button.png");

	// Create Sprites
	Sprite* playSprite = new Sprite(texture, game->defaultSpriteShader, game->defaultQuad);
	playSprite->SetNumXFrames(5);
	playSprite->SetNumYFrames(4);
	playSprite->AddAnimation("normal",2 , 2);
	playSprite->AddAnimation("hover", 15, 19);
	playSprite->AddAnimation("press", 19, 19);
	playSprite->SetAnimationDuration(100);
	playSprite->SetBoundToCamera(true);

	Sprite* tutorialSprite = new Sprite(texture, game->defaultSpriteShader, game->defaultQuad);
	tutorialSprite->SetNumXFrames(5);
	tutorialSprite->SetNumYFrames(4);
	tutorialSprite->AddAnimation("normal", 0, 0);
	tutorialSprite->AddAnimation("hover", 10, 14);
	tutorialSprite->AddAnimation("press", 14, 14);
	tutorialSprite->SetAnimationDuration(100);
	tutorialSprite->SetBoundToCamera(true);

	Sprite* exitSprite = new Sprite(texture, game->defaultSpriteShader, game->defaultQuad);
	exitSprite->SetNumXFrames(5);
	exitSprite->SetNumYFrames(4);
	exitSprite->AddAnimation("normal", 1, 1);
	exitSprite->AddAnimation("hover", 5, 9);
	exitSprite->AddAnimation("press", 9, 9);
	exitSprite->SetAnimationDuration(100);
	exitSprite->SetBoundToCamera(true);

	texturekuru = new Texture("Asset/Character/kurukuru.png");
	spritekuru = new Sprite(texturekuru, game->defaultSpriteShader, game->defaultQuad);
	spritekuru->SetNumXFrames(6);
	spritekuru->SetNumYFrames(1);
	spritekuru->AddAnimation("normal", 0, 4);
	spritekuru->PlayAnim("normal");
	spritekuru->SetAnimationDuration(100);
	spritekuru->SetScale(5);
	spritekuru->SetPosition(387, game->setting->screenHeight / 2 - 200);
	spritekuru->SetBoundToCamera(true);

	texturejombi = new Texture("Asset/Enemy/Zombie.png");
	spritejombi = new Sprite(texturejombi, game->defaultSpriteShader, game->defaultQuad);
	spritejombi->SetNumXFrames(13);
	spritejombi->SetNumYFrames(6);
	spritejombi->AddAnimation("idle", 0, 7);
	spritejombi->PlayAnim("idle");
	spritejombi->SetAnimationDuration(100);
	spritejombi->SetScale(10);
	spritejombi->SetPosition(700, -100);
	spritejombi->SetFlipHorizontal(true);
	spritejombi->SetBoundToCamera(true);

	spritejombi2 = new Sprite(texturejombi, game->defaultSpriteShader, game->defaultQuad);
	spritejombi2->SetNumXFrames(13);
	spritejombi2->SetNumYFrames(6);
	spritejombi2->AddAnimation("idle", 0, 7);
	spritejombi2->PlayAnim("idle");
	spritejombi2->SetAnimationDuration(100);
	spritejombi2->SetScale(10);
	spritejombi2->SetPosition(230, game->setting->screenHeight-200);
	spritejombi2->SetFlipVertical(true);
	spritejombi2->SetBoundToCamera(true);

	spritejombi3 = new Sprite(texturejombi, game->defaultSpriteShader, game->defaultQuad);
	spritejombi3->SetNumXFrames(13);
	spritejombi3->SetNumYFrames(6);
	spritejombi3->AddAnimation("moving", 26, 33);
	spritejombi3->PlayAnim("moving");
	spritejombi3->SetAnimationDuration(100);
	spritejombi3->SetScale(10);
	spritejombi3->SetPosition(-150, game->setting->screenHeight/2 -200);
	spritejombi3->SetBoundToCamera(true);

	textureTitle = new Texture("Asset/title.png");
	spriteTitle = new Sprite(textureTitle, game->defaultSpriteShader, game->defaultQuad);
	spriteTitle->SetNumXFrames(1);
	spriteTitle->SetNumYFrames(1);
	spriteTitle->AddAnimation("default", 0, 0);
	spriteTitle->PlayAnim("default");
	spriteTitle->SetScale(0.8);
	spriteTitle->SetAnimationDuration(30);
	spriteTitle->SetPosition(game->setting->screenWidth - 618, game->setting->screenHeight - 206);
	spriteTitle->SetBoundToCamera(true);

	//Create Buttons
	Button* playButton = new Button(playSprite, "play");
	playButton->SetPosition(game->setting->screenWidth - 413, 350);
	buttons.push_back(playButton);
	Button* tutorialButton = new Button(tutorialSprite, "tutorial");
	tutorialButton->SetPosition(game->setting->screenWidth - 413, 235);
	buttons.push_back(tutorialButton);
	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition(game->setting->screenWidth - 413, 120);
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
	game->inputManager->AddInputMapping("next", SDLK_RIGHT);
	game->inputManager->AddInputMapping("prev", SDLK_UP);
	game->inputManager->AddInputMapping("prev", SDLK_LEFT);
	game->inputManager->AddInputMapping("press", SDLK_RETURN);

}

void Engine::ScreenMenu::Update()
{
	//BGM Play
	if (isFirstInit == false) {
		bgm->Play(true);

		//Let Go
		isFirstInit = true;
	}

	//Switch Screen Anim Out
	spriteOut->Update(game->GetGameTime());
	spriteIn->Update(game->GetGameTime());
	spritekuru->Update(game->GetGameTime());
	spritejombi->Update(game->GetGameTime());
	spritejombi2->Update(game->GetGameTime());
	spritejombi3->Update(game->GetGameTime());

	//Switch Anim In
	if (spriteIn->GetPosition().x < 1400) {
		spriteIn->SetPosition(spriteIn->GetPosition().x + 50, 0);
	}

	//Switch Anim Out
	if (isSwitching) {
		currentSwitchTime += game->GetGameTime();
		if (spriteOut->GetPosition().x < -25) {
			spriteOut->SetPosition(spriteOut->GetPosition().x + 50, 0);
		}

	}
	

	// Set background
	game->SetBackgroundColor(30, 39, 73);

	if (game->inputManager->IsKeyReleased("next")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Next Button
		currentButtonIndex = currentButtonIndex < buttons.size() - 1 ? currentButtonIndex + 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
		soundSelection->Play(false);
	}

	if (game->inputManager->IsKeyReleased("prev")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Prev Button
		currentButtonIndex = currentButtonIndex > 0 ? currentButtonIndex - 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
		soundSelection->Play(false);
	}

	//Get Pressed Key Information
	if (game->inputManager->IsKeyReleased("press")) {
		// Set current button to press state
		b = buttons[currentButtonIndex];
		b->SetButtonState(Engine::ButtonState::PRESS);
		// Turn isSwitching to true if button pressed
		isSwitching = true;
		soundComplete->Play(false);
	}

	//Change Screen After Switch Screen Animation End
	if (b != NULL) {
		//std::cout << b->GetButtonName();

		if (currentSwitchTime > 750) {

			if ("play" == b->GetButtonName()) {
				//BGM Stop
				bgm->Stop();

				manager->switchScreen(ScreenState::IN_GAME);
			}
			else if ("tutorial" == b->GetButtonName()) {
				manager->switchScreen(ScreenState::HOW_TO_PLAY);
			}
			else if ("exit" == b->GetButtonName()) {
				game->state = Engine::State::EXIT;
			}
			
		}

	}

	
	//Update Switch Time
	

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
	spritekuru->Draw();
	spritejombi->Draw();
	spritejombi2->Draw();
	spritejombi3->Draw();

	//Switch Screen Anim Out
	spriteOut->Draw();
	spriteIn->Draw();
}




