#include <conio.h>
#include <iostream>

#include "KeyHandler.h"

using namespace std;

KeyHandler* KeyHandler::s_pInstace = nullptr;

KeyHandler::KeyHandler(){}

KeyHandler* KeyHandler::getInstance()
{
    if(s_pInstace == nullptr)
    {
        s_pInstace = new KeyHandler();
    }

    return s_pInstace;
}

KeyHandler::~KeyHandler()
{
    delete s_pInstace;
    s_pInstace = nullptr;
}

void KeyHandler::addHandler(const char key, const fp_key function)
{
    this->m_callbackMap[key] = function;
}

void KeyHandler::run()
{
    while (GameModel::getInstance()->getGameState() != QUIT)
    {
        char key = getch();
        map<char, fp_key>::iterator it = m_callbackMap.find(key);
        if(it != m_callbackMap.end())
        {
            // Invoke the handler
            (*it->second)();
        }
        else
        {
            // Key is not handled
        }
        
    }
}
