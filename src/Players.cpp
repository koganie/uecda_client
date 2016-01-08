#include <iostream>

#include "Card.h"
#include "Table.h"
#include "Players.h"

using namespace std;

int Players::getSeats(){
    //現在のターンの人が座っている席番号
    for(int i=0;i<5;i++){
        if(seats[i]==turn)return i;
    }
    return -1;
}

int Players::getCardsNum(){
    //現在のターンの人の持ち札数
    return cards_num[turn];
}

void Players::print() const{
    int i;
    printf("num=");
    for(i=0;i<5;i++)printf("%d,", cards_num[i]);
    printf("\ngra=");
    for(i=0;i<5;i++)printf("%d,", grades[i]);
    printf("\nseat=");
    for(i=0;i<5;i++)printf("%d,", seats[i]);
    
    printf("\npass=%d ", isPassed);
    for(i=0;i<5;i++)printf("%d,", (isPassed&(1<<i))!=0 );
    
    printf("\ngoal=%d ", isGoaled);
    for(i=0;i<5;i++)printf("%d,", (isGoaled&(1<<i))!=0 );
    
    printf("\nturn=%d \n", turn);
}

void Players::update(int cards[8][15]){
    //カードの5行目以下を見て更新する
    if(cards_num[turn] == cards[6][turn]){//新しいやつと変わっていない = パスした
        isPassed |= (1 << turn);
    }else{
        cards_num[turn] = cards[6][turn];   //枚数を更新して
        if(cards_num[turn] == 0){           //0枚になったら
            isGoaled |= (1 << turn);        //あがりっ！
        }
    }
    /*
	cout <<"cn" << endl;
	for(int i=0;i<5;i++){
		cout << cards_num[i] <<":"<< cards[6][i]<<endl;
	}
    */
    turn = cards[5][3];     //新しいプレイヤー番号に更新
}
    
void Players::set(int cards[8][15]){
    //ゲーム開始時に各プレイヤーの情報を格納する
    for(int i=0;i<5;i++){
        cards_num[i] = cards[6][i]; //手持ちのカード枚数
        grades[i] = cards[6][5+i];  //各プレーヤのランク
        seats[i]  = cards[6][10+i]; //席iに座っているプレイヤー番号
        sekijun[cards[6][10+i]] = i;//プレイヤー番号iの席番号
    }
    isPassed = 0;
    isGoaled = 0;
    turn = cards[5][3];//ターンであるプレイヤー番号
}
    
void Players::init(){//初期化
    turn = -1;
    isPassed = 0;
    isGoaled = 0;
}

void Players::recover(){//パスから復帰
    isPassed = 0;
}
    
void Players::simGoal(){
    isGoaled |= (1 << turn);
}

void Players::nextTurn(){
    int nowSeki = sekijun[turn];//今の席番号
    nowSeki = (nowSeki+1)%5;    //1つ席をずらす
    
    int GP = isGoaled|isPassed; //あがりまたはパスの集合
    if( GP == (BITi(5)-1) ){    //みんなに提出権がなくなった
        recover();//パスを復帰させる
        GP = isGoaled;
    }
    while( (GP&BITi(seats[nowSeki]))!=0 ){//すでにあがっている
        nowSeki = (nowSeki+1)%5;    //1つ席をずらす
    }
    
    //std::cout << "old turn is " << turn  << std::endl;
    turn = seats[nowSeki];
    //std::cout << "new turn is " << turn  << std::endl;
}

int Players::simPass(){
    isPassed |= (1 << turn);
    if( (isPassed|isGoaled) == (1<<5)-1 ){//全員に提出権がなくなる
        isPassed = 0;
        return 1;
    }else{
        nextTurn();
    }
    return 0;
}

void Players::simSubmit(const Card &cd){//カードを提出した後処理
    //パスはここには来ない
    
    cards_num[turn] = cards_num[turn] - cd.mNum;//カード枚数を差し引く
    if(cards_num[turn]==0){//あがった
        isGoaled |= BITi(turn);
    }else if(cards_num[turn]<0){
        printf("okasisi!!\n");
        printf("%d %d\n", cards_num[turn], cd.mNum);
        cd.printBit();
        cd.printBit3();
        exit(1);
    }
    
    if(cd.is8giri()==0){//8切りではない
        nextTurn();
    }
    else{//8切りだった
        isPassed = 0;//パスを復帰させる
        if(cards_num[turn]==0){//あがっていたら次の人
            nextTurn();
        }
    }
}
