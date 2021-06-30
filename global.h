
#ifndef GLOBAL_H
#define GLOBAL_H

#define WIDTH 50
#define HEIGHT 26

#define EMPTY   ' '
#define WALL    'X'
#define HEAD    'O'
#define BODY    'O'
#define FOOD    '*'

#define MOVE_INTERVAL 1500

typedef void (*fp_key)(void);

struct Position
{
    int x;
    int y;
};

enum SnakeDir
{
    DIR_NONE,    // keep the current direction
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
};

struct SNAKE_ACTION_TABLE
{
    SnakeDir cmd;
    SnakeDir currentDir;
    SnakeDir action;
};

#endif