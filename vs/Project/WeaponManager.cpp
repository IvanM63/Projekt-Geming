#include "WeaponManager.h"

Engine::WeaponManager::WeaponManager(Game* game, Player* player)
{
	this->game = game;
	this->player = player;
}

Engine::WeaponManager::~WeaponManager()
{
}

void Engine::WeaponManager::Init()
{
	//Sound Effect
	soundReloadStart = new Sound("Asset/Sound/Weapon/wpn_reload_start.ogg");
	soundReloadStart->SetVolume(80);
	soundReloadEnd = new Sound("Asset/Sound/Weapon/wpn_reload_end.ogg");
	soundReloadEnd->SetVolume(80);

	// W E A P O N  L I S T \\
	//Weapon Init (Pistol, Rifle)
	pistol = new Pistol(game);
	pistol->Init();

	rifle = new Rifle(game);
	rifle->Init();

	activeWeapon = pistol;

	weapons.push_back(pistol);
	weapons.push_back(rifle);

	//Weapon Sound
	sound = new Sound("pistol-shot.ogg");
	sound->SetVolume(100);

	//Simple GUI Info\\
	
	//Crosshair
	textureCrosshair = new Texture("Asset/Crosshair/crosshair2.png");
	spriteCrosshair = new Sprite(textureCrosshair, game->defaultSpriteShader, game->defaultQuad);

	spriteCrosshair->SetNumXFrames(1);
	spriteCrosshair->SetNumYFrames(1);
	spriteCrosshair->AddAnimation("idle", 0, 0);

	spriteCrosshair->PlayAnim("idle");
	spriteCrosshair->SetScale(0.1);
	spriteCrosshair->SetAnimationDuration(100);

	spriteCrosshair->SetBoundToCamera(true);

	//Text
	ammoText = new Text("lucon.ttf", 24, game->defaultTextShader);
	ammoText->SetScale(1.0f);
	ammoText->SetColor(255, 255, 255);

	ammoText2 = new Text("lucon.ttf", 54, game->defaultTextShader);
	ammoText2->SetScale(1.0f);
	ammoText2->SetColor(255, 255, 255);

	//Reload Bar UI
	reloadTexture = new Texture("Asset/UI/reloadBar.png");

	reloadSprites.push_back(new Sprite(reloadTexture, game->defaultSpriteShader, game->defaultQuad));
	reloadSprites.push_back(new Sprite(reloadTexture, game->defaultSpriteShader, game->defaultQuad));
	reloadSprites.push_back(new Sprite(reloadTexture, game->defaultSpriteShader, game->defaultQuad));

	for (size_t i = 0; i < reloadSprites.size(); i++) {
		reloadSprites[i]->SetNumXFrames(1);
		reloadSprites[i]->SetNumYFrames(3);
		reloadSprites[i]->AddAnimation("idle", i, i);
		reloadSprites[i]->PlayAnim("idle");
		reloadSprites[i]->SetBoundToCamera(true);

		if (i == 1) {
			reloadSprites[i]->SetSize(reloadSprites[i]->GetScaleWidth(), reloadSprites[i]->GetScaleHeight()*3);
		}
	}

}

void Engine::WeaponManager::Update()
{
	//Reload
	//std::cout << activeWeapon->reloadPercentage << "\n";
	//Change Weapon
	if (game->inputManager->IsKeyPressed("Rifle")) {
		activeWeapon = rifle;
	}
	else if (game->inputManager->IsKeyPressed("Pistol")) {
		activeWeapon = pistol;
	}

	//Check Tiap Senjata buat Update Peluru tiap masing-masing senjata
	for (size_t i = 0; i < weapons.size(); i++) {
		weapons[i]->UpdateProjectiles();
	}

	//Update perilaku Senjata yang lagi aktif
	activeWeapon->Update();
	activeWeapon->SetPositionToPlayer(playerPos);
	Fire(activeWeapon);

	//Text Info
	ammoText->SetText(std::to_string(activeWeapon->GetCurrentAmmo()));
	ammoText->SetPosition(mousePos.x - characterOffSet.x - 15 + 30 + 50, 755 - mousePos.y + characterOffSet.y + 20);
	ammoText2->SetText(std::to_string(activeWeapon->GetCurrentAmmo()) + "." + std::to_string(activeWeapon->GetTotalAmmo()));
	ammoText2->SetPosition(game->setting->screenWidth - 185, 15);

	//Reload UI Bar
	if (activeWeapon->isReload) {
		for (size_t i = 0; i < reloadSprites.size(); i++) {
			reloadSprites[i]->Update(game->GetGameTime());
			reloadSprites[i]->SetPosition(game->setting->screenWidth / 2 - 90, game->setting->screenHeight / 2 + 100);

			if (i == 1) {
				//std::cout << 146 * activeWeapon->reloadPercentage << "\n";
				reloadSprites[i]->SetSize(146 * activeWeapon->reloadPercentage, reloadSprites[i]->GetScaleHeight() * 3);
			}
			
			if (activeWeapon->reloadPercentage == 0.1) {
				soundReloadStart->Play(false);
			}

			//std::cout << activeWeapon->reloadPercentage<<"\n";
		}
	}
	

}

void Engine::WeaponManager::RenderAmmoText() {
	ammoText2->Draw();
}

void Engine::WeaponManager::Render()
{
	//Render Senjata yang lagi aktif sekarang
	activeWeapon->Render();
	ammoText->Draw();

	//Check Tiap Senjata buat Render Peluru
	for (size_t i = 0; i < weapons.size(); i++) {
		weapons[i]->RenderProjectiles();
	}
	
	//Render Crosshair
	spriteCrosshair->Draw();
	
	//Reload UI Bar
	if (activeWeapon->isReload) {
		for (size_t i = 0; i < reloadSprites.size(); i++) {
			reloadSprites[i]->Draw();
		}
	}
	
}

void Engine::WeaponManager::Fire(Weapon* weapon)
{
	duration += game->GetGameTime();
	
	//Ingput Calkulason
	playerPos = player->GetPosition();

	//Aiming With Mouse
	GetCursorPos(&mousePos);
	HWND windowHandle = FindWindow(NULL, "Jombi-Jombian");

	// Hide the mouse cursor
	ShowCursor(FALSE);

	//Convert the mouse position to coordinates relative to the top-left corner of your game window
	ScreenToClient(windowHandle, &mousePos);

	int mouseX = mousePos.x - characterOffSet.x;
	int mouseY = mousePos.y + characterOffSet.y;

	//Offset normal  x = -15 y = 755

	vec2 mouseWorldPos = { mouseX-15, 755 - mouseY };

	//std::cout << mouseWorldPos.x << " " << mouseWorldPos.y << "\n";

	//vec2 aimDir = { mouseWorldPos.x - playerPos.x, mouseWorldPos.y - playerPos.y };
	vec2 aimDir = { mouseWorldPos.x - 683 + 50, mouseWorldPos.y - 384 };

	//CrosshairPos
	spriteCrosshair->SetPosition(mouseWorldPos.x +30, mouseWorldPos.y);

	if (duration >= 1000) {
		//std::cout << playerPos.x << playerPos.y<<"\n";
		//std::cout << playerPos.y;
		duration = 0;
	}

	//Calculate for angle no negative number for calculate accuracy and recoil
	//this variable doesn't used to calculate weapon sprite rotation
	float angleNoNegative = atan2(aimDir.y, aimDir.x);
	if (angleNoNegative < 0) {
		angleNoNegative += 2 * M_PI;
	}
	
	// Calculate Raw Aim ANgle for sprite rotation
	rawAimAngle = atan2(aimDir.y, aimDir.x) * 180 / M_PI;

	aimDir = vec2(cos(angleNoNegative), sin(angleNoNegative));
	aimDir = normalize(aimDir);

	//Setting rotation for both Player and Weapon Sprite
	if (rawAimAngle > 90 || rawAimAngle < -90) {
		weapon->SetFlipVertical(true);
		player->SetFlipHorizontal(true);
	}
	else {
		weapon->SetFlipVertical(false);
		player->SetFlipHorizontal(false);
	}

	weapon->SetRotation(rawAimAngle);

	//Debug for Aiming
	//Debug aimANgle
	//std::cout << "Angle: " << rawAimAngle << "\n";
	//std::cout << "Velocity: " << bulletVelocityX << "\n";

	// Update the aim direction
	//vec2 aimDir = aimDir;

	//Debug Mouse Pos in X n Y
	//std::cout << mouseX << " " << 768 - mouseY << "\n";

	//Fire Management
	weapon->Fire(playerPos, aimDir, angleNoNegative, rawAimAngle);
	
}







