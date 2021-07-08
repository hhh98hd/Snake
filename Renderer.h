#include "global.h"

#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
private:
    static Renderer* s_pInstance;
    Renderer(/* args */);
    bool m_bGameOver = false;
        
    void clearScreen();
    void gameOverText();
public:
    ~Renderer();
    static Renderer* getInstance();
    void drawFrame();
    void run();
    void gameOver();
};

#endif
