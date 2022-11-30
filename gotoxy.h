#include <iostream>
#include <windows.h>
using namespace std;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void transisi()
{
    for(int a=25;a>=0;a--)
    {
        for(int b=50;b>=0;b--)
        {
            gotoxy(b,a); cout<<" ";
        }
    }
}