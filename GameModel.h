#include <vector>
#include "global.h"

using namespace std;

#ifndef GAMEMODEL_H
#define GAMEMODEL_H

class GameModel
{
private:
    static GameModel* s_pInstance;
    Position genFood();
    GameModel();
public:
    ~GameModel();
    void init();
    static GameModel* getInstance();
    void updateSnakePos(Position curPos, Position newPos);
};

#endif