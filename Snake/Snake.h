#ifndef SNAKE_H
#define SNAKE_H

class Snake
{
private:
    int iHeadX;
    int iHeadY;
    int iLength = 2;
public:
    Snake(int x, int y);

    ~Snake();

    void onForwardPressed();

    void onLeftPressed();

    void onRightPressed();

    void onBackwardPressed();
};

#endif