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
	
}

void Engine::WeaponManager::Update()
{
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
	activeWeapon->SetPosition(playerPos.x, playerPos.y);
	Fire(activeWeapon);

	//Text Info
	ammoText->SetText(std::to_string(activeWeapon->GetCurrentAmmo()));
	ammoText->SetPosition(game->setting->screenWidth/2, game->setting->screenHeight/2 +100);

	
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
	
}

void Engine::WeaponManager::Fire(Weapon* weapon)
{
	duration += game->GetGameTime();
	
	//Ingput Calkulason
	playerPos = player->GetPosition();

	//Aiming With Mouse
	GetCursorPos(&mousePos);
	HWND windowHandle = FindWindow(NULL, "Jombi-Jombian");

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
		player->SetFlipHorizontal(false);
	}
	else {
		weapon->SetFlipVertical(false);
		player->SetFlipHorizontal(true);
	}

	weapon->SetRotation(rawAimAngle);

	//Debug for Aiming
	//Debug aimANgle
	//std::cout << "Direction: " << dir.x << "\n";
	//std::cout << "Velocity: " << bulletVelocityX << "\n";

	// Update the aim direction
	//vec2 aimDir = aimDir;

	//Debug Mouse Pos in X n Y
	//std::cout << mouseX << " " << 768 - mouseY << "\n";

	//Fire Management
	weapon->Fire(playerPos, aimDir, angleNoNegative, rawAimAngle);
	
}







