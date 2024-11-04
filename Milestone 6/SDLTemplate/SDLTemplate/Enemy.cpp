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
	directionChangeTime = (rand () % 300) + 180;
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
		Bullet* bullet = new Bullet(x + width / 2, y - 2 + height / 2, dx, dy, 10, Side::ENEMY_SIDE);
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
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			// We can't mutate (change) our vector while looping inside it
			// this might crash on the next 100p iteration
			// We can also avoid lag this way
			break;
		}
	}

	if (isBoss) {
		if (firingPattern == 0) {
			x += (sin(y / 50.0) * 5); // Swing from side to side
		}
		else if (firingPattern == 1) {
			y += speed;   // Move down
		}
	}
	else {
		// Conventional enemy logic
	}

	if (currentReloadTime > 0) currentReloadTime--;

	if (currentReloadTime == 0) {
		fire();  // Both bosses and normal enemies execute firing logic
		currentReloadTime = reloadTime;
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

int Enemy::getPositionX()
{
	return x;
}

int Enemy::getPositionY()
{
	return y;
}

int Enemy::getWidth()
{
	return width;
}

int Enemy::getHeight()
{
	return height;
}

void Enemy::switchPattern() {
	firingPattern = (firingPattern + 1) % 3;  // Switch mode
}

void Enemy::fire() {
	if (isBoss) {
		if (firingPattern == 0) {
			// Single rapid fire
			Bullet* bullet = new Bullet(x, y + height, 0, 1, 10, Side::ENEMY_SIDE);
			bullets.push_back(bullet);
			getScene()->addGameObject(bullet);
		}
		else if (firingPattern == 1) {
			// Fan three hair
			Bullet* bullet1 = new Bullet(x - 15, y + height, -1, 1, 10, Side::ENEMY_SIDE);
			Bullet* bullet2 = new Bullet(x, y + height, 0, 1, 10, Side::ENEMY_SIDE);
			Bullet* bullet3 = new Bullet(x + 15, y + height, 1, 1, 10, Side::ENEMY_SIDE);
			bullets.push_back(bullet1);
			bullets.push_back(bullet2);
			bullets.push_back(bullet3);
			getScene()->addGameObject(bullet1);
			getScene()->addGameObject(bullet2);
			getScene()->addGameObject(bullet3);
		}
	}
	else {
		// Common enemy firing logic
		Bullet* bullet = new Bullet(x, y + height, 0, 1, 10, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
	}
}

void Enemy::setFiringRate(int rate) {
	firingRate = rate;
}

void Enemy::setHealth(int hp) {
	health = hp;
}

void Enemy::setIsBoss(bool isBoss) {
	this->isBoss = isBoss;
}

bool Enemy::getIsBoss() const {
	return isBoss;
}
