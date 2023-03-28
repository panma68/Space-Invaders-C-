#include "Enemy.h"
#include "windows.h"

void Enemy::update()
{

	movingDirection = dropChance();



	if(movingDirection > 30 && movingDirection < 50)
		pos_x += speed * graphics::getDeltaTime() / 4.0f;

	if(movingDirection > 10 && movingDirection < 30)
		pos_x -= speed * graphics::getDeltaTime() / 4.0f;
	
	if(movingDirection < 10)
		pos_y += speed * graphics::getDeltaTime() / 40.0f;
	
	//if(movingDirection > 95)
		//pos_y -= speed * graphics::getDeltaTime() / 40.0f;
	

	if (pos_x < 20.0f) pos_x = 20.0f;
	if (pos_x > CANVAS_WIDTH - 20.0f) pos_x = CANVAS_WIDTH - 20.0f;

	if (pos_y > CANVAS_HEIGHT - 100.0f) pos_y = CANVAS_HEIGHT - 100.0f;
	if (pos_y < 20.0f) pos_y = 20.0f;
	
	if (activateFireBullet)
	{
		fireBullet();
		if (bullet_ptr->checkDeleteBullet())
		{
			activateFireBullet = false;
		}
	}

}

void Enemy::draw()
{
	br.texture = std::string(ASSET_PATH) + "enemy3.png";
	
	br.outline_opacity = 0.0f;
	br.gradient = true;
	
	br.gradient_dir_u = 0.5f;
	br.gradient_dir_v = 0.5f;
	br.outline_opacity = 0.0f;

	if (hitPoints == 5)
	{
		br.fill_color[0] = 0.2f;
	}
	else if (hitPoints == 4)
	{
		br.fill_color[0] = 0.4f;
	}
	else if (hitPoints == 3)
	{
		br.fill_color[0] = 0.5f;
	}
	else if (hitPoints == 2)
	{
		br.fill_color[0] = 0.6f;
	}

	else if (hitPoints == 1)
	{
		br.fill_secondary_color[0] = 0.7f;
	}

		br.fill_color[1] = 0.0f; //GREEN
		br.fill_color[2] = 0.0f; //BLUE

	graphics::drawRect(pos_x, pos_y, size, size, br);

	//Glowing Effect if special drop
	if (dropPickup == true)
	{
		br.fill_secondary_opacity = 0.2f;
		br.texture = "";
	
		br.fill_secondary_color[1] = 0.4f;
		br.fill_secondary_color[2] = 0.0f;
		br.fill_opacity = 0.1f;
		br.outline_opacity = 0.5f;
		br.gradient = true;
		br.gradient_dir_v = 0.4f;
		br.gradient_dir_u = 0.0f;
		Disk disk1 = getCollisionDisk();
		graphics::drawDisk(disk1.cx, disk1.cy, disk1.radius+2.0f, br);

		//END
	}
}

void Enemy::init()
{
	bullet_ptr = new Bullet(false);
	hitPoints = randomHP();
	int i = dropChance();
	if (i <= 50) 
		dropPickup = true;
	else
		dropPickup = false;
}

Disk Enemy::getCollisionDisk() const
{
	Disk disk(pos_x + 6.0f ,pos_y - 4.0f, size-60.0f);
	return disk;
}

Disk Enemy::getCollisionDiskOfBullet() const
{
	return bullet_ptr->getCollisionDisk();
}


Enemy::Enemy()
{
	init();
}

Enemy::~Enemy()
{
	activateFireBullet = false;
	delete bullet_ptr;
	bullet_ptr = nullptr;
	std::cout << "Bullet Destroyed\n";
	std::cout << "Enemy Destroyed\n";
}

int Enemy::getHitPoints()
{
	return hitPoints;
}

int Enemy::getBulletAttack()
{
	return bullet_ptr->getAttack();
}

bool Enemy::getDropPickup()
{
	return dropChance;
}

void Enemy::setPosX(float i)
{
	pos_x = i;
}

void Enemy::setPosY(float i)
{
	pos_y = i;
}

void Enemy::getRandomBonus(int i)
{
	if (i == 1) {
		bullet_ptr->setAttack(bullet_ptr->getAttack() + 1);
		score += 40;
	}
	if (i == 2) {
		hitPoints++;
		score += 20;
	}
	if (i == 3) {
		bullet_ptr->setBulletSize(bullet_ptr->getBulletSize() + 2.0f);
		score += 10;
	}
	if (i == 4) {
		bullet_ptr->setBulletSpeed(bullet_ptr->getBulletSpeed() + 1.0f);
		score += 30;
	}
}


void Enemy::setActivateFireBullet(bool i)
{
	activateFireBullet = i;
}

void Enemy::fireBullet()
{
	bullet_ptr->setPosY(bullet_ptr->getPosY() + bullet_ptr->getBulletSpeed() * graphics::getDeltaTime() / 8.0f);
}

void Enemy::addHitPoints(int i)
{
	hitPoints += i;
}

int Enemy::getScore()
{
	return score;
}

bool Enemy::getHasActiveBullet()
{
	return activateFireBullet;
}

void Enemy::bulletInit()
{
	activateFireBullet = true;
	bullet_ptr->setPosX(pos_x);
	bullet_ptr->setPosY(pos_y + 30.0f);
	//bullet_ptr->setAttack();
}

void Enemy::drawBullet()
{
	if (bullet_ptr != nullptr && activateFireBullet == true)
		bullet_ptr->draw();
}
