#include <bits/stdc++.h>
#include <pthread.h>

#include "KeyHandler.h"
#include "Snake.h"

using namespace std;

void onForwardPressed();
void onBackwardPressed();
void onLeftPressed();
void onRightPressed();

pthread_t keyThread;

void* runKeyHandler(void* arg)
{
    KeyHandler::getInstance()->addHandler('w', onForwardPressed);
    KeyHandler::getInstance()->addHandler('a', onLeftPressed);
    KeyHandler::getInstance()->addHandler('s', onBackwardPressed);
    KeyHandler::getInstance()->addHandler('d', onRightPressed);

    KeyHandler::getInstance()->run();
}

int main()
{      
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&keyThread, &attr, &runKeyHandler, NULL);
    pthread_join(keyThread, NULL);

    cout << "Exiting..." << endl;
    return 0;
}

void onForwardPressed()
{
    cout << "FORWARD" << endl;
}

void onBackwardPressed()
{
    cout << "BACKWARD" << endl;
}

void onLeftPressed()
{
    cout << "LEFT" << endl;
}

void onRightPressed()
{
    cout << "RIGHT" << endl;
}
