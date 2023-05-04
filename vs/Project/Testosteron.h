#ifndef TESTOSTERON_H
#define TESTOSTERON_H

#include "Game.h"


class Testosteron :
	public Engine::Game
{
public:
	Testosteron(Engine::Setting* setting);
	virtual void Init();
	virtual void Update();
	virtual void Render();
	int r = 255;
	int g = 0;
	int b = 0;
};

#endif

