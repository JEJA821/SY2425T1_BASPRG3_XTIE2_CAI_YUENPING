#pragma once
#include "GameObject.h"
#include "draw.h"

class Obstacle :
    public GameObject
{
public:
    // constructor to set the initial position
    Obstacle(int startX, int startY);

    // Destructor to clean up texture resources
    ~Obstacle();

    // Override the update method of the base class
    void update() override;

    // Override the drawing method of the base class
    void draw() override;

    void setSpeed(int speed) { this->speed = speed; } // Set the obstacle speed

    // Obtain the location and dimensions of obstacles
    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int x, y;            // Location of obstacles
    int width, height;   // Obstacle size
    SDL_Texture* texture;  // Obstacle texture
    int speed;  // Obstacle speed
};

