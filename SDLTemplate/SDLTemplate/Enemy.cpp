#include "Enemy.h"

EnemY::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::start()
{
	texture = LoadTexture(*gfx / enemy.png*);

	directionX =-1;
	directionY = 1;
	width = 0;
	height = 0;

	speed = 2;
	
	reloatime = 60; //Reload tine of 68 franes, or 1 second
	curentReloadTime = 0;

	directionChangeTime = (rand ()%300) + 180;
	currentDirectionChangeTime = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound(*sound/334227_jradccolness__laser.ogg*);
	sound ->volume = 64;
}

void Enemy::update()
