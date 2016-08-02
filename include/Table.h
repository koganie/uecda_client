#ifndef DEFINE_TABLE
#define DEFINE_TABLE

using namespace std;

#include "Yaku.h"
#include "Player.h"

class Table{
private:
    int64 baBit;//場の情報は32bit
	//右から
    // 0:空場
	// 1:階段
	// 2:ペア
	// 3:単騎
	// 4:革命
	// 5:縛り
	// 6:ジョーカー単騎
	
public:
    bool isOnset() const;
    bool isKaidan() const;
    bool isPair() const;
    bool isTanki() const;
    bool isKakumei() const;
    bool isShibari() const;
    bool isJTanki() const;
    bool isChangePhase() const;
    bool is11back() const;
    void setOnset(bool flag);//空場フラグをセットする
    void setKakumei(bool flag);//革命フラグをセットする
    void revKakumei();//革命を反転する
    void setKaidan(bool flag);//階段フラグをセットする
    void setPair(bool flag);//ペアフラグをセットする
    void setTanki(bool flag);//単騎フラグをセットする
    void setShibari(bool flag);//縛りフラグをセットする
    void setJTanki(bool flag);//ジョーカー単騎フラグをセットする
	int whoseTurn() const;//現在のターンの人のプレイヤー番号を返す
    
    /*
    //ここらへんはmBafudaを参照するのでいらない
    int mNum;
    int mRankR;         //ランク（強さ）
    int mRankL;         //ランク（強さ）
    int mSuits;
    */
    
    int player_id;//前回の出した人のID
    int preBafuda[8][15];
    Yaku mBafuda;         //場札
    //Player mPlayer;   //各プレイヤーの情報
    
    Table();
    
    void firstGame(int cards[8][15]);
    void purge();
    //void setBafuda(int cards[8][15]);
    void setBaInfo(int cards[8][15]);

    void print() const;
    
    void print2();

    //クライアント用の関数群
    bool sameBafuda( int bafuda[8][15] );
    void setBafuda( const Yaku &yaku );
};

#endif

