#include"player.h"
using namespace std;
bool Player::GuessDigits()
{
    //srand(time(NULL));
    int num[4]= {0};
    int guessNum=0,times=0;
    int ans=0;
    for(int i=0; i<4; ++i )
    {
        int noRe=0;
        while(noRe!=1)
        {
            num[i]=rand()%10;
            noRe=1;
            for(int j=0;j<i;j++)
            {
                if(num[j]==num[i]) noRe=0;
            }
        }
    }
    ans=num[0]+num[1]*10+num[2]*100+num[3]*1000;
    cout<<"[猜數字遊戲]"<<endl;
    cout<<"規則：A代表數字對、位置對 ； B代表位置錯，但數字對"<<endl;
    cout<<"例如：正確->1234 你猜->2538 顯示：1A1B"<<endl;
    cout<<"每位數是 0 ~ 9 ，不會重複，最多猜10次"<<endl<<endl;
    while(times!=10)
    {
        int countA=0,countB=0;
        cout<<"請猜一數字...>";
        cin>>guessNum;
        int guess[4]= {0};
        for(int i=0; i<4; ++i )
        {
            guess[i]=guessNum%10;
            guessNum=guessNum/10;
        }
        for(int i=0; i<4; ++i)
        {
            for(int j=0; j<4; ++j)
            {
                if(guess[i]==num[j])
                {
                    if(i==j)countA++;
                    else {countB++;break;}
                }
            }
        }
        if(countA==4)return true;
        else cout<<countA<<"A"<<countB<<"B"<<endl;
        countA=0;
        countB=0;
        times++;
    }
    cout<<endl<<"答案："<<ans<<endl;
    return false;
}
enum PSR {NUL,PAPER,SCISSORS,ROCK};
bool Player::PaperScissorRock()
{
    cout<<"[剪刀石頭布]"<<endl;
    cout<<"規則：平手算你贏"<<endl<<endl;
    cout<<"(1)布 "
        <<"(2)剪刀 "
        <<"(3)石頭"<<endl;
    cout<<"選擇...>";
    int tmp;
    cin>>tmp;
    int result=rand()%3+1;
    cout<<"對手：";
    switch (result)
    {
    case PAPER:
        cout<<"布"<<endl;
        if(tmp==SCISSORS) return true;
        break;
    case SCISSORS:
        cout<<"剪刀"<<endl;
        if(tmp==ROCK) return true;
        break;
    case ROCK:
        cout<<"石頭"<<endl;
        if(tmp==PAPER) return true;
        break;
    }
    if(tmp==result) return true;
    return false;
}
bool Player::NumGuess()
{
     cout<<"[預測數字]"<<endl;
    cout<<"規則：請猜出我心中數字 (介於1到50) 能猜5次"<<endl<<endl;
    int times=0;
    int real=rand()%50+1;
    while(times!=5)
    {
        cout<<"請輸入數字...>";
        int guess=0;
        cin>>guess;
        if(guess==real) return true;
        else if(guess>real) cout<<"小於 "<<guess<<endl;
        else cout<<"大於 "<<guess<<endl;
        times++;
    }
    cout<<endl<<"答案："<<real<<endl;
    return false;
}
