#pragma once
#include "GameObject.h"
#include "Common.h"
#include "draw.h"

class Player :
    public GameObject
{
public:
    void start();
    void update();
    void draw();
private:
    int x;
    int y;
    int width;
    int height;
    SDL_Texture* texture;

    float originalSpeed;
    float increasedSpeed;
    float currentSpeed;
};

