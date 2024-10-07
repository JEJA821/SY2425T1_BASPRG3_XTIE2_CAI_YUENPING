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

    int bulletCooldown;           // 原始子弹冷却
    int wingBulletCooldown;       // 翼端子弹冷却

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
        // 初始化子弹的其他属性
    }

    void update() override
    {
        // 子弹移动逻辑
        y -= 5;  // 假设子弹向上移动
    }

    void draw() override
    {
        // 绘制子弹
    }

private:
    int x, y;
};
