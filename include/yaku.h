#ifndef DEFINE_YAKU
#define DEFINE_YAKU

#include <string>
#include<vector>
#include "bit.h"

using namespace std;

class Yaku{
private:
    int64 mCardBit;       //カードのビット表現
    int mCards[8][15];
    
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
    
    void setSuit(int s);
    void setTanki();
    void setPair();
    void setKaidan();
    void setJTanki();
    
    int64 getCardBit() const;//カードビットを返す
    void printBit() const;
    void printBit2() const;
    void printBit3() const;
    
    void print() const;
	
	Yaku();
    
    //コンストラクタ
    //左からカードビット、スート、枚数、左側のランク、右側のランク（階段、joker単騎のとき以外は同じ数字）、使うjokerのスート、使うjokerのランク（使わないときは-1）
    Yaku(int64 cd, int suits, int num, int rank, int rank2, int jps, int jpr);
    //joker使わないコンストラクタを用意してもいい
    
    //整理しろ
    void clear();
    void init();
    void demoPass();
    
    //違いがよくわからんので改名しろ
    void setBit(int src[8][15]);//[8][15]配列から情報を格納する //場札の解析用である
    void set815ToBit(int src[8][15]);//815配列をbitに変換する
    void set815ToYaku(int src[8][15]);//815配列をyaku形式に変換する
    void setBitTo815(int dest[8][15]) const;//bitを815配列に変換する
    
    string getStr();
    
};

void removeLap(vector<Yaku> *vecCard, int64 cdBit);
void removeYaku(vector<Yaku> *vecCard, Yaku &yaku);
void removePass(vector<Yaku> *vecCard);

#endif

