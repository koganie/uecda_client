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
    inline bool isOnset() const{
        return (baBit&(IS_BA_ONSET))!=0;//空場か？
    }
    inline bool isKaidan() const{
        return (baBit&(IS_BA_KAIDAN))!=0;//階段か？
    }
    inline bool isPair() const{
        return (baBit&(IS_BA_PAIR))!=0;//ペアか？
    }
    inline bool isTanki() const{
        return (baBit&(IS_BA_TANKI))!=0;//単騎か？
    }
    inline bool isKakumei() const{
        return (baBit&(IS_BA_KAKUMEI))!=0;//革命か？
    }
    inline bool isShibari() const{
        return (baBit&(IS_BA_SHIBARI))!=0;//縛りか？
    }
    inline bool isJTanki() const{
        return (baBit&(IS_BA_JOKER))!=0;//ジョーカー単騎か？
    }
    inline void setOnset(bool flag){//空場フラグをセットする
        if(flag)    baBit |=  IS_BA_ONSET;
        else        baBit &= ~IS_BA_ONSET;
    }
    inline void setKakumei(bool flag){//革命フラグをセットする
        if(flag)    baBit |=  IS_BA_KAKUMEI;
        else        baBit &= ~IS_BA_KAKUMEI;
    }
    inline void revKakumei(){//革命を反転する
        if(isKakumei()) setKakumei(0);//革命状態であるなら戻す
        else            setKakumei(1);//通常状態であるなら立てる
    }
    inline void setKaidan(bool flag){//階段フラグをセットする
        if(flag)    baBit |=  IS_BA_KAIDAN;
        else        baBit &= ~IS_BA_KAIDAN;
    }
    inline void setPair(bool flag){//ペアフラグをセットする
        if(flag)    baBit |=  IS_BA_PAIR;
        else        baBit &= ~IS_BA_PAIR;
    }
    inline void setTanki(bool flag){//単騎フラグをセットする
        if(flag)    baBit |=  IS_BA_TANKI;
        else        baBit &= ~IS_BA_TANKI;
    }
    inline void setShibari(bool flag){//縛りフラグをセットする
        if(flag)    baBit |=  IS_BA_SHIBARI;
        else        baBit &= ~IS_BA_SHIBARI;
    }
    inline void setJTanki(bool flag){//ジョーカー単騎フラグをセットする
        if(flag)    baBit |=  IS_BA_JOKER;
        else        baBit &= ~IS_BA_JOKER;
    }
	
    inline int whoseTurn() const{//現在のターンの人のプレイヤー番号を返す
        return mPlayers.turn;
    }
    int mNum;
    int mRank;
    int mRankR;         //ランク（強さ）
    int mRankL;         //ランク（強さ）
    int mSuits;
    Card mCard;         //場札
    Players mPlayers;   //各プレイヤーの情報
    
    Table();
    
    void firstGame(int cards[8][15]);
    void purge();
    void setBafuda(int cards[8][15]);
    void setBaInfo(int cards[8][15]);
    void print();
    
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