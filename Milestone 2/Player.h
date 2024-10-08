#pragma once
#include "GameObject.h"
#include "Common.h"
#include "draw.h"
#include "Scene.h" 

class Player :
    public GameObject
{
public:
    void start();
    void update();
    void draw();
    void fireWingBullets();
private:
    int x;
    int y;
    int width;
    int height;
    SDL_Texture* texture;

    int bulletCooldown;           //  Original bullet cooldown
    int wingBulletCooldown;       // Wing tip bullet cooling

private:
    float originalSpeed;
    float increasedSpeed;
    float currentSpeed;

};

class Bullet : public GameObject
{
public:
    Bullet(int startX, int startY)
    {
        x = startX;
        y = startY;
        // Initialize other properties of the bullet
    }

    void update() override
    {
        //Bullet movement logic
        y -= 5;  // Assume the bullet is moving upwards
    }

    void draw() override
    {
        // Draw the bullet
    }

private:
    int x, y;
};
