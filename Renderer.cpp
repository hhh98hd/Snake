#include <bits/stdc++.h>

#include "Renderer.h"
#include "global.h"

extern char box[HEIGHT + 2][WIDTH + 2];
extern pthread_mutex_t boxMutex;

using namespace std;

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

void Renderer::drawFrame()
{
    pthread_mutex_lock(&boxMutex);
    for(int i = 0; i <= HEIGHT + 1; i++)   
    {
        for(int j = 0; j <= WIDTH + 1; j++)
        {
            cout << box[i][j] << " ";
        }
        cout << endl;
    }
    pthread_mutex_unlock(&boxMutex);
}

void Renderer::clearScreen()
{
    system("cls");
}

void Renderer::run()
{
    while(true)
    {
        drawFrame();
        _sleep(MOVE_INTERVAL);
        clearScreen();
    }
}