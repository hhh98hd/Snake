#include "global.h"

#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
private:
    static Renderer* s_pInstance;
    Renderer(/* args */);
    bool m_bGameOver = false;
public:
    ~Renderer();
    static Renderer* getInstance();
    void drawFrame();
    void clearScreen();
    void run();
    void gameOver();
};

#endif
