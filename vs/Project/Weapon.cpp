#include "Weapon.h"
//#include "../../../../backup/Projekt/Projekt-Geming/vs/Project/Projectile.h"

Engine::Weapon::Weapon(Game* game, Player* player)
{
	this->game = game;
	this->player = player;
}

Engine::Weapon::~Weapon()
{
}

void Engine::Weapon::Init()
{
	// W E A P O N  L I S T \\
	//Pistol Init
	pistol = new Pistol(game);
	pistol->Init();

	//Weapon Sound
	sound = new Sound("pistol-shot.ogg");
	sound->SetVolume(100);

	//Simple GUI Info
	ammoText = new Text("lucon.ttf", 24, game->defaultTextShader);
	ammoText->SetScale(1.0f);
	ammoText->SetColor(255, 255, 255);
	
}

void Engine::Weapon::Update()
{
	pistol->Update();
	pistol->SetPosition(playerPos.x, playerPos.y);
	Fire();

	//Text Info
	ammoText->SetText(std::to_string(pistol->GetCurrentAmmo()));
	ammoText->SetPosition(playerPos.x, playerPos.y + 100);
}

void Engine::Weapon::Render()
{
	pistol->Render();
	ammoText->Draw();
}

void Engine::Weapon::Fire()
{
	duration += game->GetGameTime();
	if (duration >= 1000) {
		//std::cout << mouseWorldPos.x;
		//std::cout << playerPos.y;
		duration = 0;
	}

	//Ingput Calkulason
	playerPos = player->GetPosition();

	//Wolk
	float velocity = 0.15f;

	//Aiming With Mouse
	GetCursorPos(&mousePos);
	HWND windowHandle = FindWindow(NULL, "Jombi-Jombian");

	//Convert the mouse position to coordinates relative to the top-left corner of your game window
	ScreenToClient(windowHandle, &mousePos);

	int mouseX = mousePos.x - characterOffSet.x;
	int mouseY = mousePos.y + characterOffSet.y;

	vec2 mouseWorldPos = { mouseX, 768 - mouseY };
	vec2 dir = { mouseWorldPos.x - playerPos.x, mouseWorldPos.y - playerPos.y };

	// Normalize the direction vector
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	dir.x /= length;
	dir.y /= length;

	// Calculate the aim angle
	aimAngle = atan2(dir.y, dir.x) * 180 / M_PI;

	//Setting rotation for both Player and Weapon Sprite
	if (aimAngle > 90 || aimAngle < -90) {
		pistol->SetFlipVertical(true);
		player->SetFlipHorizontal(false);
	}
	else {
		pistol->SetFlipVertical(false);
		player->SetFlipHorizontal(true);
	}

	pistol->SetRotation(aimAngle);

	//Debug aimANgle
	//std::cout << aimAngle << "\n";

	// Update the aim direction
	vec2 aimDir = dir;

	//Debug Mouse Pos in X n Y
	//std::cout << mouseX << " " << 768 - mouseY << "\n";

	//Fire Management
	pistol->Fire(playerPos, aimDir);
	
}







