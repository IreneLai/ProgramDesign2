#include<string>
#include <stdio.h>
#include<iostream>
#include<Windows.h>
#include<MMSystem.h>
#include<sstream>
#include<fstream>
#include<queue>
#include<time.h>
#include <iomanip>
#include"Map.h"
#include"Player.h"
#include"Character.h"
class Game
{
public:
    Game(){}
    ~Game(){}
    int  Option();
    void Introduction();
    std::string MapName();
    int GameLoad();
    void PrintRole();
    void Sound(const std::string s );
    void BgMusic(const int triggerNum);
    void Trigger(const int triggerNum,std::queue<std::string> *q) const;
    std::string GetTrigger();
    void RoleSearchDisplay(const int trigger);
    Map map;
    Player player;
private:
    int trigger_=1;
    Player record_[10];//讀檔玩家紀錄，最多十筆
    int numChar_=0;
    Character roles_[20];
    int SearchID_(std::string name);
    void Role2Talk_(int searchID,std::string Name);
    void StoryLine_(int searchID,std::string Name,std::string str);


};
