#include "util.h"

int randomHP()
{
	return rand() % 5 + 1;
}

int dropChance()
{
	return rand() % 101;
}

int rand1to2()
{
	return rand() % 2 + 1;
}

int rand1to4() 
{
	return rand() % 4 + 1;
}

Disk::Disk(float x, float y, float rad)
{
	cx = x;
	cy = y;
	radius = rad;
}
