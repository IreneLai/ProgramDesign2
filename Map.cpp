#include"map.h"
using namespace std;
void Map::SetColor(int f,int b)
{
    unsigned short ForeColor=f+16*b;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,ForeColor);
}
void Map::SetCursorPosition(const int x,const int y)const
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE); //handle cursor buffer
    COORD pos ;
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(output,pos);
}
void Map::ClearScreen(const std::string &ch)
{
    for(int x=0; x<mapRow_; ++x)
    {
        for(int y=0; y<mapCol_; ++y)
        {
            SetCursorPosition(x,y);
            std::cout<<ch;
        }
    }
}
void Map::Position(const int x,const int y)
{
    xPos=x;
    yPos=y;
    map_[x][y]=2; //location ascii
}
void Map::PrintMap()
{
    SetColor(mapNum,0);
    for(int i=0; i<mapRow_; ++i)
    {
        for(int j=0; j<mapCol_; ++j)
        {
            if(map_[i][j]==2) SetColor(15,0);
            else if((map_[i][j]>=4&&map_[i][j]<=6)||map_[i][j]==21) SetColor(12,14);
            else if(map_[i][j]==1) SetColor(13,0);
            else if((map_[i][j]>=65)||(map_[i][j]>=49&&map_[i][j]<=57)) SetColor(14,0);
            else if(map_[i][j]!=35&&map_[i][j]!=0) SetColor(7,0);
            std::cout<<static_cast<char>(map_[i][j]);
            SetColor(mapNum,0);
        }
        std::cout<<std::endl;
    }
    Sleep(10);
}
bool Map::GetMap()
{
    char mapFile[21]="";
    sprintf(mapFile,"map%d.txt",mapNum);
    FILE *fmap=fopen(mapFile,"r");
    if(fmap)
    {
        for(int i=0; i<mapRow_; ++i)
        {
            for(int j=0; j<mapCol_; ++j)
            {
                fscanf(fmap,"%d",&map_[i][j]);
            }
        }
        fclose(fmap);
        return true;
    }
    return false;
}
int Map::Keyboard()
{
    int trigger=-1;
    for(int i=0; i<mapRow_; ++i)
    {
        for(int j=0; j<mapCol_; ++j)
        {
            switch (map_[i][j])
            {
            case 2: //location ascii
            {
                SetColor(15,0);
                if(GetAsyncKeyState(VK_UP)!=0)
                {
                    if(map_[i-1][j]==0)
                    {
                        i-=1;
                        map_[i][j]=2;
                        map_[i+1][j]=0;
                        SetCursorPosition(j,i);
                        std::cout<<static_cast<char>(2);
                        SetCursorPosition(j,i+1);
                        std::cout<<" ";
                    }
                    else
                    {
                        trigger=map_[i-1][j];

                    }
                }
                else if (GetAsyncKeyState(VK_DOWN)!=0)
                {
                    if(map_[i+1][j]==0)
                    {
                        i+=1;
                        map_[i][j]=2;
                        map_[i-1][j]=0;
                        SetCursorPosition(j,i);
                        std::cout<<static_cast<char>(2);
                        SetCursorPosition(j,i-1);
                        std::cout<<" ";

                    }
                    else
                    {
                        trigger=map_[i+1][j];
                    }
                }
                else if(GetAsyncKeyState(VK_LEFT)!=0)
                {
                    if(map_[i][j-1]==0)
                    {
                        j-=1;
                        map_[i][j]=2;
                        map_[i][j+1]=0;
                        SetCursorPosition(j,i);
                        std::cout<<static_cast<char>(2);
                        SetCursorPosition(j+1,i);
                        std::cout<<" ";

                    }
                    else
                    {
                        trigger=map_[i][j-1];
                    }
                }
                else if(GetAsyncKeyState(VK_RIGHT)!=0)
                {
                    if(map_[i][j+1]==0)
                    {
                        j+=1;
                        map_[i][j]=2;
                        map_[i][j-1]=0;
                        SetCursorPosition(j,i);
                        std::cout<<static_cast<char>(2);
                        SetCursorPosition(j-1,i);
                        std::cout<<" ";


                    }
                    else
                    {
                        trigger=map_[i][j+1];
                    }
                }
                xPos=i,yPos=j;
                SetColor(12,0);
                break;
            }
            }
        }
    }
    return trigger;
}
