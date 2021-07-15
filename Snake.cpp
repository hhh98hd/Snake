#include <bits/stdc++.h>
#include <windows.h>

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

    {DIR_DOWN,      DIR_RIGHT,      DIR_DOWN},
    {DIR_UP,        DIR_RIGHT,      DIR_UP  },

    {DIR_DOWN,      DIR_LEFT,       DIR_DOWN},
    {DIR_UP,        DIR_LEFT,       DIR_UP  },

    {DIR_RIGHT,     DIR_UP,         DIR_RIGHT},
    {DIR_RIGHT,     DIR_DOWN,       DIR_RIGHT},

    {DIR_LEFT,      DIR_UP,         DIR_LEFT},
    {DIR_LEFT,      DIR_DOWN,       DIR_LEFT},
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
    this->m_bTurned = false;
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

    pthread_mutex_trylock(&snakeMutex);
    switch (dir)
    {
        case DIR_DOWN:
        {
            this->direction = DIR_DOWN;
            curHead = body[0];
            body[0].x += 1;
            body[0].y = curHead.y;
            newHead = body[0];
            m_bTurned = true;
            GameModel::getInstance()->updateSnakePos(curHead, newHead, true);
            break;
        }

        case DIR_UP:
        {
            this->direction = DIR_UP;
            curHead = body[0];
            body[0].x -= 1;
            body[0].y = curHead.y;
            newHead = body[0];
            m_bTurned = true;
            GameModel::getInstance()->updateSnakePos(curHead, newHead, true);
            break;
        }

        case DIR_RIGHT:
        {
            this->direction = DIR_RIGHT;
            curHead = body[0];
            body[0].x = curHead.x;
            body[0].y += 1;
            newHead = body[0];
            m_bTurned = true;
            GameModel::getInstance()->updateSnakePos(curHead, newHead, true);
            break;
        }

        case DIR_LEFT:
        {
            this->direction = DIR_LEFT;
            curHead = body[0];
            body[0].x = curHead.x;
            body[0].y -= 1;
            newHead = body[0];
            m_bTurned = true;
            GameModel::getInstance()->updateSnakePos(curHead, newHead, true);
            break;
        }

        default:
        {
            // do nothing
            break;
        }
    } 
    pthread_mutex_unlock(&snakeMutex);
}

void Snake::move()
{
    Position prevBody;
    Position curHead;
 
    if(m_bTurned == false)
    {  
        if(GameModel::getInstance()->getGameState() == PLAYING)
        {
            switch (this->direction)
            {
                case DIR_RIGHT:
                {
                    pthread_mutex_trylock(&snakeMutex);
                    curHead = body[0];
                    body[0].y += 1;
                    Position newHead = body[0];
                    GameModel::getInstance()->updateSnakePos(curHead, newHead, true);
                    break;
                }

                case DIR_LEFT:
                {
                    pthread_mutex_trylock(&snakeMutex);
                    curHead = body[0];
                    body[0].y -= 1;
                    Position newHead = body[0];
                    GameModel::getInstance()->updateSnakePos(curHead, newHead, true);
                    break;
                }

                case DIR_DOWN:
                {
                    pthread_mutex_trylock(&snakeMutex);
                    curHead = body[0];
                    body[0].x += 1;
                    Position newHead = body[0];
                    GameModel::getInstance()->updateSnakePos(curHead, newHead, true);
                    break;
                }

                case DIR_UP:
                {
                    pthread_mutex_trylock(&snakeMutex);
                    curHead = body[0];
                    body[0].x -= 1;
                    Position newHead = body[0];
                    GameModel::getInstance()->updateSnakePos(curHead, newHead, true);
                    break;
                }

                case DIR_NONE:
                {
                    // do nothing
                }
            }
        }
    }

    if(GameModel::getInstance()->getGameState() == PLAYING)
    {
        for(uint8_t i = 1; i < body.size(); i++)
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
    }

    m_bTurned = false;
    pthread_mutex_unlock(&snakeMutex);
    Sleep(MOVE_INTERVAL);
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

void Snake::onFoodEaten()
{
    pthread_mutex_trylock(&snakeMutex);

    Position tail = this->body[this->body.size() - 1];

    switch (direction)
    {
        case DIR_UP:
        {
            Position newTail = {tail.x - 1, tail.y};
            this->body.push_back(newTail);
            break;
        }

        case DIR_DOWN:
        {
            Position newTail = {tail.x + 1, tail.y};
            this->body.push_back(newTail);
            break;
        }

        case DIR_LEFT:
        {
            Position newTail = {tail.x, tail.y + 1};
            this->body.push_back(newTail);
            break;
        }

        case DIR_RIGHT:
        {
            Position newTail = {tail.x, tail.y - 1};
            this->body.push_back(newTail);
            break;
        }

        case DIR_NONE:
        {
            // do nothing
        }
    }

    pthread_mutex_unlock(&snakeMutex);
}

void Snake::run()
{
    while(true)
    {
        GameState state = GameModel::getInstance()->getGameState();
        if(state == PLAYING)
        {
            move();
        }   
        else if(state == PAUSED)
        {
            /* paused -> do nothing */
        }
        else if(state == DIED)
        {
            this->body.clear();
            Position head;
            head.x = HEIGHT / 2;
            head.y = WIDTH * 0.15;
            this->direction = SnakeDir::DIR_RIGHT;
            this->body.push_back(head);
            head.y = head.y - 1;
            this->body.push_back(head);
            head.y = head.y - 1;
            this->body.push_back(head);
            this->direction = DIR_RIGHT;
            this->m_bTurned = false;
        }
        else if(state == QUIT)
        {
            break;
        }
    }
}
