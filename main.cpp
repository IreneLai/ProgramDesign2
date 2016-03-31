#include<time.h>
#include"Game.h"
using namespace std;
int main()
{
    Player player;
    Map map;
    Game game;
    //START_OptionMenu
    int option=game.Option();
    if(option==0)
    {
        map.SetColor(0,10);
        map.SetCursorPosition(10,5);
        cout<<"遊戲規則";
        map.SetColor(10,0);
        map.SetCursorPosition(10,7);
        cout<<"(1) 不要放過遊戲中的任何蛛絲馬跡";
        map.SetCursorPosition(10,8);
        cout<<"(2) 移動：方向鍵 ↑ ↓ ← → 控制";
        map.SetCursorPosition(10,9);
        cout<<"(3) 玩家狀態請按 [Enter]，內容包括金錢、花費時間";
        map.SetCursorPosition(10,10);
        cout<<"    可進行存檔、地圖更換、道具查看等等...";
        //Print name
        map.SetColor(11,0);
        map.SetCursorPosition(10,12);
        cout<<"請輸入姓名...>";
        cin>>game.player.name;
    }
    else if(option==1)
    {
        map.SetCursorPosition(10,5);
        cout<<"RECORD";
        map.SetCursorPosition(10,6);
        cout<<"Choose the record...>";
        int record=0;
        cin>>record;
    }
    else exit(1);
    game.GameLoad();
   // game.PrintRole();
    map.SetCursorPosition(15,15);
    system("pause");
    system("cls");
    map.SetColor(7,0);
    //Start clock
    clock();
    bool GameRun = true;
    int mapCount=1;
    map.Position(1,1);
    int Gpos=0;
    queue<string> q;
    map.SetCursorPosition(0,0);
    game.Introduction();
    char tmp[64];
    time_t t = time(0);
    map.SetCursorPosition(36,1);
    cout<<"開始時間 :";
    strftime( tmp, sizeof(tmp), "%Y/%m/%d %X %A",localtime(&t) );
    puts( tmp );
    map.SetCursorPosition(36,2);
    cout<<"[玩家] "<<game.player.name<<endl;
    map.SetCursorPosition(36,3);
    cout<<"[目標] "<<"找到勞爾夏尼子爵";
    map.SetCursorPosition(36,4);
    cout<<"[位置] "<<game.MapName();
    map.SetColor(12,0);
    game.map.GetMap();
    map.SetCursorPosition(0,0);
    game.map.PrintMap();
    game.BgMusic(game.map.mapNum);
    srand(time(NULL));
    while(GameRun)
    {
        int trigger=game.map.Keyboard();
        if(trigger>=4&&trigger<=6)
        {
            game.Role2Talk();
        }
        map.SetCursorPosition(0,15);
        system("pause>nul");

        GetAsyncKeyState(VK_RETURN);
        if(GetAsyncKeyState(VK_RETURN)!=0)
        {
            system("cls");
            int select=0;
            while(select!=4)
            {
                map.SetColor(13,0);
                switch(select)
                {
                case 1:

                    break;
                case 2:
                    map.SetCursorPosition(0,5);
                    cout<<"\t\t地圖選單"<<endl
                        <<"\t\t1: 廣場 "<<endl
                        <<"\t\t2: 東區白教堂"<<endl
                        <<"\t\t3: 維多利亞音樂廳"<<endl
                        <<"\t\t4: 酒吧"<<endl<<endl
                        <<"\t\t請選擇地圖...>";
                    cin>>game.map.mapNum;
                    game.map.GetMap();
                    game.BgMusic(game.map.mapNum);
                    break;
                case 3:
                    break;
                }
                if(select!=0)
                {
                    map.SetCursorPosition(15,19);
                    system("pause");
                    system("cls");
                }
                map.SetColor(6,0);
                map.SetCursorPosition(0,5);
                cout<<"\t\t"<<game.player.name<<" 目錄"<<endl<<endl;
                cout<<"\t\t※提示：遊戲當中長按 [空白鍵]能知道目前經過時間"<<endl<<endl;
                cout<<"\t\t[選項]"<<endl<<endl
                    <<"\t\t(1) 道具及情報箱 "<<endl
                    <<"\t\t(2) 地圖移轉"<<endl
                    <<"\t\t(3) 儲存檔案或離開遊戲"<<endl
                    <<"\t\t(4) 離開選單"<<endl<<endl
                    <<"\t\t輸入選擇項目...>";
                cin>>select;
                map.SetCursorPosition(15,19);
                system("pause");
                system("cls");
            }
            system("cls");
            map.SetColor(14,0);
            map.SetCursorPosition(36,1);
            cout<<"開始時間 :";
            strftime( tmp, sizeof(tmp), "%Y/%m/%d %X %A",localtime(&t) );
            puts( tmp );
            map.SetCursorPosition(36,2);
            cout<<"[玩家] "<<game.player.name<<endl;
            map.SetCursorPosition(36,3);
            cout<<"[目標] "<<"找到勞爾夏尼子爵";
            map.SetCursorPosition(36,4);
            cout<<"[位置] "<<game.MapName();
            map.SetCursorPosition(0,0);
            game.map.PrintMap();
        }

        if(GetAsyncKeyState(VK_SPACE)!=0)
        {
            while(GetAsyncKeyState(VK_SPACE)!=0)
            {
                map.SetCursorPosition(0,18);
                int minute=clock()/CLOCKS_PER_SEC/60;
                int second=clock()/CLOCKS_PER_SEC%60;
                std::cout<<"已經過 : "<<minute<<" 分 "<<second<<" 秒 "<<std::endl;
                Sleep(100);
            }
            map.SetCursorPosition(0,18);
            cout<<"                       ";
        }
    }
    cin.get();
    return 0;
}


