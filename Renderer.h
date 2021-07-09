#include "global.h"

#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
private:
    static Renderer* s_pInstance;
    Renderer(/* args */);
        
    void clearScreen();
    void gameOverText();
    void mainMenuText();
    void setColor(Color color);
public:
    ~Renderer();
    static Renderer* getInstance();
    void drawGame();
    void drawMenu();
    void run();
};

#endif
