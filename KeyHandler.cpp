#include <conio.h>
#include <thread>
#include <iostream>

#include "KeyHandler.h"

using namespace std;

KeyHandler* KeyHandler::s_pInstace = NULL;

KeyHandler::KeyHandler(){}

KeyHandler* KeyHandler::getInstance()
{
    if(s_pInstace == NULL)
    {
        s_pInstace = new KeyHandler();
    }

    return s_pInstace;
}

KeyHandler::~KeyHandler()
{
    delete s_pInstace;
}

void KeyHandler::addHandler(const char key, const fp function)
{
    this->m_callbackMap[key] = function;
}

void KeyHandler::run()
{
    while (true)
    {
        char key = getch();
        map<char, fp>::iterator it = m_callbackMap.find(key);
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
