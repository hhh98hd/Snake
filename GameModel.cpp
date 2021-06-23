#include <bits/stdc++.h>

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
    box[HEIGHT / 2][(int)(WIDTH * 0.15)] = BODY;
}

void GameModel::updateSnakePos(Position curPos, Position newPos)
{
    int curRow = curPos.x;
    int curCol = curPos.y;

    int newRow = newPos.x;
    int newCol = newPos.y;

    pthread_mutex_lock(&boxMutex);
    box[curRow][curCol] = EMPTY;
    box[newRow][newCol] = BODY;
    pthread_mutex_unlock(&boxMutex);
}
