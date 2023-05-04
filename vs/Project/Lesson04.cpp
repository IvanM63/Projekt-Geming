#include "Lesson04.h"

Engine::Lesson04::Lesson04(Setting* setting) :Engine::Game(setting)
{

}

Engine::Lesson04::~Lesson04()
{
	//delete texture;
	//delete sprite;
}

void Engine::Lesson04::Init()
{
	texture = new Texture("monster.png");
	sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	sprite->SetNumXFrames(6);
	sprite->SetNumYFrames(2);
	sprite->AddAnimation("idle", 0, 3);
	sprite->AddAnimation("walk", 6, 11);
	sprite->PlayAnim("walk");
	sprite->SetScale(3);
	sprite->SetAnimationDuration(90);

	SetBackgroundColor(65, 180, 242);

}

void Engine::Lesson04::Update()
{
	sprite->Update(GetGameTime());
	float x = sprite->GetPosition().x;
	float y = sprite->GetPosition().y;
	float velocity = 0.07f;
	// s = v * t;
	float maxX = setting->screenWidth - sprite->GetScaleWidth();
	float minX = 0;
	mul *= (x > maxX || x < minX) ? -1 : 1;
	x += velocity * mul * GetGameTime();
	sprite->SetFlipHorizontal(mul == 1 ? false : true);
	sprite->SetPosition(x, y);
}

void Engine::Lesson04::Render()
{
	sprite->Draw();
}

/*
int main(int argc, char** argv) {
	Engine::Setting* setting = new Engine::Setting();
	setting->windowTitle = "Animation Demo";
	setting->screenWidth = 1024;
	setting->screenHeight = 768;
	setting->windowFlag = Engine::WindowFlag::WINDOWED;
	setting->vsync = false;
	setting->targetFrameRate = 0;
	Engine::Game* game = new Engine::Lesson04(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}
*/
