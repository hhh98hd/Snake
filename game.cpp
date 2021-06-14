#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

#include "KeyHandler.h"
#include "KeyHandler.cpp"

#include "Snake.h"
#include "Snake.cpp"

using namespace std;

void Snake::onForwardPressed()
{
    cout << "W" << endl;
}

int main()
{    
    Snake snake(0, 0);

    while (true)
    {
        char c = getch();
        cout << c << " is pressed" << endl;
    }
}