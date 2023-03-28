#pragma once
#include "GameObject.h"
#include "config.h"
#include "graphics.h"
#include "util.h"
#include "Bullet.h"

class Enemy :public GameObject , public Collidable
{
	Bullet* bullet_ptr = nullptr;

	bool dropPickup;

	int movingDirection; // will take a random value between 1 and 4

	void fireBullet();

	bool activateFireBullet = false;

	float pos_x, pos_y = 0.0f;

	float speed = 2.0f;
	int hitPoints = 1;
	float size = 80.0f;

	//for calculating the final score
	int score = 10;

public:
    
	void update() override;
   	void draw() override;
   	void init() override;
	Disk getCollisionDisk() const override;
	Disk getCollisionDiskOfBullet() const;

	Enemy();
   	~Enemy();

	graphics::Brush br;
	
	
	int getHitPoints();
	int getBulletAttack();
	bool getDropPickup();

	void setPosX(float i);
	void setPosY(float i);

	void getRandomBonus(int i);

	void setActivateFireBullet(bool i);
	bool getHasActiveBullet();

	void bulletInit();

	void addHitPoints(int i);
	int getScore();

	void drawBullet();

};