
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
    PRE_PLAY,
    PLAYING,
    DIED,
    QUIT
};

struct SNAKE_ACTION_TABLE
{
    SnakeDir cmd;
    SnakeDir currentDir;
    SnakeDir action;
};

struct GAME_STATE_TABLE
{
    GameState curState;
    int select;
    GameState nextState;
    int optNum;
};

#endif