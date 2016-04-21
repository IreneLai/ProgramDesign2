#include"Record.h"
#include<algorithm>
using namespace std;
enum List {NUL,LOAD,NEW,EXIT};
void Record::Interface(Game &game)
{
    cout<<"\t\t------------------ 玩家排行 -----------------------"<<endl
        <<"\t\t"<<"排名"<<setw(12)<<"姓名"<<setw(16)<<"時間"<<endl<<endl;
    DisplayRank();
    cout<<endl<<endl;

    cout<<"\t\t------------------ 玩家紀錄 -----------------------"<<endl
        <<"\t\t"<<"編號"<<setw(12)<<"姓名"<<setw(12)<<"金錢"<<setw(12)<<"時間花費"<<endl<<endl;
    Load();
    for(int i=0; i<numRecord_; ++i)
    {
        cout<<"\t\t"<<"["<<i+1<<"]"<<setw(12)<<data_[i].Pname<<setw(12)<<data_[i].money<<setw(6)
            <<(data_[i].time/CLOCKS_PER_SEC/3600)<<"時"<<(data_[i].time/CLOCKS_PER_SEC/60)<<"分"<<(data_[i].time/CLOCKS_PER_SEC%60)<<"秒"<<endl;
    }

    cout<<endl;
    game.map.SetColor(14,0);
    int choose=0;
    cout<<"\t\t請選擇接下來動作:"<<endl
        <<"\t\t(1)載入玩家 (2)開新遊戲 (3)離開遊戲...>";
    cin>>choose;
    string name;
    switch (choose)
    {
    case LOAD:
        cout<<"\t\t請輸入載入玩家之編號...>";
        cin>>choose;
        if(choose>0&&choose<=numRecord_)
        {
            choose--;
            game.player.name=data_[choose].Pname;
            game.player.money=data_[choose].money;
            game.player.buyNumNews=data_[choose].buyNumNews;
            game.player.storyline[data_[choose].storyline]=1;
            game.player.time=data_[choose].time;
        }
        else
        {
            cout<<"\t\t無該玩家";
            exit(1);
        }
        break;
    case NEW:
        cout<<"\t\t請輸入姓名...>";
        cin>>name;
        game.player.name=name;
        break;
    case EXIT:
        exit(1);
        break;
    }
}
bool Record::Save(Game *g)
{
    string ans;
    Load();
    int sID=Search(g->player.name.c_str());
    if(sID>=0)
    {
        cout<<endl<<"\t\t找到相同的玩家，請問要"<<endl
            <<"\t\t[S:覆蓋；R:重新命名;E:離開]...>";
        cin>>ans;
        if(ans=="S")
        {
            data_[sID]=CreateData_(g);
        }
        else if(ans=="R")
        {
            char reName[21]="";
            cout<<"\t\t請輸入新名稱...>";
            cin>>reName;
            while(Search(reName)>=0)
            {
                cout<<"\t\t仍有相同名稱，請再輸入...>";
                cin>>reName;
            }
            g->player.name=reName;
            if(numRecord_<capacity_) {data_[numRecord_]=CreateData_(g);numRecord_++;}
        }
        else return false;
        if(OutputFile_()) return true;
        return false;
    }
    if(numRecord_<capacity_)
    {
        data_[numRecord_]=CreateData_(g);
        numRecord_++;
        if(OutputFile_()) return true;
    }
    return false;
}
int Record::Search(const char name[])
{
    for(int i=0; i<numRecord_; ++i)
    {
        if(strcmp(data_[i].Pname,name)==0) return i;
    }
    return -1;
}
Data Record::CreateData_(const Game *g)
{
    Data d;
    strcpy(d.Pname,g->player.name.c_str());
    d.money=g->player.money;
    d.buyNumNews=g->player.buyNumNews;
    int story=0;
    for(int i=0; i<20; ++i)
    {
        if(g->player.storyline[i]==1) story=i;
    }
    d.storyline=story;
    d.time=clock()+g->player.time;
    return d;
}
bool Record::Load()
{
    FILE* fp;
    fp=fopen("record.txt","r");
    if(fp)
    {
        if(fscanf(fp,"%d",&numRecord_)==1)
        {
            for(int i=0; i<numRecord_; ++i)
            {
                fscanf(fp,"%s %d %d %d %d",data_[i].Pname,&data_[i].money,&data_[i].time,&data_[i].buyNumNews,&data_[i].storyline);
            }
        }
        fclose(fp);
        return true;
    }
    return false;
}
void DisplayRank()
{
    int numRank=0;
    FILE *fp=fopen("rank.txt","r");
    if(fp)
    {
        fscanf(fp,"%d",&numRank);
        Rank *RankArray=(Rank*)malloc(sizeof(Rank)*numRank);
        if(RankArray)
        {
            for(int i=0; i<numRank; ++i)
            {
                fscanf(fp,"%s %d %d %lf %s",RankArray[i].name,&RankArray[i].money,&RankArray[i].time,&RankArray[i].score,&RankArray[i].finish);
            }
            sort(RankArray,RankArray+numRank);
            for(int i=0; i<numRank; ++i)
            {
                cout<<"\t\t"<<"["<<i+1<<"]"<<setw(12)<<RankArray[i].name<<setw(35)<<RankArray[i].finish<<endl;
            }
            free(RankArray);
        }
        fclose(fp);
    }
}
bool Record::OutputFile_()
{
    fstream fp;
    fp.open("record.txt",ios::out|ios::trunc);
    if(fp)
    {
        fp<<numRecord_<<endl;
        for(int i=0; i<numRecord_; ++i)
        {
            fp<<data_[i].Pname<<" "<<data_[i].money<<" "<<data_[i].time<<" "<<data_[i].buyNumNews<<" "<<data_[i].storyline<<endl;
        }
        fp.close();
        return true;
    }
    return false;
}

