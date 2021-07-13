#include <bits/stdc++.h>
#include <windows.h>

#include "GameModel.h"
#include "Snake.h"
#include "Renderer.h"
#include "global.h"

extern char box[HEIGHT + 2][WIDTH + 2];
extern pthread_mutex_t boxMutex;
pthread_mutex_t selMutex = PTHREAD_MUTEX_INITIALIZER;

using namespace std;

GAME_STATE_TABLE m_stStateMap[] = {
/* curState */    /* selection */     /*nextState*/    /* optNum */
    {DIED,              1,              PAUSED,            2},
    {DIED,              2,              QUIT   ,            2},

    /* pause/resume the game */
    {PLAYING,           0,              PAUSED,             0},
    {PAUSED,            0,              PLAYING,            0}
};

GameModel* GameModel::s_pInstance = nullptr;

GameModel::GameModel()
{
    this->m_iTotalScore = 0;
    this->m_iCursorPos = 1;
    this->m_eState = PAUSED;
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
    box[(int)(HEIGHT / 2)][(int)(WIDTH * 0.15) + 15] = FOOD;

    // disable cursor blinking
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = false; 
    SetConsoleCursorInfo(out, &cursorInfo);
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
        if(box[curRow][curCol] != FOOD || box[curRow][curCol] != BODY)
        {
            box[curRow][curCol] = EMPTY;
            box[newRow][newCol] = BODY;
        }
    }

    pthread_mutex_unlock(&boxMutex);
}

void GameModel::notifyGameOver()
{
    Sleep(150);
    pthread_mutex_trylock(&boxMutex);
    for(int i = 0; i <= HEIGHT + 1; i++)   
    {
        for(int j = 0; j <= WIDTH + 1; j++)
        {
            if(box[i][j] != WALL)
            {
                box[i][j] = EMPTY;
            }
        }
    }
    pthread_mutex_unlock(&boxMutex);
    this->m_eState = DIED;
}

void GameModel::genFood()
{
    int foodRow, foodCol;
    srand(time(NULL));

    pthread_mutex_trylock(&boxMutex);
    do
    {
        foodRow = rand() % WIDTH;
        foodCol = rand() % HEIGHT;
    } 
    while (box[foodRow][foodCol] != EMPTY);
    box[foodRow][foodCol] = FOOD;
    pthread_mutex_unlock(&boxMutex);
}

int GameModel::getCurrentScore()
{
    return this->m_iTotalScore;
}

GameState GameModel::getGameState()
{
    return this->m_eState;
}

void GameModel::dispatchKeyEvent(SnakeDir key)
{
    if(this->m_eState == PLAYING)
    {
        Snake::getInstance()->onKeyPressed(key);
    }
    else if(this->m_eState == DIED)
    {
        if(key == DIR_UP || key == DIR_DOWN)
        {
            this->changeCursorPos(key);
        }
    }
}

void GameModel::dispatchKeyEvent()
{
    GameState state = this->getNextState();

    if(this->m_eState == DIED && state == PAUSED)
    {
        resetGame();
    }

    this->m_eState = state;
}

GameState GameModel::getNextState()
{
    GameState state;
    int iSize = sizeof(m_stStateMap) / sizeof(GAME_STATE_TABLE);

    for (int i = 0; i < iSize; i++)
    {
        if(m_stStateMap[i].curState == this->m_eState)
        {
            if(m_stStateMap[i].select != 0)
            {
                if(m_stStateMap[i].select == this->m_iCursorPos)
                {
                    state = m_stStateMap[i].nextState;
                    break;
                }
            }
            else
            {
                state = m_stStateMap[i].nextState;
                break;
            }
        }
    }

    return state;
}

int GameModel::getCursorPos()
{
    pthread_mutex_trylock(&selMutex);
    return this->m_iCursorPos;
    pthread_mutex_unlock(&selMutex);
}

void GameModel::changeCursorPos(SnakeDir key)
{
    pthread_mutex_trylock(&selMutex);
    if(key == DIR_UP)
    {
        this->m_iCursorPos -= 1;
        if(this->m_iCursorPos <= 1)
        {
            this->m_iCursorPos = 1;
        }
    }
    else if(key == DIR_DOWN)
    {
        int maxOpt;
        int iSize = sizeof(m_stStateMap) / sizeof(GAME_STATE_TABLE);

        for (int i = 0; i < iSize; i++)
        {
            if(m_stStateMap[i].curState == m_eState)
            {
                maxOpt = m_stStateMap[i].optNum;
                break;
            }
        }

        this->m_iCursorPos += 1;
        if(this->m_iCursorPos >= maxOpt)
        {
            this->m_iCursorPos = maxOpt;
        }
    }
    pthread_mutex_unlock(&selMutex);
}

void GameModel::resetGame()
{
    this->m_iTotalScore = 0;
    this->m_iCursorPos = 1;

    init();
}