#pragma once
#include "util.h"
#include "GameObject.h"
#include "config.h"
#include "graphics.h"

//For debugging
#include <iostream>


class Bullet :public GameObject , public Collidable
{
	bool isPlayer;

	int attackPoints = 1;	//Attack on hit

	float pos_x = 0,
		  pos_y = 0;
	
	float bulletSpeed = 6.0f;
	
	float size = 5.0f;
	
public:
	
	Bullet(bool i); //i == true ->is Player , else is Enemy
	~Bullet();
	
	bool checkDeleteBullet();

	int getAttack() const;

	void setAttack(int i);

	void setPosX(float i);
	void setPosY(float i);

	void setBulletSize(float i);
	float getBulletSize();

	void setBulletSpeed(float i);
	float getBulletSpeed();

	float getPosY();

	void update() override;
	void draw() override;
	void init() override;
	Disk getCollisionDisk() const override;

};