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
    void displayScore();
public:
    ~Renderer();
    static Renderer* getInstance();
    void drawMenu();
    void drawGame();
    void drawGameOver();
    void run();
};

#endif
