#ifndef SUBMIT_CARD_DEFINE
#define SUBMIT_CARD_DEFINE

#include <vector>
#include "Table.h"

using namespace std;

void makeAllYaku(vector<Yaku> *allYaku, const int hands[8][15]);//すべての役を作る
void makeKaidanFrom815(vector<Yaku> *yaku, const int hands[8][15]);//階段を作る
void makePairFrom815(vector<Yaku> *yaku, const int hands[8][15]);//ペアを作る
void makeTankiFrom815(vector<Yaku> *yaku, const int hands[8][15]);//単騎を作る
void makePass(vector<Yaku> *yaku);//パスを作る

//これらは不要にする
void sortKaidan(vector<Yaku> *tky, const vector<Yaku> *atky, const Table &table);
void sortPair(vector<Yaku> *tky, const vector<Yaku> *atky, const Table &table);
void sortTanki(vector<Yaku> *tky, const vector<Yaku> *atky, const Table &table);
void sortAllYaku(vector<Yaku> *tky, const vector<Yaku> *atky, const Table &table);
void makeYakuBFrom815(vector<Yaku> *tky, int hands[8][15], const Table &table);
/*
//Yaku配列の添え字だけ抜き取る
void sortKaidan2(vector<int> *parallel, const vector<Yaku> *atky, const Table &table);
void sortPair2(vector<int> *parallel, const vector<Yaku> *atky, const Table &table);
void sortTanki2(vector<int> *parallel, const vector<Yaku> *atky, const Table &table);
void sortAllYaku2(vector<int> *parallel, const vector<Yaku> *atky, const Table &table);
*/

//allYakuからすべての階段を入れる、tableは見ない
void pickKaidan(vector<Yaku> *kaidan, const vector<Yaku> &allYaku);
void pickPair(vector<Yaku> *pair, const vector<Yaku> &allYaku);
void pickTanki(vector<Yaku> *tanki, const vector<Yaku> &allYaku);

//allYakuの役集合からtableに提出可能なものをlegalYakuに入れていく
//makeAllYakuを使った後にこれに渡すことで、全ての合法手集合を作る
void pickAllLegalYaku(vector<Yaku> *legalYaku, const vector<Yaku> &allYaku, const Table &table);
void pickLegalKaidan(vector<Yaku> *legalYaku, const vector<Yaku> &allYaku, const Table &table);
void pickLegalPair(vector<Yaku> *legalYaku, const vector<Yaku> &allYaku, const Table &table);
void pickLegalTanki(vector<Yaku> *legalYaku, const vector<Yaku> &allYaku, const Table &table);

void printYakuVec(const vector<Yaku> &vecYakus);
void makePass(vector<Yaku> *tky);

//役集合を弱い順に並べる（vecCards[0]が最弱となるようにする）
bool isYaku1HigherThanYaku2(const Yaku &c1, const Yaku &c2);
bool isYaku1LowerThanYaku2(const Yaku &c1, const Yaku &c2);
void sortYakuByRank( vector<Yaku> *vecYakus, bool isKakumei );

//void removeLap(vector<Yaku> *vecCard, int64 cdBit);
#endif