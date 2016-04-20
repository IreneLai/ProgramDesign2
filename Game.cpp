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
    cout<<"                  Best,雷斯垂德. 12/7 星期三"<<endl<<endl;
    map.SetCursorPosition(10,15);
    system("pause");
    system("cls");
    map.SetColor(14,0);
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
        str="尼爾酒吧";
        break;
    case 5:
        str="迷宮";
    }
    return str;
}
int Game::GameLoad()
{
    fstream charfp;
    charfp.open("Character.txt",fstream::in);
    if(charfp)
    {
        while(getline(charfp,roles_[numChar_].name))
        {
            fstream cfp;
            string tmp(roles_[numChar_].name);
            tmp+=".txt";
            cfp.open(tmp.c_str(),fstream::in);
            if(cfp)
            {
                string str;
                while(getline(cfp,str))
                {
                    roles_[numChar_].word[roles_[numChar_].numWord]=str;
                    roles_[numChar_].numWord++;
                    //cout<<roles_[numChar_].numWord<<" * "<<roles_[numChar_].word[roles_[numChar_].numWord-1]<<endl;
                }
                cfp.close();
            }
            numChar_++;
        }
        charfp.close();
        fstream newsf;
        newsf.open("News.txt",fstream::in);
        if(newsf)
        {
            int count=0;
            string strtmp;
            while(getline(newsf,strtmp))
            {
                player.newspaper[count/3][count%3]=strtmp;
                count++;
            }
            newsf.close();
        }
        else return 0;
        return 1;
    }
    return 0;
}
void Game::PrintRole()
{
    for(int i=0; i<numChar_; ++i)
    {
        cout<<roles_[i].name<<endl;
        for(int j=0; j<roles_[i].numWord; ++j)
        {
            cout<<roles_[i].word[j]<<endl;
        }
    }
}
void Game::PrintStoryLine_(int id,std::string Name)
{
    cout<<"\t\t"<<Name<<endl;
    int length=player.story[id].length();
    for(int i=0; i<length; ++i)
    {
        if(i%36==0)
        {
            cout<<endl;
            cout<<"\t\t";
        }
        cout<<player.story[id][i];
    }

}
bool Game::StoryLine_(int searchID,std::string Name,std::string str,int start)//劇情
{
    fstream fp;
    fp.open("Storyline.txt",fstream::in);
    if(fp)
    {
        string strtmp;
        int count=0;
        while(getline(fp,strtmp))
        {
            player.story[count]=strtmp;
            count++;
        }
        fp.close();
        if(roles_[searchID].name=="Neil"&&storyChapter_[0]==0)
        {
            system("cls");
            map.SetCursorPosition(0,5);
            if(player.storyline[2]!=1)
            {
                player.storyline[0]=1;
                PrintStoryLine_(0,Name);
            }
            else
            {
                player.storyline[2]=0;
                player.storyline[3]=1;
                PrintStoryLine_(3,Name);
            }
        }
        else if(roles_[searchID].name=="Gypsy"&&player.storyline[0])
        {
            map.SetCursorPosition(35,start+3);
            cout<<"輸入...>";
            cin>>str;
            getchar();
            if(str=="Help")
            {
                system("cls");
                map.SetCursorPosition(0,5);
                player.storyline[0]=0;
                player.storyline[1]=1;
                PrintStoryLine_(1,Name);
            }
            else return false;
        }
        else if(roles_[searchID].name=="Sherlock"&&player.storyline[1])
        {
            map.SetCursorPosition(35,start+3);
            cout<<"輸入...>";
            cin>>str;
            getchar();
            if(str=="Revolver")
            {
                system("cls");
                map.SetCursorPosition(0,5);
                player.storyline[1]=0;
                player.storyline[2]=1;
                PrintStoryLine_(2,Name);
            }
            else return false;
        }
        else if(roles_[searchID].name=="Lestrade"&&player.storyline[3])
        {
            player.storyline[3]=0;
            player.storyline[4]=1;
            system("cls");
            map.SetCursorPosition(0,5);
            PrintStoryLine_(4,Name);
            player.money+=200;
            storyChapter_[0]=1;
        }
        else if(roles_[searchID].name=="Orphan"&&storyChapter_[1]==0)
        {
            player.storyline[4]=0;
            player.storyline[5]=1;
            system("cls");
            map.SetCursorPosition(0,5);
            PrintStoryLine_(5,Name);
            player.money-=250;

        }
        else if(roles_[searchID].name=="Persia")
        {
            if(player.storyline[5])
            {
                map.SetCursorPosition(35,start+3);
                cout<<"輸入...>";
                cin>>str;
                getchar();
                if(str=="Erick")
                {
                    player.storyline[5]=0;
                    player.storyline[6]=1;
                    system("cls");
                    map.SetCursorPosition(0,5);
                    PrintStoryLine_(6,Name);
                }
                else return false;
            }
            else if(player.storyline[7])
            {
                player.storyline[7]=0;
                player.storyline[8]=1;
                system("cls");
                map.SetCursorPosition(0,5);
                PrintStoryLine_(8,Name);

            }
            else return false;
        }
        else if(roles_[searchID].name=="Christine")
        {

            if(player.storyline[6])
            {
                map.SetCursorPosition(35,start+3);
                cout<<"輸入...>";
                cin>>str;
                getchar();
                if(str=="MusicAngel")
                {
                    player.storyline[6]=0;
                    player.storyline[7]=1;
                    system("cls");
                    map.SetCursorPosition(0,5);
                    PrintStoryLine_(7,Name);
                }
                else return false;
            }
            else if(player.storyline[9])
            {
                player.storyline[9]=0;
                player.storyline[10]=1;
                storyChapter_[1]=1;
                system("cls");
                map.SetCursorPosition(0,5);
                PrintStoryLine_(10,Name);
                map.map_[2][12]=0;
            }
            else return false;
        }
        else if(roles_[searchID].name=="CleaningStaff"&&trigger_==53)//&&player.storyline[8]
        {
            player.storyline[8]=0;
            player.storyline[9]=1;
            system("cls");
            map.SetCursorPosition(0,5);
            PrintStoryLine_(9,Name);
        }
        else if(roles_[searchID].name=="Drink")
        {
            system("cls");
            map.SetColor(7,0);
            cout<<"來，我們來玩遊戲吧！看看誰能賺到錢！！！"<<endl<<endl;
            int tmp=rand()%3;
            map.SetColor(6,0);
            map.SetColor(13,0);
            switch(tmp)
            {
            case 0:
                if(player.GuessDigits())
                {
                    cout<<"你贏了 40 元"<<endl;
                    player.money+=40;
                }
                else
                {
                    cout<<"你輸了 20 元"<<endl;
                    player.money-=20;
                }
                break;
            case 1:
                if(player.PaperScissorRock())
                {
                    cout<<"你贏了 20 元"<<endl;
                    player.money+=20;
                }
                else
                {
                    cout<<"你輸了 10 元"<<endl;
                    player.money-=10;
                }
                break;
            case 2:
                if(player.NumGuess())
                {
                    cout<<"你贏了 30 元"<<endl;
                    player.money+=30;
                }
                else
                {
                    cout<<"你輸了 15 元"<<endl;
                    player.money-=15;
                }
                break;
            }
            map.SetColor(7,0);
            cout<<endl<<"歡迎再來賭一把啊！"<<endl;
        }
        else if(roles_[searchID].name=="EndStory"&&trigger_==14&&player.storyline[10])
        {
            system("cls");
            EndStory();
        }
        else return false;
        cout<<endl<<endl<<"\t\t\t\t\t";
        system("pause");
        system("cls");
        map.SetColor(14,0);
        map.SetCursorPosition(36,1);
        cout<<"開始時間 :";
        strftime( tmp, sizeof(tmp), "%Y/%m/%d %X %A",localtime(&t) );
        puts( tmp );
        map.SetCursorPosition(36,2);
        cout<<"[玩家] "<<player.name<<endl;
        map.SetCursorPosition(36,3);
        cout<<"[目標] "<<"1.賺錢、蒐集情報 2.找到勞爾夏尼子爵";
        map.SetCursorPosition(36,4);
        cout<<"[位置] "<<MapName();
        map.SetCursorPosition(0,0);
        map.PrintMap();
        return true;
    }
    return false;
}
void Game::Role2Talk_(int searchID,std::string Name)
{
    if(roles_[searchID].numWord!=0)
    {
        int start=9;
        int counttmp=start;
        int tmpnum=rand()%roles_[searchID].numWord;
        map.SetCursorPosition(35,start-2);
        cout<<Name;
        map.SetCursorPosition(35,start);
        if(player.storyline[2]&&roles_[searchID].name=="Neil")
        {
            cout<<"任務達成了？"<<endl;
        }
        else if(player.storyline[7]&&roles_[searchID].name=="Persia")
        {
            cout<<"克莉絲汀叫你問我艾瑞克的事？"<<endl;
        }
        else
        {
            for(int i=0; i<roles_[searchID].word[tmpnum].length(); ++i)
            {
                cout<<roles_[searchID].word[tmpnum][i];
                if(i%33==0)
                {
                    start++;
                    map.SetCursorPosition(35,start);
                }
            }
        }
        map.SetCursorPosition(35,start+2);
        cout<<"※ 是否要對話或答應他？[Y/Enter(N)]...>";
        char answer='\0';
        answer=getchar();
        string str,ans;
        if(answer=='Y')
        {
            if(roles_[searchID].name=="Newspaper")
            {

                if(player.buyNumNews<5)
                {
                    map.SetCursorPosition(35,start+5);
                    cout<<Name<<":感謝購買，請至玩家資料箱查看";
                    player.buyNumNews++;
                    player.money-=10;
                }
                else
                {
                    map.SetCursorPosition(35,start+5);
                    cout<<Name<<":報紙已售完...";
                }
                map.SetCursorPosition(35,start+6);
                system("pause");

            }
            else if(!StoryLine_(searchID,Name,str,start))
            {
                map.SetCursorPosition(35,start+5);
                cout<<Name<<":好像沒什麼要說的吧？";
                map.SetCursorPosition(35,start+6);
                system("pause");
            }
        }
        map.SetCursorPosition(35,counttmp-2);
        cout<<"                              ";
        for(int i=0; i<roles_[searchID].word[tmpnum].length(); ++i)
        {
            cout<<" ";
            if(i%33==0)
            {
                counttmp++;
                cout<<"   ";
                map.SetCursorPosition(35, counttmp);
            }
        }
        for(int i=2; i<=6; ++i)
        {
            map.SetCursorPosition(35,counttmp+i);
            cout<<"                                             ";
        }
    }
}
enum Location {NUL,SQUARE,CHURCH,CONCERTHALL,BAR,MAZE};
void Game::RoleSearchDisplay(const int trigger)
{
    trigger_=trigger;
    string roleName;
    string Name;
    switch(map.mapNum)
    {
    case SQUARE:
        if(trigger==4)
        {
            roleName="Vendor";
            Name="蔬果攤販";
        }
        else if(trigger==5)
        {
            roleName="Sherlock";
            Name="夏洛克福爾摩斯";
        }
        else if(trigger==6)
        {
            roleName="Newspaper";
            Name="賣報小童";
        }
        break;
    case CHURCH:
        if(trigger==4)
        {
            roleName="Orphan";
            Name="孤兒";
        }
        else if(trigger==5)
        {
            roleName="Gypsy";
            Name="吉普賽人";
        }
        else if(trigger==6)
        {
            roleName="Persia";
            Name="波斯人";
        }
        else if(trigger==21)
        {
            roleName="Lestrade";
            Name="雷斯垂德警探";
        }
        break;
    case CONCERTHALL:
        if(trigger>=49&&trigger<=54)
        {
            roleName="CleaningStaff";
            Name="包廂清潔工";
        }
        else if(trigger==5)
        {
            roleName="Christine";
            Name="克莉絲汀";
        }
        else if(trigger==14)
        {
            roleName="EndStory";
            Name="音樂廳地下室";
        }
        break;
    case BAR:
        if(trigger==5)
        {
            roleName="Neil";
            Name="尼爾公爵";
        }
        else if(trigger==6)
        {
            roleName="Drink";
            Name="酒客";
        }
        break;
    case MAZE:
        break;
    }
    int searchID=SearchID_(roleName);
    if(searchID>=0) Role2Talk_(searchID,Name);
}
int Game::SearchID_(std::string name)
{
    for(int i=0; i<numChar_; ++i)
    {
        if(roles_[i].name==name) return i;
    }
    return -1;
}
void Game::Sound(const std::string s )
{
    std::string tmp=s+".wav";
    PlaySound(TEXT(tmp.c_str()),NULL,SND_ASYNC|SND_LOOP);//music player
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
    case 3:
        Sound("ThinkofMe");
        break;
    case 4:
        Sound("Afterschool");
        break;
    case 5:
        Sound("Phantom");
        break;
    }
}
void Game::EndStory()
{
    map.mapNum=5;
    BgMusic(map.mapNum);
    fstream fp1;
    fp1.open("End1.txt",fstream::in);
    if(fp1)
    {
        string str;
        while(getline(fp1,str))
        {
            system("cls");
            map.SetCursorPosition(5,10);
            cout<<str;
            Sleep(4500);
        }
        fp1.close();
    }
    map.SetCursorPosition(5,13);
    system("pause");
    system("cls");
    map.GetMap();
    map.PrintMap();
    clock_t t1;
    t1=clock();
    while(map.Keyboard()!=31)
    {
        clock_t t2=clock();
        double t=(t2-t1)/(double)(CLOCKS_PER_SEC);
        map.SetCursorPosition(35,6);
        cout<<t;
        if(t>=50)
        {
            system("cls");
            map.SetCursorPosition(10,10);
            cout<<"You lose";
            exit(1);
        }
        map.SetCursorPosition(0,15);
        system("pause>nul");
    }
    system("cls");
}


