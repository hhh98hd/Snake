#ifndef GLOBAL_H
#define GLOBAL_H

#define WIDTH 50
#define HEIGHT 26

#define EMPTY   ' '
#define WALL    'X'
#define HEAD    'O'
#define BODY    'O'
#define FOOD    '*'

#define MOVE_INTERVAL 950

struct Position
{
    int x;
    int y;
};

enum SnakeDir
{
    DIR_NONE,    //idle
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
};

#endif