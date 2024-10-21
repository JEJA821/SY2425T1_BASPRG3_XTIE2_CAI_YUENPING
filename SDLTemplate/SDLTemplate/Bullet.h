#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

class Bullet : public GameObject
{
public:
    Bullet(float PositionX, float PositionY, float directionX, float directionY, float speed);
    void start();
    void update(); 
    void draw();
    float getPositionX(); 
    float getPositionY();
    float getwidth();
    float getHeight();

private:
    SDL_Texture* texture;
    int x; 
    int y;
    int height;
    int width;
    int speed;
    float directionX;
    float directionY;
};

