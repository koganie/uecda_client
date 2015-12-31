#ifndef CARD_DEFINE
#define CARD_DEFINE

#include <iostream>
#include <vector>
#include "common.h"

class Card{
private:
    int64 mCardBit;       //カードのビット表現
    int mCards[8][15];  //カードの配列表現
    
    //カードの特性
    int mKaidan;        //階段
    int mPair;          //ペア
    int mTanki;         //単騎
    int mPass;          //パス
    int mJoker;         //ジョーカー単騎
    
    //副作用
    int mKakumei;       //革命を引き起こす
    int mShibari;       //しばり
    int m8giri;         //8切りを起こす
    
public:
    int mNum;           //枚数
    int mRankR;         //ランク（強さ）
    int mRankL;         //ランク（強さ）
    
    int mSuits;         //スート
    int mJposSuit;
    int mJposRank;
    bool mSpe3;
    
    bool isKaidan() const;
    bool isPair() const;
    bool isTanki() const;
    bool isJTanki() const;
    bool isKakumei() const;
    //bool isShibari() const;
    bool is8giri() const;
    bool isSpade3() const;
    bool isPass() const;
    int64 getCardBit() const;
    void printBit() const;
    void printBit2() const;
    void printBit3() const;
	
	Card();
    
    Card(int64 cd, int suits, int num, int rank, int rank2, int jps, int jpr);
    
    void clear();
    void init();
    void demoPass();
    
    void setBit(int src[8][15]);//[8][15]配列から情報を格納する //場札の解析用である
    void set815ToBit(int src[8][15]);//815配列をbitに変換する
    void setBitTo815(int dest[8][15]) const;//bitを815配列に変換する
};

void removeLap(std::vector<Card> *vecCard, int64 cdBit);
void removePass(std::vector<Card> *vecCard);
bool compYakuRankL(const Card &c1, const Card &c2);
bool compYakuRankR(const Card &c1, const Card &c2);
int selectBigCards(const std::vector<Card> &vecCard);
int selectLowCards(const std::vector<Card> &vecCard);

#endif