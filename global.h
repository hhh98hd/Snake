
#ifndef GLOBAL_H
#define GLOBAL_H

#define WIDTH 50
#define HEIGHT 26

#define EMPTY   ' '
#define WALL    'X'
#define BODY    'o'
#define HEAD    'O'
#define FOOD    '*'

#define MOVE_INTERVAL 200
#define FOOD_SCORE 10

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