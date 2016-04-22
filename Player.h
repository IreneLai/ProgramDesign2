#include<string>
#include"time.h"
#include<iostream>
#include<stdlib.h>
#include <stdio.h>
#ifndef PLAYER_H_
#define PLAYER_H_
class Player
{
public:
    Player (){}
    Player(std::string name_,int money_,int time_):name(name_),money(money_),time(time_){}
    ~Player(){}
    std::string name;
    int money=10000;
    int time=0;
    std::string newspaper[5][3];
    int buyNumNews=0;
    int storyline[20]={0};
    //0:NeilTeak 1:gypsy 2:sherlock 3:gunget 4:guntolestrade
    //5:orphan 6:persiaErick 7:cristine 8:persiasecret 9:(5)
    std::string story[15];
    bool GuessDigits();
    bool PaperScissorRock();
    bool NumGuess();

};

#endif // PLAYER_H_
