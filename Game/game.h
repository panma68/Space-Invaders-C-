#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "util.h"
#include <vector>

class Game
{
	Player * player = nullptr;
	std::vector<Enemy*> enemyArr;

	int score = 0;
	int sizeOfEnemyVec = 20;

	bool endGame = false;
	bool wonGame = false;

	bool playingMode = false;

	int firingRateOfEnemies = 0;
	int firingLimit = 93;
	int enemyFiringBullet;

	void initializeEnemies();
	
	void checkCollisionWithEnemy();
	void checkCollisionWithPlayer();
	void checkCollisionBullets();	
	void destroyEnemies(std::vector<Enemy*> enemyArray);

public:
	void update();
	void draw();
	void init();

	void setFiringLimit(int frgLmt) { firingLimit = frgLmt; };
	Game();
	~Game();
};