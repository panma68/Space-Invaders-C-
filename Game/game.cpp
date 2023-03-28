#include "game.h"
#include "graphics.h"
#include "config.h"
#include <iostream>



void Game::initializeEnemies()
{
	if (enemyArr.empty()) 
	{
		int initializationPositionX = CANVAS_WIDTH;
		int iterAmount = 50;
		for (int i = 0; i < sizeOfEnemyVec; i++)
		{
			enemyArr.push_back(new Enemy());

			enemyArr[i]->setPosX(initializationPositionX - iterAmount);
			if (i < 10)
				enemyArr[i]->setPosY(90);
			else
				enemyArr[i]->setPosY(150);

			iterAmount += 100;
			iterAmount = iterAmount % 1000;
		}
	}
}


void Game::checkCollisionWithEnemy()
{
	if (!enemyArr.empty() && player)
	{
		for (int i = 0; i < sizeOfEnemyVec; i++)
		{
			if (player->getHasActiveBullet() && enemyArr[i])
			{
				//player bullet and Enemy
				Disk d1 = enemyArr[i]->getCollisionDisk();
				Disk d2 = player->getCollisionDiskOfBullet();

				float dx = d1.cx - d2.cx;
				float dy = d1.cy - d2.cy;

				if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
				{
					//Decrementing hp of enemy by attack of playerBullet
					enemyArr[i]->addHitPoints(-player->getBulletAttack());
					player->setActivateBullet(false);
					//Checking if enemy being hit hp is equal to 0
					//if it is , delete that enemy
					if (enemyArr[i]->getHitPoints() <= 0)
					{
						if (enemyArr[i]->getDropPickup() == true) 
						{
							player->getBonus(rand1to4());
						}
						//Adding score
						score += enemyArr[i]->getScore();

						//Deleting enemy
						delete enemyArr[i];
						enemyArr.erase(enemyArr.begin() + i);
						sizeOfEnemyVec--;
						//End of deleting enemy


						//Adding bonuses to enemies
						if(enemyArr.size()<=5)
						{ 
							firingLimit++;

							for (unsigned int y = 0; y < enemyArr.size(); y++)
								enemyArr[y]->getRandomBonus(rand1to4());
						}
				}

				}
			}
		}
	}
}

void Game::checkCollisionWithPlayer()
{
	for (int i = 0; i < sizeOfEnemyVec; i++)
	{
			//Here we are using firingRateOfEnemies as an index
		if (enemyArr[i] && player)
		{
			if (enemyArr[i]->getHasActiveBullet() == true) {
				//player and Enemy bullet
				Disk d1 = player->getCollisionDisk();
				Disk d2 = enemyArr[i]->getCollisionDiskOfBullet();

				float dx = d1.cx - d2.cx;
				float dy = d1.cy - d2.cy;

				if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
				{
					player->incrementHitPoints(-(enemyArr[i]->getBulletAttack()));
					enemyArr[i]->setActivateFireBullet(false);

					//Checking if player hp is equal to 0
					//if it is , end game

					if (player->getHitPoints() <= 0)
					{
						score += player->getScore();
						delete player;
						player = nullptr;
						endGame = true;
					}
				}
			}
		}
	}
}

void Game::checkCollisionBullets()
{
	
}


/*
*
*
* --GAME UPDATE-- 
* 
* 
*/
void Game::update()
{
	//DONE ONLY ONCE
	if(!playingMode)
	{
		player = new Player();
		initializeEnemies();
		player->init();
		playingMode = true;
	}
		
	if (!wonGame && !endGame)
	{
		firingRateOfEnemies = dropChance();

		if (player)
			player->update();

		if (!enemyArr.empty()) {
			for (int i = 0; i < sizeOfEnemyVec; i++) {
				if (enemyArr[i] != nullptr) {
					enemyArr[i]->update();
				}
				else {
					continue;
				}
			}
		}

		else
		{
			wonGame = true;
		}
		//ENEMY Firing
		//firingRateOfEnemies specifing how often an enemy is firing

		if (firingRateOfEnemies >= firingLimit && !enemyArr.empty())
		{
			
			enemyFiringBullet = dropChance() % sizeOfEnemyVec;
			//When we do setActiveBullet() in an EnemyObject , it fires a bullet from
			//a random enemy
			//The if statement checks if the selected enemy's bullet is active (meaning he has already fired)
			if (enemyArr[enemyFiringBullet]) {
				if (enemyArr[enemyFiringBullet]->getHasActiveBullet() == false)
				{
					enemyArr[enemyFiringBullet]->bulletInit();
				}
			}
		}

		if (player)
		{
			//Player attacking Enemy ---> Collision
			checkCollisionWithEnemy();

			//Enemy attacking Player ---> Collision
			checkCollisionWithPlayer();
		}
	}
}

void Game::draw()
{
	if (playingMode) {
		//Initialization of Brush
		graphics::Brush br;
		graphics::Brush text;

		//text init
		text.texture = "";
		text.fill_color[0] = 1.0f; //RED
		text.fill_color[1] = 1.0f; //GREEN
		text.fill_color[2] = 1.0f; //BLUE


	//DRAW BACKGROUND//
		//------START------------//

		br.texture = std::string(ASSET_PATH) + "background.png";

		br.outline_opacity = 0.0f;
		br.gradient = true;
		br.gradient_dir_u = 0.5f;
		br.gradient_dir_v = 0.5f;

		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH /**1.7f*/, CANVAS_WIDTH / 1.7f, br);
		//------FINISH-----------//

		//Glowing Effect
		br.texture = "";
		float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 800);


		br.fill_color[0] = 0.5f; //RED
		br.fill_color[1] = 0.5f; //GREEN
		br.fill_color[2] = 0.5f + glow * 0.5f; //BLUE

		br.fill_secondary_color[0] = 0.2f; //RED
		br.fill_secondary_color[1] = 0.2f; //GREEN
		br.fill_secondary_color[2] = 0.2f; //BLUE

		br.fill_opacity = 0.5f;
		br.fill_secondary_opacity = 0.5f;

		br.gradient = true;

		br.gradient_dir_u = 0.0f;
		br.gradient_dir_v = 1.0f;

		br.outline_opacity = 0.0f;

		graphics::drawDisk(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, 55, br);
		//Finish of Glowing Effect


		//Draw Player
		if (player != nullptr)
		{
			player->draw();
			player->drawBullet();
			drawText(CANVAS_WIDTH - 300.0f, CANVAS_HEIGHT  - 450.0f, 30.0f, player->printHp(), text);
		}
		//Draw Enemy
		if (!enemyArr.empty() && !endGame && !wonGame) 
		{
			for (int i = 0; i < sizeOfEnemyVec; i++)
			{
				if (enemyArr[i] != nullptr)
				{
					enemyArr[i]->draw();
					enemyArr[i]->drawBullet();
				}
			}
		}
		
		//EndingGame Screen
		if (endGame)
		{
			//PRINT GAME OVER SCREEN
			char gameOverTxt[] = "Game Over";
			drawText(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 100.0f, 40.0f, gameOverTxt, text);
			drawText(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 - 100.0f, 30.0f, "Your score is: "+std::to_string(score), text);
		}

		if (wonGame)
		{
			//PRINT GAME OVER SCREEN
			char wonTxt[] = "You've won!";
			drawText(CANVAS_WIDTH / 2 - 50.0f, CANVAS_HEIGHT / 2 - 60.0f, 40.0f, wonTxt, text);
			drawText(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 - 100.0f, 30.0f, "Your score is: " + std::to_string(score) ,text);
			
		}
	}
}

void Game::init()
{
	//INITIALIZE FONT
	graphics::setFont(std::string(ASSET_PATH) + "AeroviasBrasilNF.ttf");
}

Game::Game()
{
	
}

Game::~Game()
{
	if (player) 
	{
		delete player;
	}

	destroyEnemies(enemyArr);
}

//Destroy enemies in vector
void Game::destroyEnemies(std::vector<Enemy*> enemyArray){
	if (!enemyArray.empty())
	{
		for (int i = 0; i < enemyArray.size() - 1; i++) {
			delete enemyArray[i];
		}
	}
}