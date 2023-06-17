#include "ScreenHowToPlay2.h"

Engine::ScreenHowToPlay2::ScreenHowToPlay2(Game* game, ScreenManager* manager) : Screen(game, manager)
{

}



void Engine::ScreenHowToPlay2::Init()
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
	
	PrevSprite = new Sprite(howtoplayButton, game->defaultSpriteShader, game->defaultQuad);
	PrevSprite->SetNumXFrames(5);
	PrevSprite->SetNumYFrames(4); 
	PrevSprite->AddAnimation("normal", 2, 2);
	PrevSprite->AddAnimation("hover", 15, 19);
	PrevSprite->AddAnimation("press", 19, 19);
	PrevSprite->SetAnimationDuration(100);
	PrevSprite->SetBoundToCamera(true);

	//Create Buttons
	Button* mainmenuButton = new Button(MainMenuSprite, "mainmenu");
	mainmenuButton->SetPosition(0, game->setting->screenHeight - 100);
	buttons.push_back(mainmenuButton);
	Button* changepageButton = new Button(PrevSprite, "changepage");
	changepageButton->SetPosition(game->setting->screenWidth - 337, game->setting->screenHeight - 100);
	buttons.push_back(changepageButton);

	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);


	Player1 = new Texture("Asset/Character/CharacterV2.png");
	pistol3 = new Texture("Asset/Weapon/Pistol/Pistol.png");
	rifle3 = new Texture("Asset/Weapon/Rifle/Rifle_12F_Single.png");

//How To Play 4 Reload
	//keyboard
	KeyBoardReload = new Texture("Asset/KeyBoardReload.png");
	KeyBoardReloadSprite = new Sprite(KeyBoardReload, game->defaultSpriteShader, game->defaultQuad);
	KeyBoardReloadSprite->SetNumXFrames(4);
	KeyBoardReloadSprite->SetNumYFrames(1);
	KeyBoardReloadSprite->AddAnimation("idle", 0, 3);
	KeyBoardReloadSprite->PlayAnim("idle");
	KeyBoardReloadSprite->SetScale(2.5);
	KeyBoardReloadSprite->SetPosition(game->setting->screenWidth * 1 / 3 - 240, game->setting->screenHeight * 2 / 5 - 100);
	KeyBoardReloadSprite->SetAnimationDuration(1000);
	KeyBoardReloadSprite->SetBoundToCamera(true);

	rifle4Sprite = new Sprite(rifle3, game->defaultSpriteShader, game->defaultQuad);
	rifle4Sprite->SetNumXFrames(12);
	rifle4Sprite->SetNumYFrames(1);
	rifle4Sprite->AddAnimation("idle", 0, 0);
	rifle4Sprite->AddAnimation("fire", 0, 11);
	rifle4Sprite->PlayAnim("idle");
	rifle4Sprite->SetScale(2.5);
	rifle4Sprite->SetPosition(game->setting->screenWidth * 1 / 3 - 250, game->setting->screenHeight * 3 / 5 - 100);
	rifle4Sprite->SetAnimationDuration(12);
	rifle4Sprite->SetBoundToCamera(true);

	player4sprite = new Sprite(Player1, game->defaultSpriteShader, game->defaultQuad);
	player4sprite->SetNumXFrames(7);
	player4sprite->SetNumYFrames(4);
	player4sprite->AddAnimation("idle", 0, 0);
	player4sprite->PlayAnim("idle");
	player4sprite->SetScale(2.5);
	player4sprite->SetPosition(game->setting->screenWidth * 1 / 3 - 250, game->setting->screenHeight * 3 / 5 - 100);
	player4sprite->SetAnimationDuration(175);
	player4sprite->SetFlipHorizontal(false);
	player4sprite->SetBoundToCamera(true);

	//Reload Bar UI
	Reload = new Texture("Asset/UI/reloadBar.png");

	ReloadSprite.push_back(new Sprite(Reload, game->defaultSpriteShader, game->defaultQuad));
	ReloadSprite.push_back(new Sprite(Reload, game->defaultSpriteShader, game->defaultQuad));
	ReloadSprite.push_back(new Sprite(Reload, game->defaultSpriteShader, game->defaultQuad));

	for (size_t i = 0; i < ReloadSprite.size(); i++) {
		ReloadSprite[i]->SetNumXFrames(1);
		ReloadSprite[i]->SetNumYFrames(3);
		ReloadSprite[i]->AddAnimation("idle", i, i);
		ReloadSprite[i]->PlayAnim("idle");
		ReloadSprite[i]->SetBoundToCamera(true);
		ReloadSprite[i]->SetPosition(game->setting->screenWidth * 1 / 3 - 250, game->setting->screenHeight * 4 / 5 - 100);

		if (i == 1) {
			ReloadSprite[i]->SetSize(ReloadSprite[i]->GetScaleWidth(), ReloadSprite[i]->GetScaleHeight() * 3);
		}
	}



	//How To Play 5 Damage

	player5sprite = new Sprite(Player1, game->defaultSpriteShader, game->defaultQuad);
	player5sprite->SetNumXFrames(7);
	player5sprite->SetNumYFrames(4);
	player5sprite->AddAnimation("idle", 0, 0);
	player5sprite->PlayAnim("idle");
	player5sprite->SetScale(2.5);
	player5sprite->SetPosition(game->setting->screenWidth * 2 / 3 - 250, game->setting->screenHeight * 3 / 5 - 100);
	player5sprite->SetAnimationDuration(175);
	player5sprite->SetFlipHorizontal(false);
	player5sprite->SetBoundToCamera(true);

	enemy = new Texture("Asset/Enemy/Zombie.png");
	enemy5sprite = new Sprite(enemy, game->defaultSpriteShader, game->defaultQuad);
	enemy5sprite->SetNumXFrames(13);
	enemy5sprite->SetNumYFrames(6);
	enemy5sprite->AddAnimation("attack", 14, 18);
	enemy5sprite->PlayAnim("attack");
	enemy5sprite->SetScale(5);
	enemy5sprite->SetAnimationDuration(120);
	enemy5sprite->SetPosition(game->setting->screenWidth * 2 / 3 - 150, game->setting->screenHeight * 3 / 5 - 100);
	enemy5sprite->SetFlipHorizontal(true);
	enemy5sprite->SetBoundToCamera(true);

	//HP Bar
	textureHPbar = new Texture("Asset/UI/healthbar.png");
	spriteHPbar = new Sprite(textureHPbar, game->defaultSpriteShader, game->defaultQuad);
	spriteHPbar->SetNumXFrames(11);
	spriteHPbar->SetNumYFrames(1);
	spriteHPbar->AddAnimation("100", 0, 0);
	spriteHPbar->AddAnimation("90", 1, 1);
	spriteHPbar->AddAnimation("80", 2, 2);
	spriteHPbar->AddAnimation("70", 3, 3);
	spriteHPbar->AddAnimation("60", 4, 4);
	spriteHPbar->AddAnimation("50", 5, 5);
	spriteHPbar->AddAnimation("40", 6, 6);
	spriteHPbar->AddAnimation("30", 7, 7);
	spriteHPbar->AddAnimation("20", 8, 8);
	spriteHPbar->AddAnimation("10", 9, 9);
	spriteHPbar->AddAnimation("0", 10, 10);
	spriteHPbar->PlayAnim("100");
	spriteHPbar->SetScale(0.5);
	spriteHPbar->SetAnimationDuration(30);
	spriteHPbar->SetPosition(game->setting->screenWidth * 2 / 3 - 370, game->setting->screenHeight * 2 / 5 - 100);
	spriteHPbar->SetBoundToCamera(true);

	//How To Play 6 Ammo Drop

	enemy6sprite = new Sprite(enemy, game->defaultSpriteShader, game->defaultQuad);
	enemy6sprite->SetNumXFrames(13);
	enemy6sprite->SetNumYFrames(6);
	enemy6sprite->AddAnimation("dies", 65, 76);
	enemy6sprite->PlayAnim("dies");
	enemy6sprite->SetScale(5);
	enemy6sprite->SetAnimationDuration(121);
	enemy6sprite->SetPosition(game->setting->screenWidth * 3 / 3 - 250, game->setting->screenHeight * 3 / 5 - 100);
	enemy6sprite->SetFlipHorizontal(true);
	enemy6sprite->SetBoundToCamera(true);

	ammo = new Texture("Asset/Weapon/Rifle/ammo-rifle.png");
	ammo6sprite = new Sprite(ammo, game->defaultSpriteShader, game->defaultQuad);
	ammo6sprite->SetNumXFrames(1);
	ammo6sprite->SetNumYFrames(1);
	ammo6sprite->AddAnimation("idle", 0, 0);
	ammo6sprite->PlayAnim("attack");
	ammo6sprite->SetScale(2.5);
	ammo6sprite->SetAnimationDuration(120);
	ammo6sprite->SetPosition(game->setting->screenWidth * 3 / 3 - 240, game->setting->screenHeight * 3 / 5 - 100);
	ammo6sprite->SetFlipHorizontal(true);
	ammo6sprite->SetBoundToCamera(true);

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

void Engine::ScreenHowToPlay2::Update()
{
	
	//How To Play 4 reload
	KeyBoardReloadSprite->Update(game->GetGameTime());
	if (isReload) {
		reloadtime4 += game->GetGameTime();
		for (size_t i = 0; i < ReloadSprite.size(); i++) {
			ReloadSprite[i]->Update(game->GetGameTime());

			if (i == 1) {
				//std::cout << 146 * activeWeapon->reloadPercentage << "\n";
				ReloadSprite[i]->SetSize(146 * reloadtime4 / 2000, ReloadSprite[i]->GetScaleHeight() * 3);
			}
		}
		if (reloadtime4 >= 2000) {
			isReload = false;
			reloadtime4 = 0;
		}
	}

	if (gametime4 >= 6000 && isReload == false) {
		isReload = true;
		gametime4 = 0;
	}

	gametime4 += game->GetGameTime();

	//How To Play 5 damage
	KeyBoardReloadSprite->Update(game->GetGameTime());
	enemy5sprite->Update(game->GetGameTime());

	//healthbar
	spriteHPbar->Update(game->GetGameTime());
	if (gametime5 >= 630) {
		health -= 10;
		if (health > 90) {
			spriteHPbar->PlayAnim("100");
		}
		else if (health > 80) {
			spriteHPbar->PlayAnim("90");
		}
		else if (health > 70) {
			spriteHPbar->PlayAnim("80");
		}
		else if (health > 60) {
			spriteHPbar->PlayAnim("70");
		}
		else if (health > 50) {
			spriteHPbar->PlayAnim("60");
		}
		else if (health > 40) {
			spriteHPbar->PlayAnim("50");
		}
		else if (health > 30) {
			spriteHPbar->PlayAnim("40");
		}
		else if (health > 20) {
			spriteHPbar->PlayAnim("30");
		}
		else if (health > 10) {
			spriteHPbar->PlayAnim("20");
		}
		else if (health > 0) {
			spriteHPbar->PlayAnim("10");
		}
		else if (health > -10) {
			spriteHPbar->PlayAnim("0");
		}
		else {
			health = 100;
			spriteHPbar->PlayAnim("100");
		}

		gametime5 = 0;
	}

	if (isHittime5 >= 550) {
		isHit = true;
	}

	if (isHit) {
		currentHitCounter += game->GetGameTime();
		player5sprite->coloradjusment = { 255,255,255 };
	}
	if (currentHitCounter > 100) {
		player5sprite->coloradjusment = { 1.0f,1.0f,1.0f };
		currentHitCounter = 0;
		isHit = false;
		isHittime5 = 0;
	}

	gametime5 += game->GetGameTime();
	isHittime5 += game->GetGameTime();

	//How To Play 6 ammo

	enemy6sprite->Update(game->GetGameTime());
	if (gametime6 >= 1120) {
		isDrop = true;
		if (gametime6 >= 1477) {
			isDrop = false;
			gametime6 = 0;
		}
	}

	cout << gametime6 << " " << currentloop << "/n";
	gametime6 += game->GetGameTime();

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
				manager->switchScreen(ScreenState::HOW_TO_PLAY);
			}

		}

	}

	// Update All buttons
	for (Button* b : buttons) {
		b->Update(game->GetGameTime());
	}

}

void Engine::ScreenHowToPlay2::Render()
{

	//How to play 4 reload
	if (isReload) {
		for (size_t i = 0; i < ReloadSprite.size(); i++) {
			ReloadSprite[i]->Draw();
		}
	}
	KeyBoardReloadSprite->Draw();

	player4sprite->Draw();
	rifle4Sprite->Draw();

	//How to play 5 damage
	player5sprite->Draw();
	enemy5sprite->Draw();
	spriteHPbar->Draw();

	////How to play 6 ammo
	if (isDrop) {
		ammo6sprite->Draw();
	}
	enemy6sprite->Draw();

	//Render Background

	PrevSprite->Draw();
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

void Engine::ScreenHowToPlay2::forDebug()
{

	if (duration >= 1000) {
		//std::cout << mouseWorldPos.x;
		//std::cout << playerPos.y;
		duration = 0;
	}
}


bool Engine::ScreenHowToPlay2::getRandomBoolean(double truePercentage)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	return distribution(gen) < truePercentage;
}