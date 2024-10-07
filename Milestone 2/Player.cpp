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

	// 原有移动逻辑...

	// 检查是否按下 G 键并发射翼端子弹
	if (app.keyboard[SDL_SCANCODE_G] && wingBulletCooldown <= 0)
	{
		// 从飞船的左翼和右翼发射子弹
		fireWingBullets();
		wingBulletCooldown = 50;  // 假设冷却时间为 50 帧，可以根据需要调整
	}

	// 递减冷却时间
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
	// 发射左翼子弹
	Bullet* leftWingBullet = new Bullet(x - width / 2, y);  // 左侧的子弹位置
	Scene::getActiveScene()->addGameObject(leftWingBullet);

	// 发射右翼子弹
	Bullet* rightWingBullet = new Bullet(x + width / 2, y);  // 右侧的子弹位置
	Scene::getActiveScene()->addGameObject(rightWingBullet);
}
