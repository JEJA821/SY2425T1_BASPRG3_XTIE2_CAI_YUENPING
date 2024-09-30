#include "Player.h"

void Player::start()
{
	//Load Texture
	texture = loadTexture("gfx/player.png");

	//Initialize to avaoid grabage values
	y = 100;
	x = 100;
	width = 0;
	height = 0;

	//Query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Player::update()
{
	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= 1;
	}
	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += 1;
	}
	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= 1;
	}
	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += 1;
	}
}

void Player::draw()
{
	blit(texture, x, y);
}