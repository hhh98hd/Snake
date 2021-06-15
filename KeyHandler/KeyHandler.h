#include <map>
#include "../Snake/Snake.h"

using namespace std;

#ifndef KEYHANDLER_H
#define KEYHANDLER_H

typedef void (*fp)(void);

class KeyHandler 
{
private:
    static KeyHandler* s_pInstace;

    map<char, fp> m_callbackMap;
    
    KeyHandler();
public:
    static KeyHandler* getInstance();

    void run();

    void addHandler(const char key, const fp function);
};

#endif