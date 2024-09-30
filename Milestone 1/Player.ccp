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

	// Set speed values
	originalSpeed = 1.0f; // 原始速度
	increasedSpeed = 5.0f; // 增加的速度
	currentSpeed = originalSpeed; // 当前速度

	//Query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Player::update()
{
	// 检测按键并调整速度
	if (app.keyboard[SDL_SCANCODE_LSHIFT]) {
		currentSpeed = increasedSpeed;
	}
	else if (app.keyboard[SDL_SCANCODE_BACKSPACE]) {
		currentSpeed = originalSpeed;
	}

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
