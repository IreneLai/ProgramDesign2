#include<fstream>
#include<string>
#include<sstream>
#include<time.h>
#include<stdio.h>
#include<queue>
#include<Windows.h>

class Map
{
public:
    void SetColor(int f,int b)//¶r≈È√C¶‚
    {
        unsigned short ForeColor=f+16*b;
        HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hCon,ForeColor);
    }
    void SetCursorPosition(const int x,const int y)const
    {
        HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE); //handle cursor buffer
        COORD pos ;
        pos.X=x;
        pos.Y=y;
        SetConsoleCursorPosition(output,pos);

    }
    void ClearScreen(const std::string &ch)
    {
        for(int x=0; x<mapRow_; ++x)
        {
            for(int y=0; y<mapCol_; ++y)
            {
                SetCursorPosition(x,y);
                std::cout<< ch;
            }
        }
    }
    void Position(const int x,const int y)
    {
        xPos=x;
        yPos=y;
        map_[x][y]=2;
    }
    bool GetMap(const int numMap)
    {
        std::stringstream n;
        n<<numMap;
        std::fstream fmap;
        std::string mFile("map");
        mFile+=n.str();
        mFile+=".txt";
        fmap.open(mFile,std::fstream::in);
        if(fmap)
        {
            std::string tmp,sub;
            int num;
            std::queue<int> q;
            while(getline(fmap,tmp))
            {
                std::stringstream ss(tmp);
                while(getline(ss,sub,' '))
                {
                    std::stringstream t(sub);
                    t>>num;
                    q.push(num);
                }
            }
            for(int i=0; i<mapRow_; ++i)
            {
                for(int j=0; j<mapCol_; ++j)
                {
                    if(!q.empty())
                    {
                        map_[i][j]=q.front();
                    }
                    q.pop();
                }
            }
            fmap.close();
            return true;
        }
        return false;
    }
    void PrintMap()const
    {
        for(int i=0; i<mapRow_; ++i)
        {
            for(int j=0; j<mapCol_; ++j)
            {
                std::cout<<static_cast<char>(map_[i][j]);
            }
            std::cout<<std::endl;
        }
        Sleep(10);
    }
    int Keyboard()
    {
        int trigger=-1;
        for(int i=0; i<mapRow_; ++i)
        {
            for(int j=0; j<mapCol_; ++j)
            {
                switch (map_[i][j])
                {
                case 2:
                {
                    SetColor(3,0);
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
    int xPos=0,yPos=0;
    int mapNum;

private:
    constexpr static int mapRow_=16,mapCol_=32;
    int map_[mapRow_][mapCol_];
};
