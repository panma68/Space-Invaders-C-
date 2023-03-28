#pragma once
#include <random>

class Disk
{
public:
	float cx, cy;
	float radius;
	Disk(float x, float y, float rad);
};

int randomHP();
int dropChance();
int rand1to2();
int rand1to4();