#include<string>
class Player
{
public:
    int getMoney()const
    {
        return money_;
    }
    std::string name;

private:
    int money_=0;


};
