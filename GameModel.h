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
    GameState m_eState;

    void genFood();
    GameModel();
public:
    ~GameModel();
    void init();
    static GameModel* getInstance();
    void updateSnakePos(Position curPos, Position newPos, bool isHead = false);
    int getCurrentScore();
    void notifyGameOver();
    GameState getGameState();
};

#endif