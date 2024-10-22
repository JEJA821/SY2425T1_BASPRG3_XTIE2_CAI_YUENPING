#include "Enemy.h"
#include "Scene.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::start()
{
	texture = loadTexture("gfx / enemy.png");

	directionX = -1;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 60; //Reload tine of 68 franes, or 1 second
	currentReloadTime = 0;

	directionChangeTime = (rand ()%300) + 180;
	currentDirectionChangeTime = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound / 334227_jradccolness__laser.ogg");
	sound ->volume = 64;
}


void Enemy::update()
{
	x += directionX * speed;
	y += directionY * speed;

	if(currentDirectionChangeTime > 0)
		currentDirectionChangeTime--; 

	if (currentDirectionChangeTime == 0)
	{
		directionY = -directionY;
		currentDirectionChangeTime = directionChangeTime;
	}

	if (currentReloadTime > 0)
		currentReloadTime--;

	if (currentReloadTime == 0)
	{
		float dx = -1;
		float dy = 0;

		calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width / 2, y - 2 + height / 2, dx, dy, 10);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		// After firing, reset our reload timer
		currentReloadTime = reloadTime;
	}

	// Memory manage our bullets. When they go off screen, delete them
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() > 0)
		{
			// Cache the variable so we can delete it later
			// We can't delete it after erasing from the vector(leaked pointer)
			Bullet* bulletToErase; bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			// We can't mutate (change) our vector while looping inside it
			// this might crash on the next 100p iteration
			// We can also avoid lag this way
			break;
		}
}

void Enemy :: draw()
{
	blit(texture, x, y);
}

void Enemy::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

void Enemy::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}
