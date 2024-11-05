#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

	points = 0;
	powerUpActive = false; 
	firingLevel = 1;

	for (Enemy* enemy : spawnedEnemies) {
		delete enemy;
	}
	spawnedEnemies.clear();
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	initFonts();
	currentSpawnTimer = 300;
	spawnTime = 300;// Spawn time of 5 seconds

	for (int i = 0; i < 3; i++)
	{
		spawn();
		currentSpawnTimer = spawnTime;
	}

	// load the background texture
	backgroundTexture = loadTexture("gfx/background.png");
	explosionTexture = loadTexture("gfx/explosion.png");
	explosionTimer = 0; // No explosion initially

	powerUpTimer = 0; // No power-up initially
}

void GameScene::draw()
{
	Scene::draw();

	drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

	if(player->getIsAlive() == false)
	{ 
		drawText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "GAME OVER!");
	}

	//render the background
	if (backgroundTexture) {
		blit(backgroundTexture, 0, 0); // Assuming full-screen background
	}

	// Draw explosion if timer is active
	if (explosionTimer > 0) {
		blit(explosionTexture, explosionX, explosionY);
		explosionTimer--; // Countdown explosion timer
	}

	if (powerUpActive)
	{
		// Draw Power-Up, assuming there is a function loadTexture and blit
		blit(loadTexture("gfx/playerBullet.png"), powerUpX, powerUpY);
	}

	for (Enemy* enemy : spawnedEnemies) {
		if (enemy->getIsBoss()) {
			// Draw the Boss
			SDL_Texture* bossTexture = loadTexture("gfx/enemy.png");
			blit(bossTexture, enemy->getPositionX(), enemy->getPositionY());
		}
		else {
			enemy->draw();
		}
	}
}

void GameScene::update()
{
	Scene::update();

	doSpawnLogic(); 
	doCollisionLogic();

	// Generates the Power-Up logic
	if (!powerUpActive && rand() % 100 < 2) // 2% probability of generating a Power-Up
	{
		powerUpX = rand() % (SCREEN_WIDTH - 50);  // Random horizontal position
		powerUpY = 0;  // Generated at the top
		powerUpActive = true;  // Activate Power-Up
	}

	if (powerUpActive)
	{
		powerUpY += 2;  // Power-Up Moves down

		// Check whether the Power-Up crosses the bottom of the screen
		if (powerUpY > SCREEN_HEIGHT)
		{
			powerUpActive = false;  // Power-Up disappears
		}

		// Check if the player has collected a Power-Up
		if (checkCollision(player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
			powerUpX, powerUpY, 50, 50)) // Assume that the Power-Up size is 50x50
		{
			powerUpActive = false;  // Power-Up is collected
			firingLevel++;  // Increase the emission level
			player->increaseFiringLevel();  // Upgrade the launch level
		}
	}

	if (points >= bossSpawnThreshold && !isBossActive) {
		spawnBoss();
	}

	if (isBossActive) {
		updateBossLogic();
	}
	else {
		doSpawnLogic();
	}
}

void GameScene::doSpawnLogic()
{
	if (currentSpawnTimer > 0)
	{
		currentSpawnTimer--;

		if (currentSpawnTimer <= 0)
		{
			spawn();
		}
		currentSpawnTimer = spawnTime;
	}
}

void GameScene::doCollisionLogic()
{
	// Check for collision
	for (int i = 0; i < objects.size(); i++)
	{
		//Cast to bulllet
		Bullet* bullet = dynamic_cast<Bullet*> (objects[i]);
		//Check if the cast was successful (i,e, objects[i] is a Bullet) 
		if (bullet != NULL)
		{
			// If the bullet is from the enemy side, check against the player
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
					player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
				);
				if (collision == 1)
				{
					player->doDeath();
					break;
				}
			}
			//If the bullet is from the player side, check against ALL enemies
			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(
						currentEnemy->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);
					if (collision == 1)
					{
						despawnEnemy(currentEnemy);
						//Increment points
						points++;
						// IMPORTANT: only despawn one a tine.
						// othendise we might crash due to looping
						break;
					}
				}
			}
		}
	}
}

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(rand() % (SCREEN_WIDTH - enemy->getWidth()), SCREEN_HEIGHT/2);
	addGameObject(enemy);
	spawnedEnemies.push_back(enemy);
	currentSpawnTimer = spawnTime;
}

void GameScene::despawnEnemy(Enemy* enemy)
{
	int index = -1; 
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		// If the pointer matches
		if (enemy == spawnedEnemies[i])
		{
			index = i;
			break;
		}
	}
	// If any match is found
	if (index != -1)
	{
		spawnedEnemies.erase(spawnedEnemies.begin() + index); 
		delete enemy;
	}

	if (enemy) {
		// Set explosion position and start timer
		explosionX = enemy->getPositionX();
		explosionY = enemy->getPositionY();
		explosionTimer = 30; // Display for 30 frames (adjust as needed)

		spawnedEnemies.erase(std::remove(spawnedEnemies.begin(), spawnedEnemies.end(), enemy), spawnedEnemies.end());
		delete enemy;
	}
}

void GameScene::spawnBoss() {
	isBossActive = true;
	bossEnemy = new Enemy();
	bossEnemy->setHealth(100);  // Set the Boss's high health
	bossEnemy->setFiringRate(5);  // Set the Boss to shoot faster
	bossEnemy->setPosition(SCREEN_WIDTH / 2, 50);  // Top center of the screen
	bossEnemy->setIsBoss(true);
	spawnedEnemies.push_back(bossEnemy);  // Join the scene
	bossPatternSwitchTimer = 200;  // Mode switching interval
}

void GameScene::updateBossLogic() {
	if (bossPatternSwitchTimer-- <= 0) {
		// Switch modes each time
		bossEnemy->switchPattern();
		bossPatternSwitchTimer = 200;  // Reset the switch timer
	}

	if (bossEnemy->isDefeated()) {
		despawnEnemy(bossEnemy);
		resetAfterBossDefeat();
	}
}

void GameScene::resetAfterBossDefeat() {
	isBossActive = false;
	bossEnemy = nullptr;
	points = 0;  // or reset points by other means
}