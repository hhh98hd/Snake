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

    cout << "Thanks for playing ^^" << endl;
    return 0;
}

void onForwardPressed()
{
    GameModel::getInstance()->dispatchKeyEvent(DIR_UP);
}

void onBackwardPressed()
{
    GameModel::getInstance()->dispatchKeyEvent(DIR_DOWN);
}

void onLeftPressed()
{
    GameModel::getInstance()->dispatchKeyEvent(DIR_LEFT);
}

void onRightPressed()
{
    GameModel::getInstance()->dispatchKeyEvent(DIR_RIGHT);
}

void onSpacePressed()
{   
    GameModel::getInstance()->dispatchKeyEvent();
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

    KeyHandler::getInstance()->run();

    return nullptr;
}

void* runRenderer(void* arg)
{
    Renderer::getInstance()->run();

    return nullptr;
}

void* runGame(void* arg)
{
    Snake::getInstance()->run();
    
    return nullptr;
}