#include "GameScene.h"
#include "Player.h"
#include "Obstacle.h"
#include "util.h"
#include "SoundManager.h"
#include "text.h"
#include "draw.h"
#include "Scene.h"

GameScene::GameScene(int startLevel)
	: level(startLevel), isGameOver(false), isLevelCompleted(false), lastLevelScore(0), levelCompleteTimer(0), obstacleSpeed(5 + startLevel)
{
	// Initialize the player
	player = new Player(SCREEN_WIDTH / 2 - 16, SCREEN_HEIGHT - 48);
	addGameObject(player);

	// Initialize the game parameters
	score = 0;
	spawnTimer = 0;
	spawnInterval = 60 - level * 5;   // Reduce the spawn interval per level
	if (spawnInterval < 20) spawnInterval = 20;   // Limit the minimum generation interval
	obstacleSpeed = 5 + level;   // Increase obstacle speed per level

	// Load the background texture
	backgroundTexture = loadTexture("gfx/background.png");

	// Play background music
	SoundManager::loadMusic("sounds/background_music.wav");
	SoundManager::playMusic(-1);   // Loop background music
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
	drawText(10, 10, 255, 255, 255, TEXT_LEFT, "LEVEL %d", level);
	drawText(10, 50, 255, 255, 255, TEXT_LEFT, "SCORE %d", score);

	drawTutorial();

	// Display the game status prompt
	if (isLevelCompleted)
	{
		SoundManager::playSound("sounds/level_complete.wav");
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 255, 0, TEXT_CENTER, "LEVEL COMPLETE");
	}
	else if (isGameOver)
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 0, 0, TEXT_CENTER, "GAME OVER");
	}
}

void GameScene::update()
{
	if (isGameOver)
	{
		prepareScene();
		draw();
		presentScene();

		printf("Game Over!  Final Score: %d\n", score);

		// Game end logic
		SoundManager::playSound("sounds/game_over.wav");
		Mix_HaltMusic();    // Stop background music
		SDL_Delay(5000);    // The "GAME OVER" screen is displayed after a delay of 2 seconds
		SDL_Quit();         // Disable SDL
		exit(0);            // Exit the program
	}

	if (isLevelCompleted)
	{
		levelCompleteTimer++;
		if (levelCompleteTimer >= 30) // Displays the prompt for 3 seconds
		{
			isLevelCompleted = false;   // Restore the game state
			levelCompleteTimer = 0;     // Reset the timer
		}
		return;  // No other logic is executed when the prompt is displayed
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

		// Increase the score
		score++;
		printf("Score Updated: %d\n", score);
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
				SoundManager::playSound("sounds/hit.wav");

				isGameOver = true;
				break;
			}

			// Player score
			if (obstacle->getY() > SCREEN_HEIGHT)
			{
				score++;
				// Remove obstacles from the scene
				Scene::getActiveScene()->removeGameObject(obstacle);
			}
		}
	}

	// Check whether the level is completed
	if (score >= lastLevelScore + 20) // Level up every 20 points
	{
		level++;
		printf("Level Complete!  New Level: %d\n", level);
		lastLevelScore = score;  // Update the score of the last upgrade
		isLevelCompleted = true;

		if (spawnInterval > 20) spawnInterval -= 5;  // Speed up obstacle generation
		if (obstacleSpeed < 15) obstacleSpeed += 5;  // Increase obstacle speed
	}
}

void GameScene::drawTutorial()
{
	// Dynamically calculate the starting position of each line of text to ensure that the text is fully displayed on the screen
	int textWidth1 = strlen("USE LEFT AND RIGHT") * GLYPH_WIDTH;
	int textWidth2 = strlen("THEN AVOID OBSTACLE") * GLYPH_WIDTH;

	int rightMargin = 230;  // Control the distance between text and the right side of the screen

	int xOffset1 = SCREEN_WIDTH - textWidth1 - rightMargin;
	int xOffset2 = SCREEN_WIDTH - textWidth2 - rightMargin;

	drawText(xOffset1, 10, 255, 255, 255, TEXT_LEFT, "USE LEFT AND RIGHT");
	drawText(xOffset2, 50, 255, 255, 255, TEXT_LEFT, "THEN AVOID OBSTACLE");
}

