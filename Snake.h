#include <vector>

#include "global.h"
#include "GameModel.h"

using namespace std;

#ifndef SNAKE_H
#define SNAKE_H

class Snake
{
private:
    vector<Position> body;
    SnakeDir direction;
    static Snake* s_pInstance;
    bool m_bIsAlive;
    
    Snake();
    void move();
    void turn(SnakeDir dir);
    SnakeDir getAction(SnakeDir cmd);
public:
    static Snake* getInstance();
    ~Snake();
    int getSnakeLength();
    void run();

    void onKeyPressed(SnakeDir cmd);
    void onFoodEaten();
    void onDeath();
};

#endif