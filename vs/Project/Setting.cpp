#include "Setting.h"

using namespace Engine;

Setting::Setting()
{
	// default setting
	this->screenWidth = 800;
	this->screenHeight = 600;
	this->vsync = true;
	this->timeScale = 1;
	this->windowFlag = WindowFlag::WINDOWED;
	this->targetFrameRate = 60;
	this->windowTitle = "Untitled";
	this->score = 0;
}

Setting::~Setting()
{
}
