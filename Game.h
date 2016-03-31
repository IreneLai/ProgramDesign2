#include<string>
#include <stdio.h>
#include<iostream>
#include<Windows.h>
#include<MMSystem.h>
#include<sstream>
#include<fstream>
#include<queue>
#include <iomanip>
#include"Map.h"
#include"Player.h"
class Game
{
public:
    Game(){}
    ~Game(){}
    int  Option();
    void Introduction();
    std::string MapName();
    void Sound(const std::string s );
    void BgMusic(const int triggerNum);
    void Trigger(const int triggerNum,std::queue<std::string> *q) const;
    std::string GetTrigger();
    Map map;
    Player player;
private:
    int trigger_=1;
    Player record_[10];//最多十筆
};
