#include <bits/stdc++.h>

#include "Snake.h"
#include "global.h"

extern pthread_mutex_t snakeMutex;

using namespace std;

Snake* Snake::s_pInstance = nullptr;

SNAKE_ACTION_TABLE m_stActionMap[] = {
    /* cmd  */      /* dir */       /* act */
    {DIR_DOWN,      DIR_DOWN,       DIR_NONE},
    {DIR_DOWN,      DIR_UP,         DIR_NONE},

    {DIR_UP,        DIR_DOWN,       DIR_NONE},
    {DIR_UP,        DIR_UP,         DIR_NONE},

    {DIR_LEFT,      DIR_LEFT,       DIR_NONE},
    {DIR_LEFT,      DIR_RIGHT,      DIR_NONE},

    {DIR_RIGHT,     DIR_LEFT,       DIR_NONE},
    {DIR_RIGHT,     DIR_RIGHT,      DIR_NONE},

    /////////////////////////////////////////

    {DIR_RIGHT,     DIR_DOWN,       DIR_RIGHT},
    {DIR_RIGHT,     DIR_UP,         DIR_RIGHT}
};

Snake::Snake()
{
    Position head;
    head.x = HEIGHT / 2;
    head.y = WIDTH * 0.15;
    this->direction = SnakeDir::DIR_NONE;
    this->body.push_back(head);
    head.x = head.x - 1;
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

SnakeDir Snake::getAction(SnakeDir cmd)
{
    int iSize = sizeof(m_stActionMap) / sizeof(SNAKE_ACTION_TABLE);
    for(int i = 0; i < iSize; i++)
    {
        if(m_stActionMap[i].cmd == cmd && m_stActionMap[i].currentDir == direction)
        {
            return m_stActionMap[i].action;
        }
    }

    // not found -> keep the current direction
    return DIR_NONE;
}

void Snake::turn(SnakeDir dir)
{
    switch (dir)
    {
        case DIR_RIGHT:
        {
            pthread_mutex_lock(&snakeMutex);
            this->direction = DIR_RIGHT;
            Position oldHead = body[0];
            int oldRow = oldHead.x;
            int oldCol = oldHead.y;
            Position newHead;
            int newRol = oldRow;
            int newCol = oldCol + 1;
            body[0] = newHead;
            GameModel::getInstance()->updateSnakePos(oldHead, newHead);
            pthread_mutex_unlock(&snakeMutex);

            break;
        }
    }
}

void Snake::move()
{
    for(int i = 1; i < body.size(); i++)
    {
        Position curPos, newPos;
        GameModel::getInstance()->updateSnakePos(curPos, newPos);
    }
}

void Snake::onKeyPressed(SnakeDir cmd)
{
    SnakeDir action = getAction(cmd);
    if(action != DIR_NONE)
    {
        turn(action);
    }
    else
    {
        // maintain direction
    }
}

void Snake::run()
{
    while (true)
    {
        pthread_mutex_lock(&snakeMutex);
        move();
        pthread_mutex_unlock(&snakeMutex);
        _sleep(MOVE_INTERVAL);
    }
}

