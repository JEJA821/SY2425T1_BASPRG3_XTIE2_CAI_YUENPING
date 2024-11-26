#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include <SDL.h>

class GameScene : public Scene
{
public:
    // Constructor and Destructor
    GameScene(int level = 1);  // Constructor for loading specific level, default to level 1
    ~GameScene();

    // Core Scene Methods
    void start() override;  // Initialize the scene
    void draw() override;   // Render the scene
    void update() override; // Update scene logic

private:
    // Player object
    Player* player;

    // Obstacle spawning
    int spawnTimer;       // Timer used to generate obstacles
    int spawnInterval;    // Obstacle generation interval

    // Game state
    bool isGameOver;        // Flag to check if the game is over
    bool isLevelCompleted;  // Flag to check if the level is completed
    int level;              // Current level
    int obstacleSpeed;      // Speed of the obstacles
    int score;              // Player's score

    // Background
    SDL_Texture* backgroundTexture; // Background texture

    void drawTutorial();
};
