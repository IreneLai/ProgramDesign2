#include<fstream>
#include<string>
#include<sstream>
#include<time.h>
#include<stdio.h>
#include<queue>
#include<Windows.h>
#include<iostream>
class Map
{
public:
    void SetColor(int f,int b);//¦rÅéÃC¦â
    void SetCursorPosition(const int x,const int y)const;
    void ClearScreen(const std::string &ch);
    void Position(const int x,const int y);
    void PrintMap();
    int Keyboard();
    int xPos=0,yPos=0;
    int mapNum=1;//1:square 2:church 3:Concert Hall 4:bar 5:maze
    bool GetMap();
private:
    constexpr static int mapRow_=16,mapCol_=32;
    int map_[mapRow_][mapCol_];
};
