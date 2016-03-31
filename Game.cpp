#include"Game.h"
using namespace std;
int Game::Option()
{
    map.SetCursorPosition(10,4);
    cout<<"Option"<<endl;
    int c=0;
    int option=0;
    string str[3]= {"START NEW GAME","RECORD","EXIT"};
    do
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
            map.SetCursorPosition(10,6+i);
            if(i==c)
            {
                option=c;
                map.SetColor(0,4);
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
    while(GetAsyncKeyState(VK_RETURN)==0);
    system("cls");
    map.SetColor(7,0);
    return option;
}
void  Game::Introduction()
{
    map.SetCursorPosition(10,5);
    cout<<"您好, "<<player.name<<".";
    map.SetCursorPosition(10,6);
    cout<<"歡迎來到17世紀的倫敦...";
    map.SetCursorPosition(10,7);
    cout<<"濃霧瀰漫的市中心廣場，充斥著詭譎的氣氛，到底發生什麼事了?";
    map.SetCursorPosition(10,8);
    cout<<"我有種不祥的預兆.....";
    map.SetCursorPosition(10,9);
    cout<<"麻煩協助我調查《勞爾夏尼的失蹤案件》";
    map.SetCursorPosition(10,10);
    cout<<"廣場聽說有許多情報，幫我打聽，由衷感謝您的協助。";
    map.SetCursorPosition(10,12);
    cout<<"                  Best,Lestrade. 12/7 Wes"<<endl<<endl;
    map.SetCursorPosition(10,15);
    system("pause");
    system("cls");
    map.SetColor(14,0);
    /*
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
    map.SetCursorPosition(0,0);*/
}
std::string Game::MapName()
{
    std::string str;
    switch (map.mapNum)
    {
    case 1:
        str="廣場";
        break;
    case 2:
        str="東區白教堂";
        break;
    case 3:
        str="維多利亞音樂廳";
        break;
    case 4:
        str="酒吧";
        break;
    case 5:
        str="迷宮";
    }
    return str;
}
void Game::Sound(const std::string s )
{
    std::string tmp=s+".wav";
    PlaySound(TEXT(tmp.c_str()),NULL,SND_ASYNC|SND_LOOP);//music player'
}
void Game::BgMusic(const int triggerNum)
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
void Game::Trigger(const int triggerNum,std::queue<std::string> *q) const
{
    std::stringstream ss;
    ss<<triggerNum;
    std::string file="game"+ss.str()+".txt";
    std::fstream gFile;
    gFile.open(file,std::fstream::in);
    if(gFile)
    {
        std::string str;
        while(getline(gFile,str))
        {
            q->push(str);
        }
    }
}
std::string Game::GetTrigger()
{
    std::stringstream ss;
    std::string s;
    ss<<trigger_;
    ss>>s;
    return s;
}

