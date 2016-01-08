#ifndef TABLE_DEFINE
#define TABLE_DEFINE

#include "Card.h"
#include "Players.h"

class Table{
private:
    uint32_t baBit;//場の情報は32bit
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
    void setOnset(bool flag);//空場フラグをセットする
    void setKakumei(bool flag);//革命フラグをセットする
    void revKakumei();//革命を反転する
    void setKaidan(bool flag);//階段フラグをセットする
    void setPair(bool flag);//ペアフラグをセットする
    void setTanki(bool flag);//単騎フラグをセットする
    void setShibari(bool flag);//縛りフラグをセットする
    void setJTanki(bool flag);//ジョーカー単騎フラグをセットする
	int whoseTurn() const;//現在のターンの人のプレイヤー番号を返す
    
    int mNum;
    int mRank;
    //int mRankR;         //ランク（強さ）
    //int mRankL;         //ランク（強さ）
    int mSuits;
    Card mCard;         //場札
    Players mPlayers;   //各プレイヤーの情報
    
    Table();
    
    void firstGame(int cards[8][15]);
    void purge();
    void setBafuda(int cards[8][15]);
    void setBaInfo(int cards[8][15]);
    void print() const;
    
    bool isTurn(int player_num);
    
    /* 以下シミュレーション用の関数      */
    /* 通常のtableの更新に使うことはない */
    /* サーバ的な役割をになうのである */
    
    void simGoal();
    int simPass();
    void sim8giri(Card &cd);
    void simSubmit(const Card &cd);
};


#endif