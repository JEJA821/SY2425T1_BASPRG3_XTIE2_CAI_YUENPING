#include "Bullet.h"

Bullet::Bullet(float positionX, float positionY, float directionX, float derectionY, float speed, Side side)
{
	this->x = positionX;
	this ->y = positionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;
	this->side = side;
}

void Bullet::start()
{
	width = 0;
	height = 0;

	if(side == Side::PLAYER_SIDE)
	{
    texture = loadTexture("gfx/playerBullet.png");
	}
	else
	{
		texture = loadTexture("gfx/alienBullet.png");
	}

	x = 0;
	y = 0;
    texture = loadTexture("gfx / playerBulLet.png");

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	if (side == Side::PLAYER_SIDE) {
		texture = loadTexture("gfx/playerBullet.png");
	}
	else {
		texture = loadTexture("gfx/alienBullet.png"); // Use alien bullet texture for enemies
	}

}

void Bullet::update()
{
	x += directionX * speed;
	y += directionY * speed;
}

void Bullet :: draw()
{
	blit(texture, x, y);
}

int Bullet :: getPositionX()
{
	return x;
}

int Bullet :: getPositionY()
{
	return y;
}

int Bullet::getWidth()
{
	return width;
}

int Bullet :: getHeight()
{
	return height;
}

Side Bullet::getSide()
{
	return side;
}
