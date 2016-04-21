#include"Game.h"
#include<string>
#include<iostream>
#include<stdlib.h>
#include <iomanip>
#include<stdio.h>
#ifndef RANK_H_
#define RANK_H_
struct Rank
{
    char name[21]="";
    char finish[21]="";
    int money=0;
    int time=0;
    double score=0;
    bool operator <(const Rank &r)const
    {
        if(score>r.score) return true;
        return false;
    }
};
void DisplayRank();
#endif // RANK_H_
#ifndef DATA_H_
#define DATA_H_
struct Data
{
    char Pname[21]="";
    int money=0;
    int time=0;
    int buyNumNews=0;
    int storyline=0;
};
#endif // DATA_H_
#ifndef RECORD_H_
#define RECORD_H_
class Record
{
public:
    Record() {};
    ~Record() {};
    void Interface(Game &game);
    int Search(const char name[]);
    bool Remove(const int ind);
    void Close();
    bool Load();
    bool Save(Game *g);
    void InputFile();
private:
    int numRecord_=0;
    static constexpr int capacity_=100;
    Data data_[capacity_];
    Data CreateData_(const Game *g);
    bool OutputFile_();
};
#endif // RECORD_H_

