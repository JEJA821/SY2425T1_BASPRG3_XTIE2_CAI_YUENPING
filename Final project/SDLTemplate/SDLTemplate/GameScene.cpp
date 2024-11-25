#include "GameScene.h"
#include "Player.h"
#include "Obstacle.h"
#include "util.h"
#include "SoundManager.h"
#include "text.h"
#include "draw.h"
#include "Scene.h"

GameScene::GameScene(int startLevel)
	: level(startLevel), isGameOver(false), isLevelCompleted(false)
{
	// Initialize the player
	player = new Player(SCREEN_WIDTH / 2 - 16, SCREEN_HEIGHT - 48);
	addGameObject(player);

	// Initialize the game parameters
	score = 0;
	spawnTimer = 0;
	spawnInterval = 60 - level * 5;  // Reduce the spawn interval per level
	if (spawnInterval < 20) spawnInterval = 20;  // Limit the minimum generation interval
	obstacleSpeed = 5 + level;  // Increase obstacle speed per level

	// Load the background texture
	backgroundTexture = loadTexture("gfx/background.png");

	// Play background music
	SoundManager::loadMusic("sounds/background_music.wav");
	SoundManager::playMusic(-1);  // Loop background music
}

GameScene::~GameScene()
{
	SDL_DestroyTexture(backgroundTexture);
}

void GameScene::start()
{
	Scene::start();
}

void GameScene::draw()
{
	// Draw the background
	SDL_RenderCopy(app.renderer, backgroundTexture, NULL, NULL);

	// Call the drawing method of the base class
	Scene::draw();

	// Show scores and levels
	drawText(10, 10, 255, 255, 255, TEXT_LEFT, "Score: %d", score);
	drawText(10, 30, 255, 255, 255, TEXT_LEFT, "Level: %d", level);

	// Display the game status prompt
	if (isLevelCompleted)
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20, 0, 255, 0, TEXT_CENTER, "Level Complete!");
	}
	else if (isGameOver)
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20, 255, 0, 0, TEXT_CENTER, "GAME OVER");
	}
}

void GameScene::update()
{
	if (isGameOver)
	{
		prepareScene();
		draw();
		presentScene();
		// Game end logic
		SoundManager::playSound("sounds/game_over.wav");
		Mix_HaltMusic();   // Stop background music
		SDL_Delay(2000);   // The "GAME OVER" screen is displayed after a delay of 2 seconds
		SDL_Quit();        // Disable SDL
		exit(0);           // Exit the program
	}

	if (isLevelCompleted)
	{
		prepareScene();
		draw();
		presentScene();
		// Level completion logic
		Mix_HaltMusic();   // Stop background music
		SDL_Delay(2000);   // The "Level Complete" screen is displayed after a delay of 2 seconds
		Scene::setActiveScene(new GameScene(level + 1));  // Proceed to the next level
		delete this;   // Delete the current level object
		return;
	}

	// Update the game logic
	Scene::update();

	// Obstacle generation logic
	spawnTimer++;
	if (spawnTimer >= spawnInterval)
	{
		spawnTimer = 0;
		int startX = rand() % (SCREEN_WIDTH - 32);
		Obstacle* obstacle = new Obstacle(startX, -32);
		obstacle->setSpeed(obstacleSpeed);
		addGameObject(obstacle);
	}

	// Collision detection and bonus points
	for (auto obj : objects)
	{
		Obstacle* obstacle = dynamic_cast<Obstacle*>(obj);
		if (obstacle)
		{
			// Collision detection
			if (checkCollision(
				player->getX(), player->getY(), player->getWidth(), player->getHeight(),
				obstacle->getX(), obstacle->getY(), obstacle->getWidth(), obstacle->getHeight()))
			{
				isGameOver = true;
				break;
			}

			// Player score
			if (obstacle->getY() > SCREEN_HEIGHT)
			{
				score++;
			}
		}
	}

	// Increase the level difficulty
	if (spawnTimer % 600 == 0)
	{
		level++;
		if (spawnInterval > 20) spawnInterval -= 5;
		if (obstacleSpeed < 15) obstacleSpeed += 1;
	}

	// Check whether the level is completed
	if (score >= 50) // Assume that the player reaches 50 points to complete the level
	{
		isLevelCompleted = true;
	}
}