#include <unordered_map>

#ifndef KEYHANDLER_H
#define KEYHANDLER_H

typedef void (*fp)(void);

class KeyHandler
{
private:
    static KeyHandler* s_pInstace;

    KeyHandler();
public:
    static KeyHandler* getInstance();

    void init();

    void onKeyPressed(char key);
};

#endif