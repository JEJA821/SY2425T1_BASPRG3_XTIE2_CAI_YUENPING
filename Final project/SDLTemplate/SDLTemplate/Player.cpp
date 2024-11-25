#include "Player.h"
#include "input.h"

Player::Player(int startX, int startY)
{
	x = startX;
	y = startY;
	width = 32;
	height = 32;
	texture = loadTexture("gfx/player.png");
}

Player::~Player()
{
	// Clean up texture resources
	SDL_DestroyTexture(texture);
}

void Player::update()
{
	if (app.keyboard[SDL_SCANCODE_LEFT])
	{
		x -= 5;
		if (x < 0) x = 0;
	}
	if (app.keyboard[SDL_SCANCODE_RIGHT])
	{
		x += 5;
		if (x + width > SCREEN_WIDTH) x = SCREEN_WIDTH - width;
	}
}

void Player::draw()
{
	blit(texture, x, y);
}