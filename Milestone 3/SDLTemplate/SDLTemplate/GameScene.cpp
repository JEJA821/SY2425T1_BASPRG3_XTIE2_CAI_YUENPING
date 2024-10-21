#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here
	currentSpawnTimer = 300;
	spawnTime = 300;// Spawn time of 5 seconds

	for (int i = 0; i < 3; i++)
	{
		spawn();
		currentSpawnTimer = spawnTime;
	}
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();

	if (currentSpawnTimer > 0) 
		currentSpawnTimer--;

	if (currentSpawnTimer <= 0)
	{
		spawn();
	}
}

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(1200, 300 + (rand() % 300));
	spawnedEnemies.push_back(enemy);
	currentSpawnTimer = spawnTime;
}
