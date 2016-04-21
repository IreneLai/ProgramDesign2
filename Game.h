#include<string>
#include <stdio.h>
#include<iostream>
#include<Windows.h>
#include<MMSystem.h>
#include<sstream>
#include<fstream>
#include<vector>
#include<time.h>
#include <iomanip>
#include<sstream>
#include"Map.h"
#include"Player.h"
#include"Character.h"
#ifndef GAME_H_
#define GAME_H_
class Game
{
public:
    Game() {}
    ~Game() {}
    int  Option();
    void Introduction();
    std::string MapName();
    int GameLoad();
    void PrintRole();
    void Sound(const std::string s );
    void BgMusic(const int triggerNum);
    std::string GetTrigger();
    void RoleSearchDisplay(const int trigger);
    void EndStory();
    Map map;
    Player player;
    char tmp[64];
    time_t t = time(0);
private:
    int trigger_=1;
    int storyChapter_[2]={0};
    Player record_[10];//讀檔玩家紀錄，最多十筆
    int numChar_=0;
    Character roles_[20];
    int SearchID_(std::string name);
    void Role2Talk_(int searchID,std::string Name);
    bool StoryLine_(int searchID,std::string Name,std::string str,int start);
    void PrintStoryLine_(int id,std::string Name);
    void AddRank_();
};

#endif // GAME_H_
