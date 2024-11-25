#include "Obstacle.h"
#include "Scene.h"

Obstacle::Obstacle(int startX, int startY)
{
	x = startX;
	y = startY;
	width = rand() % 20 + 20;// Random width
	height = 32;
	texture = loadTexture("gfx/obstacle.png");
	speed = 5;
}

Obstacle::~Obstacle()
{
	// Clean up texture resources
	SDL_DestroyTexture(texture);
}

void Obstacle::update()
{
	y += speed;  // The obstacle moves down
	if (y > SCREEN_HEIGHT)
	{
		// Self-destruct after leaving the screen
		Scene::getActiveScene()->removeGameObject(this);
	}
}

void Obstacle::draw()
{
	blit(texture, x, y);
}
