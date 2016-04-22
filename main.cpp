#include<time.h>
#include"Game.h"
#include"Record.h"
using namespace std;
int main()
{
    Player player;
    Map map;
    Game game;
    Record record;
    //START_OptionMenu
    int option=game.Option();
    if(option==0)
    {
        map.SetColor(0,10);
        map.SetCursorPosition(10,5);
        cout<<"遊戲規則";
        map.SetColor(10,0);
        map.SetCursorPosition(10,7);
        cout<<"(1) 不要放過遊戲中的任何蛛絲馬跡，尤其是地圖上的黃色符號";
        map.SetCursorPosition(10,8);
        cout<<"(2) 移動：方向鍵 ↑ ↓ ← → 控制";
        map.SetCursorPosition(10,9);
        cout<<"(3) 若金錢歸零，即輸了遊戲";
        map.SetCursorPosition(10,10);
        cout<<"(4) 提醒：同樣人物，對話不只一種；報紙(情報)可買多份";
        map.SetCursorPosition(10,11);
        cout<<"(5) 查看玩家狀態請按 [Enter]，內容包括金錢、花費時間";
        map.SetCursorPosition(10,12);
        cout<<"    可進行存檔、地圖更換、道具查看等等...";
        //Print name
        map.SetColor(11,0);
        map.SetCursorPosition(10,14);
        cout<<"請輸入姓名...>";
        cin>>game.player.name;
        getchar();
    }
    else if(option==1)
    {
        map.SetCursorPosition(0,1);
        record.Interface(game);
        getchar();
    }
    else exit(1);
    if(game.GameLoad()) cout<<"\n\t\t遊戲已下載完畢，即將開始..."<<endl;
    else exit(1);
    // game.PrintRole();
    cout<<"\t\t";
    system("pause");
    system("cls");
    map.SetColor(7,0);
    bool GameRun = true;
    map.Position(1,1);
    queue<string> q;
    map.SetCursorPosition(0,0);
    game.Introduction();
    map.SetCursorPosition(36,1);
    cout<<"開始時間 :";
    strftime( game.tmp, sizeof(game.tmp), "%Y/%m/%d %X %A",localtime(&game.t) );
    puts( game.tmp );
    map.SetCursorPosition(36,2);
    cout<<"[玩家] "<<game.player.name<<endl;
    map.SetCursorPosition(36,3);
    cout<<"[目標] "<<"1.蒐集情報、賺錢 2.找到勞爾夏尼子爵";
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
        game.RoleSearchDisplay(trigger);

        map.SetCursorPosition(0,15);
        system("pause>nul");

        GetAsyncKeyState(VK_RETURN);
        if(GetAsyncKeyState(VK_RETURN)!=0)
        {
            system("cls");
            int select=0,mapSelect=0;
            string makeSure;
            while(select!=4)
            {
                map.SetColor(13,0);
                map.SetCursorPosition(0,5);
                int tmp=0;
                switch(select)
                {
                case 1:

                    cout<<"\t\t";
                    map.SetColor(0,13);
                    cout<<"[玩家資料]"<<endl<<endl;
                    map.SetColor(13,0);
                    cout<<"\t\t玩家 : "<<game.player.name<<endl
                        <<"\t\t金錢 : "<<game.player.money<<" 英鎊"<<endl<<endl
                        <<"\t\t";
                    map.SetColor(0,13);
                    cout<<"[情報箱]"<<endl<<endl;
                    map.SetColor(13,0);
                    for(int i=0; i<game.player.buyNumNews; ++i)
                    {
                        for(int j=0; j<3; j++)
                        {
                            if(j==2)
                            {
                                for(int k=0; k<game.player.newspaper[i][j].length(); ++k)
                                {
                                    if(k%36==0)
                                    {
                                        cout<<endl;
                                        cout<<"\t\t";
                                    }
                                    cout<<game.player.newspaper[i][j][k];
                                }
                            }
                            else cout<<"\t\t"<<game.player.newspaper[i][j]<<endl;
                        }
                        cout<<endl<<"\t\t------------------------------------"<<endl;
                    }
                    break;
                case 2:

                    cout<<"\t\t[地圖選單]"<<endl<<endl
                        <<"\t\t1: 廣場 "<<endl
                        <<"\t\t2: 東區白教堂"<<endl
                        <<"\t\t3: 維多利亞音樂廳"<<endl
                        <<"\t\t4: 尼爾酒吧"<<endl<<endl
                        <<"\t\t請選擇地圖...>";
                    cin>>mapSelect;
                    if(mapSelect==3)
                    {
                        cout<<"\n\t\t進音樂廳要付50英鎊，你要購票嗎？[Y/N]...>";
                        cin>>makeSure;
                        if(makeSure=="Y")
                        {
                            game.player.money-=50;
                            if(game.player.money<=0)
                            {
                                cout<<"\t\t你的錢不足，遊戲結束"<<endl;
                                exit(1);
                            }
                            game.map.mapNum=3;
                        }
                        else mapSelect=game.map.mapNum;
                    }
                    else if(mapSelect>=1&&mapSelect<=4)game.map.mapNum=mapSelect;
                    game.map.GetMap();
                    game.BgMusic(game.map.mapNum);
                    tmp=1;

                    break;
                case 3:
                    cout<<"\t\t";
                    map.SetColor(0,13);
                    cout<<"[存檔資料]"<<endl<<endl;
                    map.SetColor(13,0);
                    cout<<"\t\t玩家名稱 : "<<game.player.name<<endl
                        <<"\t\t金錢 : "<<game.player.money<<endl
                        <<"\t\t目前花費時間 : "<<clock()/CLOCKS_PER_SEC/60<<" 分 "<<clock()/CLOCKS_PER_SEC%60<<" 秒 "<<endl<<endl
                        <<"\t\t請問要儲存檔案嗎[Y/N]...>";
                    string ans;
                    cin>>ans;
                    if(ans=="Y")
                    {
                        if(record.Save(&game))
                        {
                            cout<<"\t\t儲存成功，請問要繼續遊戲嗎?[Y/N]...>";
                            cin>>ans;
                            if(ans=="N") exit(1);
                        }
                    }
                    break;
                }
                if(select!=0)
                {
                    cout<<"\n\t\t";
                    system("pause");
                    system("cls");
                }
                if(tmp) {break;}
                map.SetCursorPosition(0,5);
                cout<<"\t\t ";
                map.SetColor(0,6);
                cout<<"目錄"<<endl<<endl;
                map.SetColor(6,0);
                cout<<"\t\t※提示：遊戲當中長按 [空白鍵]能知道目前經過時間"<<endl<<endl;
                cout<<"\t\t[選項]"<<endl<<endl
                    <<"\t\t(1) 玩家資料箱 "<<endl
                    <<"\t\t(2) 地圖移轉"<<endl
                    <<"\t\t(3) 儲存檔案或離開遊戲"<<endl
                    <<"\t\t(4) 回到遊戲"<<endl<<endl
                    <<"\t\t輸入選擇項目...>";
                cin>>select;
                getchar();
                map.SetCursorPosition(15,19);
                system("pause");
                system("cls");
            }
            system("cls");
            map.SetColor(14,0);
            map.SetCursorPosition(36,1);
            cout<<"開始時間 :";
            strftime( game.tmp, sizeof(game.tmp), "%Y/%m/%d %X %A",localtime(&game.t) );
            puts( game.tmp );
            map.SetCursorPosition(36,2);
            cout<<"[玩家] "<<game.player.name<<endl;
            map.SetCursorPosition(36,3);
            cout<<"[目標] "<<"1.蒐集情報、賺錢 2.找到勞爾夏尼子爵";
            map.SetCursorPosition(36,4);
            cout<<"[位置] "<<game.MapName();
            map.SetCursorPosition(0,0);
            if(game.player.storyline[10]) game.map.map_[2][12]=0;
            game.map.PrintMap();
        }

        if(GetAsyncKeyState(VK_SPACE)!=0)
        {
            while(GetAsyncKeyState(VK_SPACE)!=0)
            {
                map.SetCursorPosition(0,18);
                int hour=(clock()+game.player.time)/CLOCKS_PER_SEC/3600;
                int minute=(clock()+game.player.time)/CLOCKS_PER_SEC/60;
                int second=(clock()+game.player.time)/CLOCKS_PER_SEC%60;
                map.SetCursorPosition(3,18);
                std::cout<<"已經過 : "<<hour<<" 時 "<<minute<<" 分 "<<second<<" 秒 "<<std::endl;
                Sleep(100);
            }
            map.SetCursorPosition(3,18);
            cout<<"                                           ";
        }
    }
    cin.get();
    return 0;
}


