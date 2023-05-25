#include "Wave.h"

Engine::Wave::Wave(Game* game)
{
	this->game = game;

	this->numEnemies = 2;
	this->enemiesLeft = 5;
	this->maxAvailEnemies = numEnemies / 2;
	this->currentWave = 1;
	this->x = 0.5;
}

Engine::Wave::~Wave()
{
}

void Engine::Wave::NextWave()
{
	waveTime = 0;
	currentWave += 1;
	
	if (currentWave % 5 == 0) {
		x += 0.5;
	}
	
	numEnemies = x*(2 * currentWave + 3);

}

void Engine::Wave::SpawnStart()
{
	this->isSpawning = true;
}

void Engine::Wave::SpawnEnd()
{
	this->isSpawning = false;
}

std::vector<Engine::Enemy*> Engine::Wave::SpawnEnemies()
{
	// spawn enemy
	int x = std::rand() % (game->setting->screenWidth + 50 * 2) - 50;
	int y = std::rand() % (game->setting->screenHeight + 50 * 2) - 50;

	// check if enemy is out of screen
	if (x < 0 || x > game->setting->screenWidth || y < 0 || y > game->setting->screenHeight) {
		//std::cout << "Enemy spawned out of screen at (" << x << ", " << y << ")" << std::endl;

		Enemy* e = new Enemy(game);
		e->Init();
		e->SetPosition(x, y);
		e->setDebug(false);

		enemiesWave.push_back(e);
		std::cout << "Enemy spawned at (" << x << ", " << y << ")" << std::endl;
	}

	 

	/*if (enemiesLeft == 0) {
		SpawnEnd();
	}*/

	if (enemiesWave.size() >= numEnemies) {
		//enemiesLeft /= 2;
		SpawnEnd();
	}

	return enemiesWave;
}

void Engine::Wave::RemoveEnemiesByOne(int i)
{
	enemiesWave.erase(enemiesWave.begin() + i);
}

bool Engine::Wave::GetSpawnStatus()
{
	return this->isSpawning;
}

int Engine::Wave::GetCurrentWave()
{
	return currentWave;
}

void Engine::Wave::Update()
{
	if (enemiesWave.size() <= 0 && game->duration > 1000) {
		NextWave();
		SpawnStart();
	}

	waveTime += game->GetGameTime();

	//std::cout << enemiesWave.size() << "\n";
	//std::cout << waveTime << "\n";
}
