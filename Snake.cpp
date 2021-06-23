#include <bits/stdc++.h>

#include "Snake.h"
#include "global.h"

using namespace std;

Snake* Snake::s_pInstance = nullptr;

Snake::Snake()
{
    Position head;
    head.x = HEIGHT / 2;
    head.y = WIDTH * 0.15;
    this->direction = SnakeDir::DIR_NONE;
    this->body.push_back(head);
}

Snake::~Snake()
{
    delete s_pInstance;
    s_pInstance = nullptr;
}

Snake* Snake::getInstance()
{
    if(s_pInstance == nullptr)
    {
        s_pInstance = new Snake();
    }

    return s_pInstance;
}

int Snake::getSnakeLength()
{
    return this->body.size();
}

void Snake::setDirection(SnakeDir dir)
{
    this->direction = dir;
}

void Snake::moveDownOne()
{
    this->direction = DIR_DOWN;
    for(int i = 0; i < body.size(); i++)
    {
        Position curPos, newPos;
        curPos = body[i];
        body[i].x += 1;
        newPos = body[i];
        GameModel::getInstance()->updateSnakePos(curPos, newPos);
    }
}

void Snake::moveRightOne()
{

}

void Snake::run()
{
    while (true)
    {
        if(this->direction == DIR_DOWN)
        {
            moveDownOne();
        }
        _sleep(MOVE_INTERVAL);
    }
}

