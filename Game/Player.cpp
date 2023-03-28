#include "Player.h"
#include "graphics.h"
#include <iostream>

void Player::update()
{
	if (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_LEFT))
	{
		pos_x -=  speed * graphics::getDeltaTime() / 8.0f;
	}
	
	
	if (graphics::getKeyState(graphics::SCANCODE_D) || graphics::getKeyState(graphics::SCANCODE_RIGHT))
	{
		pos_x += speed * graphics::getDeltaTime() / 8.0f;
	}
	
	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;
	

	//Player Firing
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
		if (!activateFireBullet)
		{
			bullet_ptr->setPosX(pos_x);
			bullet_ptr->setPosY(pos_y - 30.0f);
			activateFireBullet = true;
		}

	if (activateFireBullet)
	{
		fireBullet();
		if (bullet_ptr->checkDeleteBullet())
		{
			activateFireBullet = false;
		}
	}
}

void Player::draw()
{
	//----PLAYER------------//
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "rocket.png";

	br.outline_opacity = 0.0f;
	br.gradient = true;
	br.gradient_dir_u = 0.5f;
	br.gradient_dir_v = 0.5f;
	br.outline_opacity = 0.0f;

	graphics::drawRect(pos_x, pos_y, CANVAS_WIDTH / 10, CANVAS_HEIGHT / 10 , br);

	//--------FLARE-----------//
	br.texture = "";
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 100);
	
	
	br.fill_color[0] = 1.0f; //RED
	br.fill_color[1] = 0.5f + glow * 0.5f; //GREEN
	br.fill_color[2] = 0.2f; //BLUE

	br.fill_secondary_color[0] = 0.9f; //RED
	br.fill_secondary_color[1] = 0.3f; //GREEN
	br.fill_secondary_color[2] = 0.0f; //BLUE

	br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.4f;

	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	br.outline_opacity = 0.0f;

	graphics::drawDisk(pos_x + 2.0f, pos_y + 30.0f, size, br);

	//------------END OF FLARE---------------//
	
	/*
	//TEMP COLLISION RADIUS
	br.outline_opacity = 1.0f;
	br.texture = "";
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.3f;
	br.fill_color[2] = 0.3f;
	br.fill_opacity = 0.3f;
	br.gradient = false;
	Disk disk1 = getCollisionDisk();
	graphics::drawDisk(disk1.cx, disk1.cy, disk1.radius, br);
	//END COLLISION RADIUS
	*/
}

Player::Player()
{
	init();
}

Player::~Player()
{
	delete bullet_ptr;
	std::cout << "player destroyed + bullet destroyed\n";
}

std::string Player::printHp()
{
	return hp = "Your health is: " + std::to_string(hitPoints);
}


int Player::getBulletAttack()
{
	return bullet_ptr->getAttack();
}

bool Player::getHasActiveBullet()
{
	return activateFireBullet;
}

void Player::init()
{
	bullet_ptr = new Bullet(true);
}

Disk Player::getCollisionDisk() const
{
	Disk disk(pos_x + 2.0f, pos_y, size);
	return disk;
}

Disk Player::getCollisionDiskOfBullet() const
{
	return bullet_ptr->getCollisionDisk();
}

int Player::getScore()
{
	return score;
}

void Player::getBonus(int i)
{
	if (i == 1) {
		hitPoints++;
		score += 10;
	}
	if (i == 2) {
		bullet_ptr->setAttack(bullet_ptr->getAttack() + 1);
		score += 5;
	}
	if (i == 3) {
		speed += 1.0f;
		score += 15;
	}
	if (i == 4) {
		bullet_ptr->setBulletSize(bullet_ptr->getBulletSize() + 1.0f);
		score += 5;
	}
	
}

void Player::drawBullet()
{
	if (activateFireBullet == true)
	{
		bullet_ptr->draw();
	}
}

int Player::getHitPoints()
{
	return hitPoints;
}

void Player::setActivateBullet(bool i)
{
	activateFireBullet = i;
}

void Player::incrementHitPoints(int i)
{
	if (i == 1) {
		hitPoints += i;
		score += 10;
	}
	
	if(i>1 && i <=2)
	{
		hitPoints += i;
		score += 20;
	}
	else
	{
		hitPoints += i;
		score += 30;
	}

}

void Player::fireBullet()
{
	bullet_ptr->setPosY(bullet_ptr->getPosY() - bullet_ptr->getBulletSpeed() * graphics::getDeltaTime() / 8.0f);
}