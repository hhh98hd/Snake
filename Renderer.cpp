#include <bits/stdc++.h>
#include <windows.h>

#include "Renderer.h"
#include "GameModel.h"
#include "global.h"

extern char box[HEIGHT + 2][WIDTH + 2];
extern pthread_mutex_t boxMutex;
extern pthread_mutex_t selMutex;

using namespace std;

map<char, Color> m_colorMap = {
    {HEAD,    BLUE},
    {BODY,    GREEN},
    {WALL,    GRAY},
    {FOOD,    YELLOW},
    {EMPTY,   WHITE}
};

Renderer* Renderer::s_pInstance = nullptr;

Renderer::Renderer(){}

Renderer* Renderer::getInstance()
{
    if(s_pInstance == nullptr)
    {
        s_pInstance = new Renderer();
    }

    return s_pInstance;
}

void Renderer::setColor(Color color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Renderer::displayScore()
{
    setColor(GRAY);
    int score = GameModel::getInstance()->getCurrentScore();
    cout << "Score: ";
    setColor(YELLOW);
    if(score == 0)
    {
        cout << "0000";
    }
    else if(score < 100)
    {
        cout << "00" << score;
    }
    else if(100 <= score && score < 1000)
    {
        cout << "0" << score;
    }
    else
    {
        cout << score;
    }
    cout << endl << endl;
}

void Renderer::drawGame()
{
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);         

    displayScore();

    pthread_mutex_trylock(&boxMutex);
    for(int i = 0; i <= HEIGHT + 1; i++)   
    {
        for(int j = 0; j <= WIDTH + 1; j++)
        {
            char c = box[i][j];
            setColor(m_colorMap[c]);
            cout << c << " ";
        }

        if(i < HEIGHT + 1)
        {
            cout << endl;
        }
    }
    pthread_mutex_unlock(&boxMutex);
}

void Renderer::clearScreen()
{
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Renderer::gameOverText()
{
    setColor(RED);
    COORD coord;
    coord.X = (int)(WIDTH / 2) - 8;
    coord.Y = (int)(HEIGHT / 2) - 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << " @@@    @@@   @   @  @@@@     @@@   @   @  @@@@  @@@" << endl;
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "@   @  @   @  @@ @@  @       @   @  @   @  @     @  @" << endl;
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "@      @@@@@  @ @ @  @@@@    @   @  @   @  @@@@  @@@" << endl;
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "@ @@@  @   @  @   @  @       @   @  @   @  @     @@" << endl;
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "@   @  @   @  @   @  @       @   @   @ @   @     @ @" << endl;
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << " @@@   @   @  @   @  @@@@     @@@     @    @@@@  @  @" << endl;
}

void Renderer::mainMenuText()
{   
    setColor(GREEN);
    COORD coord;
    coord.X = (int)(WIDTH / 2) - 4;
    coord.Y = (int)(HEIGHT / 2) - 5;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);                 
    cout << " @@@@     @    @     @@@@     @    @    @@@@@@";
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);    
    cout << "@    @    @@   @    @    @    @   @     @     ";
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);   
    cout << "@         @ @  @    @    @    @  @      @     ";
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);   
    cout << " @@@@     @  @ @    @@@@@@    @@@       @@@@@@";
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);   
    cout << "     @    @  @ @    @    @    @  @      @     ";
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);   
    cout << "@    @    @   @@    @    @    @   @     @     ";
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);   
    cout << " @@@@     @    @    @    @    @    @    @@@@@@";
}

void Renderer::drawMenu()
{
    COORD coord;

    mainMenuText();

    setColor(WHITE);
    cout << endl << endl;
    coord.X = (int)(WIDTH / 2) + 10;
    coord.Y = (int)(HEIGHT / 2) + 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    int cursorPos = GameModel::getInstance()->getCursorPos();
    if(cursorPos == 1)
    {
        setColor(GREEN);
        cout << ">  ";
        setColor(WHITE);
        cout << "1. PLAY";
        coord.Y += 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "   2. TUTORIAL";
        coord.Y += 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "   3. QUIT";
    }
    else if(cursorPos == 2)
    {
        setColor(WHITE);
        cout << "   1. PLAY";
        coord.Y += 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        setColor(GREEN);
        cout << ">  ";
        setColor(WHITE);
        cout << "2. TUTORIAL";
        coord.Y += 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "   3. QUIT";
    }
    else if(cursorPos == 3)
    {
        setColor(WHITE);
        cout << "   1. PLAY";
        coord.Y += 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "   2. TUTORIAL";
        coord.Y += 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        setColor(GREEN);
        cout << ">  ";
        setColor(WHITE);
        cout << "3. QUIT";

    }
}

void Renderer::drawGameOver()
{
    COORD coord;

    displayScore();
    gameOverText();

    setColor(WHITE);
    cout << endl << endl;
    coord.X = (int)(WIDTH / 2) + 8;
    coord.Y = (int)(HEIGHT / 2) + 5;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    int cursorPos = GameModel::getInstance()->getCursorPos();
    if(cursorPos == 1)
    {
        setColor(GREEN);
        cout << ">  ";
        setColor(WHITE);
        cout << "1. TRY AGAIN";
        coord.Y += 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "   2. QUIT";
    }
    else if(cursorPos == 2)
    {
        setColor(WHITE);
        cout << "   1. TRY AGAIN";
        coord.Y += 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        setColor(GREEN);
        cout << ">  ";
        setColor(WHITE);
        cout << "2. QUIT";
    }
}

void Renderer::run()
{
    GameState prevState = MENU;
    cout << endl << endl;
    for(int i = 0; i <= HEIGHT + 1; i++)   
    {
        for(int j = 0; j <= WIDTH + 1; j++)
        {
            char c = box[i][j];
            if(c == WALL)
            {
                setColor(WHITE);
                cout << c << " ";
            }
            else
            {
                cout << "  ";
            }
        }

        if(i < HEIGHT + 1)
        {
            cout << endl;
        }
    }
    
    while(true)
    {
        GameState currentState = GameModel::getInstance()->getGameState();
        if(currentState == MENU)
        {
            /* Main menu */
            drawMenu();
            prevState = currentState;
        }
        else if(currentState == PLAYING || currentState == PAUSED)
        {
            /* changed from MENU state to PLAYING/PAUSED state */
            if(prevState == MENU)
            {
                clearScreen();
            }
            /* Playing game */
            drawGame();
            clearScreen();
            prevState = currentState;
        }
        else if(currentState == DIED)
        {
            /* changed from PLAYING/PAUSED state to DIED state */
            if(prevState != currentState)
            {
                drawGame();
                clearScreen();
            }
            prevState = currentState;

            /* Game over */
            drawGameOver();
            clearScreen();
        }
        else if(currentState == QUIT)
        {
            system("cls");
            break;
        }
    }
}