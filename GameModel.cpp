#include <bits/stdc++.h>
#include <windows.h>

#include "GameModel.h"
#include "Snake.h"
#include "Renderer.h"
#include "global.h"

// using namespace std;

extern char box[HEIGHT + 2][WIDTH + 2];
extern pthread_mutex_t boxMutex;

using namespace std;

GameModel* GameModel::s_pInstance = nullptr;

GameModel::GameModel()
{
    this->m_iTotalScore = 0;
}

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
    box[(int)(HEIGHT / 2)][(int)(WIDTH * 0.15) - 2] = BODY;
    box[(int)(HEIGHT / 2)][(int)(WIDTH * 0.15) - 1] = BODY;
    box[HEIGHT / 2][(int)(WIDTH * 0.15)] = HEAD;

    // initial position of food
    box[(int)(HEIGHT / 2)][(int)(WIDTH * 0.15) + 30] = FOOD;
}

void GameModel::updateSnakePos(Position curPos, Position newPos, bool isHead)
{
    int curRow = curPos.x;
    int curCol = curPos.y;

    int newRow = newPos.x;
    int newCol = newPos.y;

    pthread_mutex_trylock(&boxMutex);
    
    if(isHead == true)
    {
        if( (box[newRow][newCol] == WALL) || (box[newRow][newCol] == BODY) || (box[newRow][newCol] == HEAD) )
        {
            box[curRow][curCol] = HEAD;
            notifyGameOver();
        }
        else if(box[newRow][newCol] == FOOD)
        {
            Snake::getInstance()->onFoodEaten();
            this->m_iTotalScore += FOOD_SCORE;
            genFood();
            box[curRow][curCol] = EMPTY;
            box[newRow][newCol] = HEAD;
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

void GameModel::notifyGameOver()
{
    Snake::getInstance()->onDeath();
    Sleep(250);
    pthread_mutex_trylock(&boxMutex);
    for(int i = 0; i <= HEIGHT + 1; i++)   
    {
        for(int j = 0; j <= WIDTH + 1; j++)
        {
            if(box[i][j] == HEAD || box[i][j] == BODY || box[i][j] == FOOD)
            {
                box[i][j] = EMPTY;
            }
        }
    }
    Renderer::getInstance()->gameOver();
    pthread_mutex_unlock(&boxMutex);
}

void GameModel::genFood()
{
    int foodRow, foodCol;

    srand(time(NULL));
    do
    {
        foodRow = rand() % WIDTH;
        foodCol = rand() % HEIGHT;
    } 
    while (box[foodRow][foodCol] != EMPTY);
    
    pthread_mutex_trylock(&boxMutex);

    box[foodRow][foodCol] = FOOD;

    pthread_mutex_unlock(&boxMutex);
}

int GameModel::getCurrentScore()
{
    return this->m_iTotalScore;
}