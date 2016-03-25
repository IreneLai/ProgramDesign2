#include<iostream>
#include<Windows.h>
#include<MMSystem.h>
#include<string>
#include <sstream>
#include <stdio.h>
#include<time.h>
#include"Player.h"
#include"Map.h"
#include"Game.h"
using namespace std;
//function prototypes
void ClearScreen(const string &ch);
//define menu system enum
enum MenuSystem
{
    SHOWMENU,MOVECURSOR,EXITPROGRAM //0,1,2
};
void Start(Map &map,const Player &player,Game &game,const int mapCount)
{
     map.SetColor(14,0);
    time_t t = time(0);
    map.SetCursorPosition(41,3);
    cout<<"﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏";
    map.SetCursorPosition(40,4);
    cout<<"│";
    map.SetCursorPosition(40,5);
    cout<<"│";
    map.SetCursorPosition(41,6);
    cout<<"﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋﹋";
    map.SetCursorPosition(66,4);
    cout<<"│";
    map.SetCursorPosition(66,5);
    cout<<"│";
    map.SetCursorPosition(0,0);
    char tmp[64];
    map.SetCursorPosition(36,0);
    cout<<"開始時間 :";
    strftime( tmp, sizeof(tmp), "%Y/%m/%d %X %A",localtime(&t) );
    puts( tmp );
    map.SetCursorPosition(36,1);
    cout<<"[玩家] "<<player.name<<endl;
    map.SetCursorPosition(36,2);
    cout<<"[目標]"<<" "<<game.GetGamePurpose(mapCount)<<endl;
    map.SetColor(12,0);
}
int main()
{
    /*SetCursorPosition(20,3);
    cout<< "[20,3]";*/
    //ClearScreen("#");

    Player player;
    Map map;
    Game game;
    cout<<"Choose"<<endl;
    int c=0,t=1;
    string str[3]= {"START NEW GAME","RECORD","EXIT"};

    while(GetAsyncKeyState(VK_RETURN)==0)
    {
        if(GetAsyncKeyState(VK_UP)!=0)
        {
            if(c==0)c=2;
            else c--;

        }
        if(GetAsyncKeyState(VK_DOWN)!=0)
        {
            if(c==2)c=0;
            else c++;
        }
        for(int i=0; i<3; ++i)
        {
            map.SetCursorPosition(5,13+i*2);
            if(i==c)
            {
                map.SetColor(12,5);
                cout<<str[i];
                map.SetColor(0,0);

            }
            else
            {
                map.SetColor(7,0);
                cout<<str[i];
                map.SetColor(0,0);
            }

        }
        system("pause>nul");
    }
    system("cls");
    map.SetColor(12,0);
     cout<<"Print your name...>";
    cin>>player.name;
    system("cls");



    clock();
    bool GameRun = true;
    map.mapNum=0;
    int mapCount=1;
    int getMap = map.GetMap(map.mapNum);
    map.Position(1,1);
    int Mpos=0,Gpos=0;
    queue<string> q;
    int line=4;
    Start(map,player,game,mapCount);
    map.SetCursorPosition(0,0);
    map.PrintMap();
    while(GameRun&&getMap)
    {
        if(map.Keyboard()>0) Mpos=map.Keyboard(); //觸發關卡
        if(Mpos==6 && map.GetMap(mapCount))  //換地圖
        {
            map.mapNum=Mpos;
            map.Position(map.xPos,map.yPos);
            Gpos=1;
            Mpos=-1;
            map.SetCursorPosition(0,0);
            map.PrintMap();
        }

        if(Gpos)
        {
            cout<<endl;
            game.Trigger(mapCount,&q);
            game.BgMusic(mapCount);
            mapCount++;
            Gpos=0;

        }
        if(!q.empty())
        {
            if(line==4)
            {
                map.SetCursorPosition(42,5);
                cout<<"                       ";
            }

            map.SetCursorPosition(42,line);
            cout<<q.front();

            while(GetAsyncKeyState(VK_SHIFT)==0) {Sleep(1500);}
            if(line==5)
            {
                map.SetCursorPosition(42,4);
                cout<<"                       ";
            }

            line++;
            if(line==6)line=4;
            if(q.front()==q.back())
            {
                system("cls");
            }
            q.pop();
            Start(map,player,game,mapCount);
            map.SetCursorPosition(0,0);
            map.PrintMap();
        }
        else
        {
            map.SetCursorPosition(0,15);
            system("pause>nul");
        }
        if(GetAsyncKeyState(VK_SPACE)!=0)
        {
            while(GetAsyncKeyState(VK_SPACE)!=0)
            {
                map.SetCursorPosition(42,4);
                int minute=clock()/CLOCKS_PER_SEC/60;
                int second=clock()/CLOCKS_PER_SEC%60;
                std::cout<<"已經過:"<<minute<<"分"<<second<<"秒"<<std::endl;
                Sleep(100);
            }
            system("cls");
            Start(map,player,game,mapCount);
            map.SetCursorPosition(0,0);
            map.PrintMap();
        }
    }
    cin.get();
    return 0;
}


