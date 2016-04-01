#include<string>
class Player
{
public:
    Player (){}
    Player(std::string name_,int money_,int time_):name(name_),money(money_),time(time_){}
    ~Player(){}
    std::string name;
    int money=100;
    int time=0;
    int toolRecord[4];//0:news 1:map 2:gun 3:key
    std::string newspaper[5];
};
