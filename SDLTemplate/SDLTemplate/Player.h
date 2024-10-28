#pragma once
#include "GameObject.h"
#include "Common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>

class Player : public GameObject
{
public:
    ~Player();
    void start();
    void update();
    void draw();

    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
    bool getIsAlive(); 
    void doDeath();

    void increaseFiringLevel();  // Added method to increase the emission level
    void fire();

private:
    int x;
    int y;
    int width;
    int height;
    int speed;
    SDL_Texture* texture;
    Mix_Chunk* sound;

    float reloadTime;
    float currentReloadTime;
    std::vector<Bullet*> bullets;
    bool isAlive;

    float originalSpeed;
    float increasedSpeed;
    float currentSpeed;

    int firingLevel;  // Current emission level
};

