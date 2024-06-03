#include <map>

#include "Snake.h"
#include "global.h"

using namespace std;

#ifndef KEYHANDLER_H
#define KEYHANDLER_H

class KeyHandler 
{
private:
    static KeyHandler* s_pInstace;

    map<char, fp_key> m_callbackMap;
    KeyHandler();

public:
    static KeyHandler* getInstance();
    ~KeyHandler();
    void run();
    void addHandler(const char key, const fp_key function);
};

#endif