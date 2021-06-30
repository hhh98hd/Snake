#include <bits/stdc++.h>
#include <pthread.h>

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

    Snake::getInstance();
    GameModel::getInstance()->init();

    pthread_create(&uiThread, &attr, &runRenderer, NULL);
    pthread_create(&keyThread, &attr, &runKeyHandler, NULL);
    pthread_create(&gameThread, &attr, &runGame, NULL);

    pthread_join(keyThread, NULL);
    pthread_join(uiThread, NULL);
    pthread_join(gameThread, NULL);

    cout << "Exiting..." << endl;
    return 0;
}

void onForwardPressed()
{
    Snake::getInstance()->onKeyPressed(DIR_UP);
}

void onBackwardPressed()
{
    Snake::getInstance()->onKeyPressed(DIR_DOWN);
}

void onLeftPressed()
{
}

void onRightPressed()
{
    Snake::getInstance()->onKeyPressed(DIR_RIGHT);
}

void* runKeyHandler(void* arg)
{
    // movement keys
    KeyHandler::getInstance()->addHandler('w', onForwardPressed);
    KeyHandler::getInstance()->addHandler('a', onLeftPressed);
    KeyHandler::getInstance()->addHandler('s', onBackwardPressed);
    KeyHandler::getInstance()->addHandler('d', onRightPressed);

    KeyHandler::getInstance()->run();
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


// #include <iostream>
// #include <unistd.h> // for sleep()

// int main()
// {
//     std::cout << '-' << std::flush;
//     for (;;) {
//         sleep(1);
//         std::cout << "\b\\" << std::flush;
//         sleep(1);
//         std::cout << "\b|" << std::flush;
//         sleep(1);
//         std::cout << "\b/" << std::flush;
//         sleep(1);
//         std::cout << "\b-" << std::flush;
//     }
// }