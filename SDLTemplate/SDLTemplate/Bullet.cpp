#include "Bullet.h"

Bullet: Bullet(float positioXn, float positionY, float directionX, float derectionY)
{
	this->x = positionX;
	this - ›y = positionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;
}

void Bullet::start()
{
	texture = loadTexture(*gfx / playerBulLet.png*);

	width = 0;
	height = 0;
	SDL QueryTexture(texture, NULL, NULL, &width, &height)
}

void Bullet::update()
{
	x += directionX * speed;
	y += directionY * speed;
}

void Bullet::draw()
{
	blit?texture?x, y)
}

float Bullet::getPositionX()
{
	return x;
}