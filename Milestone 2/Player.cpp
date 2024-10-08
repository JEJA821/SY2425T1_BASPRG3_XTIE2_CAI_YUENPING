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
	originalSpeed = 1.0f; // Raw speed
	increasedSpeed = 5.0f; // Increased speed
	currentSpeed = originalSpeed; // Current speed

	//Query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Player::update()
{
	// Detect key presses and adjust speed
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

	// Original movement logic...

	// Check if G is pressed and fire the wing bullet
	if (app.keyboard[SDL_SCANCODE_G] && wingBulletCooldown <= 0)
	{
		// Fire bullets from the left and right wings of the spacecraft
		fireWingBullets();
		wingBulletCooldown = 50; 
		// Assume the cooldown time is 50 frames, you can adjust it as needed
	}

	// Decrease cooldown time
	if (bulletCooldown > 0)
	{
		bulletCooldown--;
	}
	if (wingBulletCooldown > 0)
	{
		wingBulletCooldown--;
	}
}

void Player::draw()
{
	blit(texture, x, y);
}

void Player::fireWingBullets()
{
	// Fire left wing bullet
	Bullet* leftWingBullet = new Bullet(x - width / 2, y);  // The bullet position on the left
	Scene::getActiveScene()->addGameObject(leftWingBullet);

	// Fire right wing bullet
	Bullet* rightWingBullet = new Bullet(x + width / 2, y);  // The bullet position on the righ
	Scene::getActiveScene()->addGameObject(rightWingBullet);
}
