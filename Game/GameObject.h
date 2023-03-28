#pragma once
#include "util.h"

class Collidable
{
public:
	virtual Disk getCollisionDisk() const= 0;
};

class GameObject
{
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
};