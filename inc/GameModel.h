#include <vector>
#include "global.h"

using namespace std;

#ifndef GAMEMODEL_H
#define GAMEMODEL_H

class GameModel
{
private:
    static GameModel* s_pInstance;
    int m_iTotalScore;
    int m_iCursorPos;
    GameState m_eState;

    GameModel();
    void genFood();
    GameState getNextState();
    void changeCursorPos(SnakeDir key);
    void resetGame();
public:
    ~GameModel();
    void init();
    static GameModel* getInstance();
    void updateSnakePos(Position curPos, Position newPos, bool isHead = false);
    int getCurrentScore();
    void notifyGameOver();
    GameState getGameState();
    void dispatchKeyEvent(SnakeDir key);
    void dispatchKeyEvent();
    int getCursorPos();
};

#endif