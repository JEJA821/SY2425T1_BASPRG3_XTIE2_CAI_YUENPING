#pragma once
#include "GameObject.h"
class Bullet :
    public GameObject
{
public：
    Bullet(float positionX, float PositionY, float directionX, float directionY)
    void start();
    void update(); 
    void draw();

    int getPositionx(); 
    int getPositionY();
    int getwidth();
    int getHeight();

    Side getSide();

private:
    Side getSide();
    
    int x; 
    int y;
    int height;
    int width;
    
    SDL_Texture* texture;
    
    float speed;
    float directionX;
    fLoat dinectionY;
};

