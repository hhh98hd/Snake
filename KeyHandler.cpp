#include "KeyHandler.h"
#include <bits/stdc++.h>

using namespace std;

KeyHandler* KeyHandler::s_pInstace = nullptr;

KeyHandler::KeyHandler()
{
    cout << "Constructed" << endl;
}

KeyHandler* KeyHandler::getInstance()
{
    if(s_pInstace == nullptr)
    {
        s_pInstace = new KeyHandler();
    }

    return s_pInstace;
}

void KeyHandler::init()
{
}

void KeyHandler::onKeyPressed(char key){}