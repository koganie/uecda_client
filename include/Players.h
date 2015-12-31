#ifndef PLAYERS_DEFINE
#define PLAYERS_DEFINE

#include <iostream>

using namespace std;

class Players{
public:
    int cards_num[5];//プレイヤー番号iの持ち札数
    int grades[5];  //プレイヤー番号iの身分i
    int seats[5];   //seats[i]は席[i]に座っているプレイヤー番号
    int sekijun[5]; //プレイヤー番号iの席番号
    
    int turn;       //現在のターンの "プレイヤー番号"
    
    int isPassed;   //プレイヤー番号iはパスをしているか
    int isGoaled;   //プレイヤー番号iはあがっているか
    
    int getSeats();
    int getCardsNum();
    
    void print();
    void update(int cards[8][15]);
    
    void set(int cards[8][15]);
    
    void init();
    
    void recover();
    
    void simGoal();
    
    void nextTurn();
    
    int simPass();
    
    void simSubmit(const Card &cd);//カードを提出した後処理
    
};

#endif