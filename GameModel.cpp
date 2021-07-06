#include <bits/stdc++.h>
#include "windows.h"

#include "GameModel.h"
#include "Snake.h"
#include "global.h"

using namespace std;

extern char box[HEIGHT + 2][WIDTH + 2];
extern pthread_mutex_t boxMutex;

using namespace std;

GameModel* GameModel::s_pInstance = nullptr;

GameModel::GameModel(){}

GameModel::~GameModel()
{
    delete s_pInstance;
    s_pInstance = nullptr;
}

GameModel* GameModel::getInstance()
{
    if(s_pInstance == nullptr)
    {
        s_pInstance = new GameModel();
    }

    return s_pInstance;
}

void GameModel::init()
{
    /* disable the cursor blinking */
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    // GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; 
    SetConsoleCursorInfo(out, &cursorInfo);

    /* setup boundaries */
    // upper boundary
    for (int i = 0; i <= WIDTH + 1; i++)
    {
        box[0][i] = WALL;
    }

    // lower boundary
    for(int i = 0; i <= WIDTH + 1; i++)
    {
        box[HEIGHT + 1][i] = WALL;
    }

    // left boundary
    for(int i = 1; i < HEIGHT + 1; i++)
    {
        box[i][0] = WALL;
    }

    // right boundary
    for(int i = 1; i < HEIGHT + 1; i++)
    {
        box[i][WIDTH + 1] = WALL;
    }

    // initial position of the snake
    box[(int)(HEIGHT / 2)][(int)(WIDTH * 0.15) - 2] = BODY;
    box[(int)(HEIGHT / 2)][(int)(WIDTH * 0.15) - 1] = BODY;
    box[HEIGHT / 2][(int)(WIDTH * 0.15)] = HEAD;
}

void GameModel::updateSnakePos(Position curPos, Position newPos, bool isHead)
{
    int curRow = curPos.x;
    int curCol = curPos.y;

    int newRow = newPos.x;
    int newCol = newPos.y;

    pthread_mutex_lock(&boxMutex);
    
    if(isHead == true)
    {
        if(box[newRow][newCol] == WALL)
        {
            box[curRow][curCol] = HEAD;
            Snake::getInstance()->onDeath();
        }
        else
        {
            box[curRow][curCol] = EMPTY;
            box[newRow][newCol] = HEAD;
        }
    }
    else
    {
        box[curRow][curCol] = EMPTY;
        box[newRow][newCol] = BODY;
    }

    pthread_mutex_unlock(&boxMutex);
}

Position GameModel::genFood()
{
    Position foodPos = {0, 0};
    return foodPos;
}