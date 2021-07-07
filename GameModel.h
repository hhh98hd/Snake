#include <vector>
#include "global.h"

using namespace std;

#ifndef GAMEMODEL_H
#define GAMEMODEL_H

class GameModel
{
private:
    static GameModel* s_pInstance;
    void genFood();
    GameModel();
    int m_iTotalScore;
public:
    ~GameModel();
    void init();
    static GameModel* getInstance();
    void updateSnakePos(Position curPos, Position newPos, bool isHead = false);
    void notifyGameOver();
};

#endif