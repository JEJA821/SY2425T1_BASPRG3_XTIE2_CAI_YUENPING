#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

enum class Side
{
    PLAYER_SIDE,
    ENEMY_SIDE
};

class Bullet : public GameObject
{
public:
    Bullet(float PositionX, float PositionY, float directionX, float directionY, float speed, Side side);
    void start();
    void update(); 
    void draw();
    int getPositionX(); 
    int getPositionY();
    int getWidth();
    int getHeight();
    Side getSide();

private:
    SDL_Texture* texture;
    Side side;
    float x; 
    float y;
    int height;
    int width;
    int speed;
    float directionX;
    float directionY;
};

