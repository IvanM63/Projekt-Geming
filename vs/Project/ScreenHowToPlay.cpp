#include "ScreenHowToPlay.h"

Engine::ScreenHowToPlay::ScreenHowToPlay(Game* game, ScreenManager* manager) : Screen(game, manager)
{

}



void Engine::ScreenHowToPlay::Init()
{
	//Switch Screen Anim Out
	textureOut = new Texture("Asset/UI/SwitchScreen_Out.png");
	spriteOut = new Sprite(textureOut, game->defaultSpriteShader, game->defaultQuad);

	spriteOut->SetNumXFrames(1);
	spriteOut->SetNumYFrames(1);
	spriteOut->AddAnimation("normal", 0, 0);
	spriteOut->SetAnimationDuration(100);
	spriteOut->SetBoundToCamera(true);
	spriteOut->SetPosition(-2100, 0);

	isSwitching = false;

	//Switch Screen Anim In
	textureIn = new Texture("Asset/UI/SwitchScreen_In.png");
	spriteIn = new Sprite(textureIn, game->defaultSpriteShader, game->defaultQuad);

	spriteIn->SetNumXFrames(1);
	spriteIn->SetNumYFrames(1);
	spriteIn->AddAnimation("normal", 0, 0);
	spriteIn->SetAnimationDuration(100);
	spriteIn->SetBoundToCamera(true);
	spriteIn->SetPosition(-600, 0);

	//Came Init
	game->defaultSpriteShader->cameraPos = { 0,0 };

	howtoplayButton = new Texture("Asset/howtoplaybutton.png");

	textureTitle = new Texture("Asset/howtoplaybutton.png");
	spriteTitle = new Sprite(textureTitle, game->defaultSpriteShader, game->defaultQuad);
	spriteTitle->SetNumXFrames(1);
	spriteTitle->SetNumYFrames(1);
	spriteTitle->AddAnimation("idle", 0, 0);
	spriteTitle->PlayAnim("idle");
	spriteTitle->SetAnimationDuration(100);
	spriteTitle->SetBoundToCamera(true);

	MainMenuSprite = new Sprite(howtoplayButton, game->defaultSpriteShader, game->defaultQuad);
	MainMenuSprite->SetNumXFrames(5);
	MainMenuSprite->SetNumYFrames(4);
	MainMenuSprite->AddAnimation("normal", 0, 0);
	MainMenuSprite->AddAnimation("hover", 5, 9);
	MainMenuSprite->AddAnimation("press", 9, 9);
	MainMenuSprite->SetAnimationDuration(100);
	MainMenuSprite->SetBoundToCamera(true);

	NextSprite = new Sprite(howtoplayButton, game->defaultSpriteShader, game->defaultQuad);
	NextSprite->SetNumXFrames(5);
	NextSprite->SetNumYFrames(4);
	NextSprite->AddAnimation("normal", 1, 1);
	NextSprite->AddAnimation("hover", 10, 14);
	NextSprite->AddAnimation("press", 14, 14);
	/*if (currentpage == 1) {
	}
	else if (currentpage == 2) {
		NextSprite->AddAnimation("normal", 2, 2);
		NextSprite->AddAnimation("hover", 15, 19);
		NextSprite->AddAnimation("press", 19, 19);
	}*/
	NextSprite->SetAnimationDuration(100);
	NextSprite->SetBoundToCamera(true);

	//Create Buttons
	Button* mainmenuButton = new Button(MainMenuSprite, "mainmenu");
	mainmenuButton->SetPosition(0, game->setting->screenHeight - 100);
	buttons.push_back(mainmenuButton);
	Button* changepageButton = new Button(NextSprite, "changepage");
	changepageButton->SetPosition(game->setting->screenWidth - 337, game->setting->screenHeight - 100);
	buttons.push_back(changepageButton);

	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	//How To Play 1 move

		Player1 = new Texture("Asset/Character/CharacterV2.png");
		Player1Sprite = new Sprite(Player1, game->defaultSpriteShader, game->defaultQuad);
		Player1Sprite->SetNumXFrames(7);
		Player1Sprite->SetNumYFrames(4);
		Player1Sprite->AddAnimation("Walk-Horizontal", 21, 24);
		Player1Sprite->AddAnimation("Walk-Up", 7, 13);
		Player1Sprite->AddAnimation("Walk-Down", 14, 20);
		Player1Sprite->AddAnimation("idle", 0, 0);
		Player1Sprite->PlayAnim("Walk-Up");
		Player1Sprite->SetScale(2.5);
		Player1Sprite->SetPosition(game->setting->screenWidth * 1 / 3 - 250, game->setting->screenHeight * 3 / 5 - 100);
		Player1Sprite->SetAnimationDuration(175);
		Player1Sprite->SetFlipHorizontal(false);

		KeyBoardMove = new Texture("Asset/KeyboardMove.png");
		KeyBoardMoveSprite = new Sprite(KeyBoardMove, game->defaultSpriteShader, game->defaultQuad);
		KeyBoardMoveSprite->SetNumXFrames(4);
		KeyBoardMoveSprite->SetNumYFrames(1);
		KeyBoardMoveSprite->AddAnimation("idle", 0, 3);
		KeyBoardMoveSprite->PlayAnim("idle");
		KeyBoardMoveSprite->SetScale(2);
		KeyBoardMoveSprite->SetPosition(game->setting->screenWidth * 1 / 3 -240, game->setting->screenHeight * 2 / 5 -100);
		KeyBoardMoveSprite->SetAnimationDuration(1000);
		currentloop = 0;

	//How To Play 2 aim n shoot

		//mouse
		Mouse = new Texture("Asset/mouse.png");
		MouseSprite = new Sprite(Mouse, game->defaultSpriteShader, game->defaultQuad);
		MouseSprite->SetNumXFrames(2);
		MouseSprite->SetNumYFrames(1);
		MouseSprite->AddAnimation("idle", 0, 1);
		MouseSprite->PlayAnim("idle");
		MouseSprite->SetScale(1);
		MouseSprite->SetPosition(game->setting->screenWidth * 2 / 3 - 240, game->setting->screenHeight * 2 / 5 - 150);
		MouseSprite->SetAnimationDuration(1000);

		////PLayer Class
		//player2 = new Player(game);
		//player2->Init();
		//player2->SetPosition(game->setting->screenWidth * 2 / 3 - 100, game->setting->screenHeight * 3 / 5);

		////Weapon Class
		//weapon2 = new WeaponManager(game, player2);
		//weapon2->Init();

		////enemy
		//enemy2 = new Enemy(game);
		//enemy2->Init();
		//enemy2->SetPosition(game->setting->screenWidth * 2 / 3 + 100, game->setting->screenHeight * 3 / 5);

		////Impact Effect
		//textureImpact = new Texture("Asset/Weapon/Impact/impact01.png");
		//spriteImpact = new Sprite(textureImpact, game->defaultSpriteShader, game->defaultQuad);
		//spriteImpact->SetNumXFrames(5);
		//spriteImpact->SetNumYFrames(1);
		//spriteImpact->AddAnimation("default", 0, 4);
		//spriteImpact->PlayAnim("default");
		//spriteImpact->SetScale(1);
		//spriteImpact->SetAnimationDuration(150);

	//How To Play 3 switch weapon
			
		//keyboard
		KeyBoardSwitch = new Texture("Asset/KeyBoardSwitch.png");
		KeyBoardSwitchSprite = new Sprite(KeyBoardSwitch, game->defaultSpriteShader, game->defaultQuad);
		KeyBoardSwitchSprite->SetNumXFrames(2);
		KeyBoardSwitchSprite->SetNumYFrames(1);
		KeyBoardSwitchSprite->AddAnimation("idle", 0, 1);
		KeyBoardSwitchSprite->PlayAnim("idle");
		KeyBoardSwitchSprite->SetScale(2.5);
		KeyBoardSwitchSprite->SetPosition(game->setting->screenWidth * 3 / 3 - 240, game->setting->screenHeight * 2 / 5 - 100);
		KeyBoardSwitchSprite->SetAnimationDuration(1000);
		KeyBoardSwitchSprite->SetBoundToCamera(true);

		pistol3 = new Texture("Asset/Weapon/Pistol/Pistol.png");
		pistol3Sprite = new Sprite(pistol3, game->defaultSpriteShader, game->defaultQuad);
		pistol3Sprite->SetNumXFrames(4);
		pistol3Sprite->SetNumYFrames(2);
		pistol3Sprite->AddAnimation("idle", 0, 0);
		pistol3Sprite->PlayAnim("idle");
		pistol3Sprite->SetScale(1);
		pistol3Sprite->SetPosition(game->setting->screenWidth * 3 / 3 - 190, game->setting->screenHeight * 3 / 5 - 60);
		pistol3Sprite->SetAnimationDuration(102);
		pistol3Sprite->SetBoundToCamera(true);

		rifle3 = new Texture("Asset/Weapon/Rifle/Rifle_12F_Single.png");
		rifle3Sprite = new Sprite(rifle3, game->defaultSpriteShader, game->defaultQuad);
		rifle3Sprite->SetNumXFrames(12);
		rifle3Sprite->SetNumYFrames(1);
		rifle3Sprite->AddAnimation("idle", 0, 0);
		rifle3Sprite->AddAnimation("fire", 0, 11);
		rifle3Sprite->PlayAnim("idle");
		rifle3Sprite->SetScale(2.5);
		rifle3Sprite->SetPosition(game->setting->screenWidth * 3 / 3 - 250, game->setting->screenHeight * 3 / 5 - 100);
		rifle3Sprite->SetAnimationDuration(12);
		rifle3Sprite->SetBoundToCamera(true);

		player3sprite = new Sprite(Player1, game->defaultSpriteShader, game->defaultQuad);
		player3sprite->SetNumXFrames(7);
		player3sprite->SetNumYFrames(4);
		player3sprite->AddAnimation("idle", 0, 0);
		player3sprite->PlayAnim("idle");
		player3sprite->SetScale(2.5);
		player3sprite->SetPosition(game->setting->screenWidth * 3 / 3 - 250, game->setting->screenHeight * 3 / 5 - 100);
		player3sprite->SetAnimationDuration(175);
		player3sprite->SetFlipHorizontal(false);
		player3sprite->SetBoundToCamera(true);

		////PLayer Class
		//player3 = new Player(game);
		//player3->Init();
		//player3->SetPosition(game->setting->screenWidth * 3 / 3, game->setting->screenHeight * 3 / 5);

		////Weapon Class
		//weapon3 = new WeaponManager(game, player3);
		//weapon3->Init();

	//Create background
	game->SetBackgroundColor(30, 39, 73);


	//x = 980 || y = 720	

	//___________Input Manajer_______________//

	
	// Add input mappings
	game->inputManager->AddInputMapping("next", SDLK_DOWN);
	game->inputManager->AddInputMapping("prev", SDLK_UP);

	game->inputManager->AddInputMapping("press", SDLK_RETURN);

	game->inputManager->AddInputMapping("prev", SDLK_a);
	game->inputManager->AddInputMapping("next", SDLK_d);
	game->inputManager->AddInputMapping("next", SDLK_w);
	game->inputManager->AddInputMapping("prev", SDLK_s);

	//Set the background color
	//game->SetBackgroundColor(102, 195, 242);

}

void Engine::ScreenHowToPlay::Update()
{
	//How To Play 1 move
		Player1Sprite->Update(game->GetGameTime());
		KeyBoardMoveSprite->Update(game->GetGameTime());
		//string player1loop[4] = {"Walk-Up", "Walk-Horizontal", "Walk-Down", "Walk-Horizontal"};
		if (gametime1 >= 1000) {
			currentloop++;
			if(currentloop == 1) {
				Player1Sprite->PlayAnim("Walk-Horizontal");
				Player1Sprite->SetFlipHorizontal(true);
			}
			else if (currentloop == 2) {
				Player1Sprite->PlayAnim("Walk-Down");

			}
			else if (currentloop == 3) {
				Player1Sprite->PlayAnim("Walk-Horizontal");
				Player1Sprite->SetFlipHorizontal(false);

			}
			else if (currentloop == 4) {
				Player1Sprite->PlayAnim("Walk-Up");
				currentloop = 0;
			}
			gametime1 = 0;
		}
		gametime1 += game -> GetGameTime();
	
	////How To Play 2 aim n shoot
	//	player2->Update();
	//	enemy2->Update();
	//	weapon2->Update();
		MouseSprite->Update(game->GetGameTime());

	//
	////How To Play 3 switch
	//	player3->Update();
	//	weapon3->Update();
		KeyBoardSwitchSprite->Update(game->GetGameTime());
		if (gametime3 >= 1000) {
			if (currentweapon == 1) {
				currentweapon++;
			}
			else if (currentweapon == 2) {
				currentweapon = 1;
			}
			gametime3 = 0;
		}
		gametime3 += game->GetGameTime();
	
	// If user press "Quit" key then exit
	if (game->inputManager->IsKeyReleased("Quit")) {
		isSwitching = true;
		screenName = "MainMenu";
		//manager->switchScreen(ScreenState::MAIN_MENU);
		return;
	}

	//Switch Screen Anim Out
	spriteIn->Update(game->GetGameTime());
	spriteOut->Update(game->GetGameTime());

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

	//Get Pressed Key Information
	if (game->inputManager->IsKeyReleased("press")) {
		// Set current button to press state
		b = buttons[currentButtonIndex];
		b->SetButtonState(Engine::ButtonState::PRESS);
		// Turn isSwitching to true if button pressed
		isSwitching = true;

	}

	//Change Screen After Switch Screen Animation End
	if (b != NULL) {
		//std::cout << b->GetButtonName();

		if (currentSwitchTime > 750) {

			if ("mainmenu" == b->GetButtonName()) {
				manager->switchScreen(ScreenState::MAIN_MENU);
			}
			else if ("changepage" == b->GetButtonName()) {
				manager->switchScreen(ScreenState::HOW_TO_PLAY2);
			}

		}

	}

	// Update All buttons
	for (Button* b : buttons) {
		b->Update(game->GetGameTime());
	}

}

void Engine::ScreenHowToPlay::Render()
{
	//How to play 1 move
	KeyBoardMoveSprite->Draw();
	Player1Sprite->Draw();

	////How to play 2 aim n shoot

	//	player2->Render();

	//	//Render Weapon and Bullet
	//	weapon2->Render();
	//	for (size_t i = 0; i < bulletImpacts.size(); i++) {
	//		bulletImpacts[i]->Draw();
	//	}

	//	enemy2->Render();
	MouseSprite->Draw();
	////How to play 3 switch
	//	player2->Render();

	//	//Render Weapon and Bullet
	//	weapon2->Render();
	player3sprite->Draw();
	if (currentweapon == 1) {
		pistol3Sprite->Draw();
	}
	else if (currentweapon == 2) {
		rifle3Sprite->Draw();
	}
	KeyBoardSwitchSprite->Draw();
	
	//Render Background

	NextSprite->Draw();
	MainMenuSprite->Draw();
	//spriteTitle->Draw();

	//Render Bullet Impact
	

	//Render UI HARUS PALING BAWAH
	//enemiesLeftText->Draw();

	//Player Hit Red Screen

	//Switch Screen Animation
	spriteIn->Draw();
	spriteOut->Draw();
}

void Engine::ScreenHowToPlay::forDebug()
{

	if (duration >= 1000) {
		//std::cout << mouseWorldPos.x;
		//std::cout << playerPos.y;
		duration = 0;
	}
}


bool Engine::ScreenHowToPlay::getRandomBoolean(double truePercentage)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	return distribution(gen) < truePercentage;
}