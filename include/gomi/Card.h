#ifndef CARD_DEFINE
#define CARD_DEFINE

#include <iostream>
#include <vector>
#include "common.h"
#include "bit.h"

/*
cardBitの中身、defineはcommon.hにある
右から
13*3+13-1 = 39+12 = 51
個の項目にjoker以外のカードがまとまっている。ので
#define CARDBIT(suit, rank)	BITull(suit*13 + (rank-1))
を使うと815配列と同じような感覚でbit演算を行うことができる。

52番目以降のビットは次のような定義でビットがフラグとして使われている
#define IS_SPADE3   BITull(0)
#define IS_JUSED	BITull(52)//jokerを使っているか
#define IS_KAIDAN   BITull(53)//階段か
#define IS_PAIR     BITull(54)//ペアか
#define IS_PASS     BITull(55)//パスか
#define IS_8GIRI    BITull(56)//8切りか
#define IS_NUM(num) BITull(56+num)//カード枚数は何枚か?1以上が入力

*/

class Card{
private:
    int64 mCardBit;       //カードのビット表現
    int mCards[8][15];  //カードの配列表現
    
    //カードの特性
    //bitと重複するものも多くあるのであんまり使わないかも
    //基本的にはbool is～()を使って問い合わせればよい
    int mKaidan;        //階段
    int mPair;          //ペア
    int mTanki;         //単騎
    int mPass;          //パス
    int mJoker;         //ジョーカー単騎
    
    //副作用
    int mKakumei;       //革命を引き起こす
    //int mShibari;       //しばり
    int m8giri;         //8切りを起こす
    
public:
    int mNum;           //枚数
    int mRankR;         //ランク（強さ）
    int mRankL;         //ランク（強さ）
    
    int mSuits;         //スート
    int mJposSuit;
    int mJposRank;
    bool mSpe3;
    
    bool isKaidan() const;//階段ならTrue、以下同様に
    bool isPair() const;
    bool isTanki() const;
    bool isJTanki() const;
    bool isJUsed() const;
    bool isKakumei() const;
    //bool isShibari() const;
    bool is8giri() const;
    bool isSpade3() const;
    bool isPass() const;
    
    int64 getCardBit() const;//カードビットを返す
    void printBit() const;
    void printBit2() const;
    void printBit3() const;
	
	Card();
    
    //コンストラクタ
    //左からカードビット、スート、枚数、左側のランク、右側のランク（階段、joker単騎のとき以外は同じ数字）、使うjokerのスート、使うjokerのランク（使わないときは-1）
    Card(int64 cd, int suits, int num, int rank, int rank2, int jps, int jpr);
    //joker使わないコンストラクタを用意してもいい
    
    //整理しろ
    void clear();
    void init();
    void demoPass();
    
    //違いがよくわからんので改名しろ
    void setBit(int src[8][15]);//[8][15]配列から情報を格納する //場札の解析用である
    void set815ToBit(int src[8][15]);//815配列をbitに変換する
    void setBitTo815(int dest[8][15]) const;//bitを815配列に変換する
};

void removeLap(std::vector<Card> *vecCard, int64 cdBit);
void removePass(std::vector<Card> *vecCard);
bool isCard1WeakerThanCard2WhenNotKakumei(const Card &c1, const Card &c2);
bool isCard1WeakerThanCard2WhenKakumei(const Card &c1, const Card &c2);
int selectBigCards(Card *card, const std::vector<Card> &vecCard);
//int selectLowCards(const std::vector<Card> &vecCard);

#endif