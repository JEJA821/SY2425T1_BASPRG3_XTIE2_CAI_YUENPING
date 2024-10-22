#include "Player.h"
#include "Scene.h"

Player::~Player()
{
	// Memory manage our bullets. Delete all bullets on player deletetion/death
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear();
}

void Player::start()
{
	//Load Texture
	texture = loadTexture("gfx/player.png");

	//Initialize to avaoid grabage values
	y = 100;
	x = 100;
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 8; // Reload time8 frames, or 0.13 seconds
	currentReloadTime = 0;

	// Set speed values
	originalSpeed = 1.0f; // Raw speed
	increasedSpeed = 5.0f; // Increased speed
	currentSpeed = originalSpeed; // Current speed

	//Query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
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
		y -= speed;
	}
	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}
	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}
	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += speed;
	}

	// Decrement the player's reload timer
	if (currentReloadTime > 0)
		currentReloadTime--;

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width / 2, y - 2 + height / 2, 1, 0, 10);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		// After firing, reset our reload timer
		currentReloadTime = reloadTime;
	}

// Memory manage our bullets. When they go off screen, delete them
for (int i = 0; i < bullets.size(); i++)
{
	if (bullets[i]->getPositionX() > SCREEN_WIDTH)
	{
		// Cache the variable so we can delete it later
		// We can't delete it after erasing from the vector(leaked pointer)
		Bullet* bulletToErase; bullets [i];
		bullets.erase(bullets.begin() + i);
		delete bulletToErase;

		// We can't mutate (change) our vector while looping inside it
        // this might crash on the next 100p iteration
		// We can also avoid lag this way
		break;
	}
}

void Player::draw()
{
	blit(texture, x, y);
}

int Player::getPositionX()
{
	return X;
}

int Player::getPositionY()
{
	return Y;
}

