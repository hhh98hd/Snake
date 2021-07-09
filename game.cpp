#include <bits/stdc++.h>
#include <pthread.h>
#include <windows.h>

#include "global.h"
#include "KeyHandler.h"
#include "Snake.h"
#include "Renderer.h"
#include "GameModel.h"

using namespace std;

void onForwardPressed();
void onBackwardPressed();
void onLeftPressed();
void onRightPressed();
void onSpacePressed();
void onQuitPressed();

void* runKeyHandler(void* arg);
void* runRenderer(void* arg);
void* runGame(void* arg);

pthread_t keyThread, uiThread, gameThread;
pthread_mutex_t boxMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t snakeMutex = PTHREAD_MUTEX_INITIALIZER;

char box[HEIGHT + 2][WIDTH + 2];

int main()
{      
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    GameModel::getInstance()->init();
    Snake::getInstance();
    Renderer::getInstance();

    pthread_create(&keyThread, &attr, &runKeyHandler, NULL);
    pthread_create(&uiThread, &attr, &runRenderer, NULL);
    pthread_create(&gameThread, &attr, &runGame, NULL);

    pthread_join(keyThread, NULL);
    pthread_join(uiThread, NULL);
    pthread_join(gameThread, NULL);

    cout << "Exiting..." << endl;
    return 0;
}

void onForwardPressed()
{
    GameState currentState = GameModel::getInstance()->getGameState();
    if(currentState == MENU)
    {

    }
    else if(currentState == PLAYING)
    {
        Snake::getInstance()->onKeyPressed(DIR_UP);
    }
}

void onBackwardPressed()
{
    GameState currentState = GameModel::getInstance()->getGameState();
    if(currentState == MENU)
    {
        
    }
    else if(currentState == PLAYING)
    {
        Snake::getInstance()->onKeyPressed(DIR_DOWN);
    }
}

void onLeftPressed()
{
    GameState currentState = GameModel::getInstance()->getGameState();
    if(currentState == MENU)
    {
        
    }
    else if(currentState == PLAYING)
    {
        Snake::getInstance()->onKeyPressed(DIR_LEFT);
    }
}

void onRightPressed()
{
    GameState currentState = GameModel::getInstance()->getGameState();
    if(currentState == MENU)
    {
        
    }
    else if(currentState == PLAYING)
    {
        Snake::getInstance()->onKeyPressed(DIR_RIGHT);
    }
}

void onSpacePressed()
{
}

void onQuitPressed()
{

}

void* runKeyHandler(void* arg)
{
    /* WASD movement */
    KeyHandler::getInstance()->addHandler('w', onForwardPressed);
    KeyHandler::getInstance()->addHandler('a', onLeftPressed);
    KeyHandler::getInstance()->addHandler('s', onBackwardPressed);
    KeyHandler::getInstance()->addHandler('d', onRightPressed);

    /* Arrow keys movement */
    KeyHandler::getInstance()->addHandler(72, onForwardPressed);
    KeyHandler::getInstance()->addHandler(75, onLeftPressed);
    KeyHandler::getInstance()->addHandler(80, onBackwardPressed);
    KeyHandler::getInstance()->addHandler(77, onRightPressed);

    /* Space key */
    KeyHandler::getInstance()->addHandler(' ', onSpacePressed);
    /* ESC key */
    KeyHandler::getInstance()->addHandler(27, onQuitPressed);

    KeyHandler::getInstance()->run();

    return nullptr;
}

void* runRenderer(void* arg)
{
    Renderer::getInstance()->run();
    return nullptr;

    return nullptr;
}

void* runGame(void* arg)
{
    Snake::getInstance()->run();
    
    return nullptr;
}