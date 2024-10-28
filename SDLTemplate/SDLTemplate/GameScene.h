#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	Player* player;
	Enemy* enemy;

	// Enemy spawning logic
	float spawnTime;
	float currentSpawnTimer;
	std::vector<Enemy*> spawnedEnemies;

	void doSpawnLogic(); 
	void doCollisionLogic();
	void spawn();
	void despawnEnemy(Enemy* enemy);

	int points;

	// add a texture for the background
	SDL_Texture* backgroundTexture;
	SDL_Texture* explosionTexture; // Texture for explosion
	int explosionX, explosionY;    // Position of explosion
	int explosionTimer;            // Timer to control duration

	int powerUpX, powerUpY; 
	bool powerUpActive; 
	int powerUpTimer; 
	int firingLevel;
};
