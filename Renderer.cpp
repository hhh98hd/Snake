#include <bits/stdc++.h>
#include <windows.h>

#include "Renderer.h"
#include "GameModel.h"
#include "global.h"

extern char box[HEIGHT + 2][WIDTH + 2];
extern pthread_mutex_t boxMutex;

using namespace std;

map<char, Color> m_colorMap = {
    {HEAD,    GREEN},
    {BODY,    GREEN},
    {WALL,    GRAY},
    {FOOD,    YELLOW},
    {EMPTY,   WHITE}
};

Renderer* Renderer::s_pInstance = nullptr;

Renderer::Renderer()
{
    /* disable the cursor blinking */
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = false; 
    SetConsoleCursorInfo(out, &cursorInfo);
}

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

void Renderer::drawFrame()
{
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

void Renderer::gameOver()
{
    m_bGameOver = true;
}

void Renderer::gameOverText()
{
    setColor(RED);
    COORD coord;
    coord.X = (int)(WIDTH / 2) - 8;
    coord.Y = (int)(HEIGHT / 2) - 2;
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
    cout << " @@@@   @    @   @@@@   @    @  @@@@@@" << endl;
    cout << "@    @  @@   @  @    @  @   @   @     " << endl;
    cout << "@       @ @  @  @    @  @  @    @     " << endl;
    cout << " @@@@   @  @ @  @@@@@@  @@@     @@@@@@" << endl;
    cout << "     @  @  @ @  @    @  @  @    @     " << endl;
    cout << "@    @  @   @@  @    @  @   @   @     " << endl;
    cout << " @@@@   @    @  @    @  @    @  @@@@@@" << endl;
}

void Renderer::run()
{
    while(m_bGameOver == false)
    {
        drawFrame();
        clearScreen();
    }

    /* game over */
    drawFrame();
    gameOverText();
}