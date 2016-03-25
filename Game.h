#include<string>
#include<iostream>
#include<Windows.h>
#include<MMSystem.h>
#include<sstream>
#include<fstream>
#include<queue>
class Game
{
public:
    std::string GetGamePurpose(const int num)
    {
        std::string str;
        switch (num)
        {
        case 1:
            str="game1";
            break;
        case 2:
            str="game2";
            break;
        case 3:
            str="game3";
        }
        return str;
    }
    void Sound(const std::string s )
    {
        std::string tmp=s+".wav";
        PlaySound(TEXT(tmp.c_str()),NULL,SND_ASYNC|SND_LOOP);//music player'
    }
    void BgMusic(const int triggerNum)
    {
        switch(triggerNum)
        {
        case 1:
            Sound("Galaxy");
            break;
        case 2:
            Sound("Mahoutsukai");
            break;
        }
    }
    void Trigger(const int triggerNum,std::queue<std::string> *q) const
    {
        std::stringstream ss;
        ss<<triggerNum;
        std::string file="game"+ss.str()+".txt";
        std::fstream gFile;
        gFile.open(file,std::fstream::in);
        if(gFile)
        {
            std::string str;
            int count=3;
            while(getline(gFile,str))
            {
                q->push(str);
            }
        }
    }
    std::string GetTrigger()
    {
        std::stringstream ss;
        std::string s;
        ss<<trigger_;
        ss>>s;
        return s;
    }
private:
    int trigger_=1;
};
