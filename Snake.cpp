#include <bits/stdc++.h>

#include "Snake.h"
#include "global.h"

extern pthread_mutex_t snakeMutex;

using namespace std;

Snake* Snake::s_pInstance = nullptr;

SNAKE_ACTION_TABLE m_stActionMap[] = {
    /* cmd  */      /* dir */       /* act */
    {DIR_RIGHT,     DIR_NONE,       DIR_RIGHT},

    {DIR_DOWN,      DIR_DOWN,       DIR_NONE},
    {DIR_DOWN,      DIR_UP,         DIR_NONE},

    {DIR_UP,        DIR_DOWN,       DIR_NONE},
    {DIR_UP,        DIR_UP,         DIR_NONE},

    {DIR_LEFT,      DIR_LEFT,       DIR_NONE},
    {DIR_LEFT,      DIR_RIGHT,      DIR_NONE},

    {DIR_RIGHT,     DIR_LEFT,       DIR_NONE},
    {DIR_RIGHT,     DIR_RIGHT,      DIR_NONE},

    /////////////////////////////////////////

    {DIR_DOWN,      DIR_RIGHT,      DIR_DOWN},
    {DIR_UP,        DIR_RIGHT,      DIR_UP}
};

Snake::Snake()
{
    Position head;
    head.x = HEIGHT / 2;
    head.y = WIDTH * 0.15;
    this->direction = SnakeDir::DIR_RIGHT;
    this->body.push_back(head);
    head.y = head.y - 1;
    this->body.push_back(head);
    head.y = head.y - 1;
    this->body.push_back(head);
    head.y = head.y - 1;
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
    Position curHead, newHead;

    switch (dir)
    {
        case DIR_DOWN:
        {
            pthread_mutex_lock(&snakeMutex);
            this->direction = DIR_DOWN;
            curHead = body[0];
            body[0].x += 1;
            body[0].y = body[1].y;
            newHead = body[0];
            GameModel::getInstance()->updateSnakePos(curHead, newHead);
            pthread_mutex_unlock(&snakeMutex);
            break;
        }

        case DIR_UP:
        {
            pthread_mutex_lock(&snakeMutex);
            this->direction = DIR_UP;
            curHead = body[0];
            body[0].x -= 1;
            body[0].y = body[1].y;
            newHead = body[0];
            GameModel::getInstance()->updateSnakePos(curHead, newHead);
            pthread_mutex_unlock(&snakeMutex);
            break;
        }
    }
}

void Snake::move()
{
    Position prevBody;
    Position curHead;

    switch (this->direction)
    {
        case DIR_RIGHT:
        {
            pthread_mutex_lock(&snakeMutex);
            curHead = body[0];
            body[0].y += 1;
            Position newHead = body[0];
            GameModel::getInstance()->updateSnakePos(curHead, newHead);
            break;
        }

        case DIR_DOWN:
        {
            pthread_mutex_lock(&snakeMutex);
            curHead = body[0];
            body[0].x += 1;
            Position newHead = body[0];
            GameModel::getInstance()->updateSnakePos(curHead, newHead);
            break;
        }

        case DIR_UP:
        {
            pthread_mutex_lock(&snakeMutex);
            curHead = body[0];
            body[0].x -= 1;
            Position newHead = body[0];
            GameModel::getInstance()->updateSnakePos(curHead, newHead);
            break;
        }
    }
    
    for(int i = 1; i < body.size(); i++)
    {
        if(1 == i)
        {
            prevBody = body[i];
            body[i] = curHead;
            GameModel::getInstance()->updateSnakePos(prevBody, curHead);

        }
        else
        {
            Position curBody = body[i];
            body[i] = prevBody;
            prevBody = curBody;
            GameModel::getInstance()->updateSnakePos(prevBody, body[i]);
        }
    }
    pthread_mutex_unlock(&snakeMutex);
    _sleep(MOVE_INTERVAL);
}

void Snake::onKeyPressed(SnakeDir cmd)
{
    SnakeDir action = getAction(cmd);
    
    cout << action << endl;

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
        move();
    }
}

