#include <conio.h>
#include <thread>
#include <iostream>

#include "KeyHandler.h"
#include "../Snake/Snake.h"

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

void KeyHandler::addHandler(const char key, const fp function)
{
    this->m_callbackMap[key] = function;
}

void KeyHandler::run()
{
    while (true)
    {
        char c = getch();
        map<char, fp>::iterator it = m_callbackMap.find(c);
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
