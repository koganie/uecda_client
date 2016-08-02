#include <iostream>
#include <cstdio>
#include <cstdlib>
#include"Player.h"

using namespace std;

void Player::setName(int card[8][15]){
    for(int i=0; i<=8; i++){
		name[i] = (char)card[1][i];
	}
	name[9]='\0';
}

void Player::setId(int num){
    id = num;
    sekijun = num;
}

void Players::sekigae( Random *random ){
    //席替え
    int a = (int)( (id.size()-1) * random->rand() );
    int b = (int)( (id.size()-1) * random->rand() );
    int c = sekijun[a];
    sekijun[a] = sekijun[b];
    sekijun[b] = c;
}

void Players::reset(){
    //席替えと、ランクのリセット
    //sekigae();//席替えは行われない
    for(int i=0; i<id.size(); i++){
        id[i].mibun = HEIMIN;
    }
}


void Players::setPlayers( int cards[8][15] ){
    int temp[5],temp1[5];
    for(int i=0;i<5;i++){
        id[i].cards_num = cards[6][i]; //手持ちのカード枚数
        id[i].mibun = cards[6][5+i];  //各プレーヤのランク
        //id[i].seats  = cards[6][10+i]; //席iに座っているプレイヤー番号
        temp[i] = cards[6][10+i];//temp[i]には席iに座っているプレイヤー番号
        id[cards[6][10+i]].sekijun = i;//プレイヤー番号iの席番号
    }
    turn = 0;
    //sekijun.push_back(cards[5][3]);//ターンであるプレイヤー番号
    int index = id[cards[5][3]].sekijun;
    for(int i=0;i<5;i++){
        sekijun.push_back( temp[index] );
        index = (index+1)%5;
    }
}

void Player::initCard(){
    //カード初期化
    for(int i=0; i<8; i++){
        for(int j=0; j<15; j++){
            cards[i][j] = 0;
        }
    }
    //枚数もゼロ
    cards_num = 0;
    //役も削除
    yakus.clear();
}

Player::Player(){
    mibun = HEIMIN;
    passed = false;
}

void Player::printCards(){
    for(int i=0;i<5;i++){
        for(int j=0;j<15;j++){
            cout << cards[i][j] << " ";
        }
        cout << endl;
    }
}

void Player::subtraction(const int card[8][15]){
    int joker_num = 0;
    for(int i=0;i<5;i++){
        for(int j=0;j<15;j++){
            if(card[i][j]==1){
                cards[i][j]=0;
            }
            else if(card[i][j]==2){
                joker_num++;
            }
        }
    }
    if(joker_num==1){
        if(cards[4][2]!=0){
            cards[4][2]=0;
        }else{
            cards[4][1]=0;
        }
    }else if(joker_num==2){
        cards[4][1]=0;
        cards[4][2]=0;
    }
}

int Players::size(){
    return id.size();
}

bool Players::isInequality(){
    if(id[0].mibun != HEIMIN || id[1].mibun != HEIMIN){//プレイヤーに身分差がついていれば
        return true;
    }else{
        return false;
    };
}

int Players::mibunId(int num){
    for(int i=0; i<id.size(); i++){
        if(id[i].mibun == num){
            return i;
        }
    }
    return -1;
}

int Players::turnId(){
    return sekijun[turn];
}

int Players::convIDtoSekiNum(int num){
    for(int i=0; i<id.size(); i++){
        if(num==sekijun[i]){
            return i;
        }
    }
    return -1;
}


void Players::nextTurn(){
    int count = 0;
    int first = turn;//今のプレイヤー
    turn = (turn + 1) % sekijun.size();//次に回すプレイヤー

    for(int i=0; i<5; i++){
        //パスしているかあがっている
        if( id[turnId()].passed == true || id[turnId()].cards_num==0 ){
            turn = (turn + 1) % sekijun.size();//さらに次を見る
        }else{
            //提出権が回ったら帰る
            return;
        }
    }
    //全員に提出権はなかった
    turn = first;
}

void Players::recover(){
    for(int i=0;i<id.size();i++){
        id[i].passed = false;
    }
}

void Players::addAgari( int num ){
    agari.push_back( num );
}

void Players::print(){
    for(int i=0; i<sekijun.size(); i++){
        cout << sekijun[i] << " ";
    }
    cout << endl;
    for(int i=0; i<agari.size(); i++){
        cout << agari[i] << " ";
    }
    cout << endl;
    for(int i=0; i<id.size(); i++){
        cout << id[i].passed << " ";
    }
    cout << endl;
    for(int i=0; i<id.size(); i++){
        cout << id[i].cards_num << " ";
    }
    cout << endl;
}

void Players::setCardsNum(){
    for(int i=0; i<id.size(); i++){
        id[i].cards_num = countCard( id[i].cards );
    }
}

void Players::pass(){
    id[turnId()].passed = true;
}

void Players::update(int cards[8][15]){
    //カードの5行目以下を見て更新する
    int index = turnId();
    if(id[index].cards_num == cards[6][index]){//新しいやつと変わっていない = パスした
        id[index].passed = true;
    }else{
        id[index].cards_num = cards[6][index];   //枚数を更新して
        if(id[index].cards_num == 0){           //0枚になったら
            agari.push_back( index );
        }
    }
    if(cards[5][4]==1){//場が流れた
        for(int i=0;i<5;i++){
            id[i].passed = false;
        }
    }
    
    //turn = cards[5][3];     //新しいプレイヤー番号に更新
    //turn = id[cards[5][3]].sekijun;
    for(int i=0;i<5;i++){
        if(sekijun[i]==cards[5][3])turn = i;
    }
}

void Players::setup(){
    for(int i=0;i<5;i++){
        Player player;
        id.push_back(player);
    }
}
