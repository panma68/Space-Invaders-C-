#include "Bullet.h"



bool Bullet::checkDeleteBullet()
{
	if (pos_y < 1.0f || pos_y > float(CANVAS_HEIGHT))
	{
		return true;
	}
	else
		return false;
}

Bullet::Bullet(bool i)
{
	isPlayer = i;
	init();
}


Bullet::~Bullet()
{

}


int  Bullet::getAttack() const
{
    return attackPoints;
}

void Bullet::setBulletSpeed(float i)
{
	bulletSpeed = i;
}

float Bullet::getBulletSpeed()
{
	return bulletSpeed;
}

void Bullet::setAttack(int i)
{
    attackPoints = i;
}


void Bullet::setPosX(float i)
{
	pos_x = i;
}

void Bullet::setPosY(float i)
{
	pos_y = i;
}


void Bullet::setBulletSize(float i)
{
	size = i;
}

float Bullet::getBulletSize()
{
	return size;
}


float Bullet::getPosY()
{
	return pos_y;
}


void Bullet::update()
{
	if (!isPlayer)
	{
		pos_y += bulletSpeed * graphics::getDeltaTime() / 8.0f ;
	}
}


void Bullet::draw()
{

	graphics::Brush br;
	br.texture = "";
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 80);

	br.fill_color[0] = 0.5f + glow * 0.5f; //RED
	br.fill_color[1] = 0.1f; //GREEN
	br.fill_color[2] = 0.1f; //BLUE

	if (attackPoints <= 1) 
	{
		br.fill_secondary_color[0] = 0.9f; //RED
		br.fill_secondary_color[1] = 0.3f; //GREEN
		br.fill_secondary_color[2] = 0.0f; //BLUE
	}
	else if (attackPoints >= 2)
	{
		br.fill_secondary_color[0] = 0.2f; //RED
		br.fill_secondary_color[1] = 0.2f; //GREEN
		br.fill_secondary_color[2] = 0.8f; //BLUE
	}
	br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.8f;

	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	br.outline_opacity = 0.0f;
	
	graphics::drawDisk(pos_x, pos_y, size, br);

	/*TEMP COLLISION RADIUS
	 * br.outline_opacity = 1.0f;
	 * br.texture = "";
	 * br.fill_color[0] = 1.0f;
	 * br.fill_color[1] = 0.3f;
	 * br.fill_color[2] = 0.3f;
	 * br.fill_opacity = 0.3f;
	 * br.gradient = false;
	 * Disk disk1 = getCollisionDisk();
	 * graphics::drawDisk(disk1.cx, disk1.cy, disk1.radius, br)
	 *
	 *END COLLISION RADIUS*/

}
	

void Bullet::init()
{	
}

Disk Bullet::getCollisionDisk() const
{
	Disk disk(pos_x, pos_y, size);
	return disk;
}
