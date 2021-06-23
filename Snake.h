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
    Snake();
    void moveDownOne();
    void moveRightOne();
public:
    static Snake* getInstance();
    ~Snake();
    int getSnakeLength();
    void setDirection(SnakeDir dir);
    void run();
};

#endif