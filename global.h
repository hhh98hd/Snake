
#ifndef GLOBAL_H
#define GLOBAL_H

#define WIDTH 34
#define HEIGHT 26

#define EMPTY   ' '
#define WALL    'X'
#define BODY    'o'
#define HEAD    'O'
#define FOOD    '*'

#define MOVE_INTERVAL 250
#define FOOD_SCORE 10

#define MAX_GAMEOVER_OPT 1
#define MAX_MENU_OPT 2

typedef void (*fp_key)(void);

struct Position
{
    int x;
    int y;
};

enum SnakeDir
{
    DIR_NONE ,    // keep the current direction
    DIR_UP   ,
    DIR_DOWN ,
    DIR_LEFT ,
    DIR_RIGHT
};

enum Color
{
    BLACK,
    GRAY = 7,
    BLUE = 9,
    GREEN,
    CYAN,
    RED,
    PURPLE,
    YELLOW,
    WHITE
};

enum GameState
{
    MENU,
    PLAYING,
    DIED,
    QUIT
};

enum GameOpt
{
    TRY = 0,
    EXIT,
};

struct SNAKE_ACTION_TABLE
{
    SnakeDir cmd;
    SnakeDir currentDir;
    SnakeDir action;
};

#endif