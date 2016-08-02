#ifndef DEFINE_PLAYER
#define DEFINE_PLAYER

#include <vector>
#include<netinet/in.h>
#include<sys/socket.h>
//#include "Result.h"
#include "Yaku.h"
#include "common.h"
#include "Random.h"

using namespace std;

class Player{
private:
    
public:
    //サーバ用変数・関数
    struct sockaddr_in addr;//アドレス
    char name[15];//名前
    int sockfd;

    void setName(int card[8][15]);
    //クライアント用変数・関数
    //サーバ・クライアント共用関数

    int id;//プレイヤー番号
    int sekijun;//席順
    
    int mibun;//身分
    
    int cards[8][15];//手持ちのカード
    int cards_num;//手持ちカードの枚数
    vector<Yaku> yakus;//手持ちカードから作られる全合法手
    
    int change[8][15];//カード交換で差し出したカード
    
    void initCard();
    
    void setId(int num);
    void subtraction(const int card[8][15]);
    
    bool passed;
    
    Player();
    
    void printCards();
};


class Players{
public:
    vector<Player> id;
    //vector<int> mibun;//身分情報（）
    vector<int> sekijun;//席情報（提出順にプレイヤー番号が入っている）
    vector<int> agari;//あがり情報（あがった順にプレイヤー番号が入っている）
    
    int turn;
    int turnId();
    
    //vector<int> sockfd;
    //int sockfd(int id);
    
    int mibunId( int mibun );
    int size();
    
    bool isInequality();
    //void update( Result &result );
    
    void setCardsNum();
    void nextTurn();
    void recover();//パスから復帰させる
    void addAgari( int num );
    void pass();//現在のプレイヤーがパスした
    
    void print();
    int convIDtoSekiNum(int num);

    //サーバ用関数群
    void sekigae( Random *random );
    void reset();
    //クライアント用関数群
    void setup();
    void setPlayers(int cards[8][15]);
    void update( int cards[8][15] );

};


#endif

