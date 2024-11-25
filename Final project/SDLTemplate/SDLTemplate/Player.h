#pragma once
#include "GameObject.h"
#include "draw.h"

class Player :
    public GameObject
{
public:
    // constructor to set the initial position
    Player(int startX, int startY);

    // Destructor to clean up texture resources
    ~Player();

    // Override the update method of the base class
    void update() override;

    // Override the drawing method of the base class
    void draw() override;

    // Get player position and size
    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int x, y;            // Player location
    int width, height;   // Player size
    SDL_Texture* texture;  // Player texture
};

