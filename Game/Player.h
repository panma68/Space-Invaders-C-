#pragma once
#include "GameObject.h"
#include "config.h"
#include "Bullet.h"
#include <string>

class Player:public GameObject , public Collidable
{
	Bullet* bullet_ptr = nullptr;

	float pos_x = CANVAS_WIDTH / 2 , pos_y= CANVAS_HEIGHT - 30.0f ;
	float speed = 3.0f;
	float size = 15.0f;
	int hitPoints = 3;
	bool activateFireBullet = false;

	void fireBullet();
	std::string hp;

	//For calculating the score
	int score = 0;

public:
	Player();
	~Player();

	std::string printHp();

	void update() override;
	void draw() override;
	void init() override;
	Disk getCollisionDisk() const override;
	Disk getCollisionDiskOfBullet() const;

	int getHitPoints();
	void incrementHitPoints(int i);

	void setActivateBullet(bool i);

	bool getHasActiveBullet();

	int getBulletAttack();

	int getScore();

	void getBonus(int i);
	void drawBullet();
};