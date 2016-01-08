#ifndef SUBMIT_CARD_DEFINE
#define SUBMIT_CARD_DEFINE

#include <vector>
#include "Table.h"

using namespace std;

void makeAllYaku(vector<Card> *allYaku, const int hands[8][15]);//すべての役を作る
void makeKaidanFrom815(vector<Card> *yaku, const int hands[8][15]);//階段を作る
void makePairFrom815(vector<Card> *yaku, const int hands[8][15]);//ペアを作る
void makeTankiFrom815(vector<Card> *yaku, const int hands[8][15]);//単騎を作る
void makePass(vector<Card> *yaku);//パスを作る

//これらは不要にする
void sortKaidan(vector<Card> *tky, const vector<Card> *atky, const Table &table);
void sortPair(vector<Card> *tky, const vector<Card> *atky, const Table &table);
void sortTanki(vector<Card> *tky, const vector<Card> *atky, const Table &table);
void sortAllYaku(vector<Card> *tky, const vector<Card> *atky, const Table &table);
void makeYakuBFrom815(vector<Card> *tky, int hands[8][15], const Table &table);
/*
//Card配列の添え字だけ抜き取る
void sortKaidan2(vector<int> *parallel, const vector<Card> *atky, const Table &table);
void sortPair2(vector<int> *parallel, const vector<Card> *atky, const Table &table);
void sortTanki2(vector<int> *parallel, const vector<Card> *atky, const Table &table);
void sortAllYaku2(vector<int> *parallel, const vector<Card> *atky, const Table &table);
*/

//allYakuからすべての階段を入れる、tableは見ない
void pickKaidan(vector<Card> *kaidan, const vector<Card> &allYaku);
void pickPair(vector<Card> *pair, const vector<Card> &allYaku);
void pickTanki(vector<Card> *tanki, const vector<Card> &allYaku);

//allYakuの役集合からtableに提出可能なものをlegalYakuに入れていく
//makeAllYakuを使った後にこれに渡すことで、全ての合法手集合を作る
void pickAllLegalYaku(vector<Card> *legalYaku, const vector<Card> &allYaku, const Table &table);
void pickLegalKaidan(vector<Card> *legalYaku, const vector<Card> &allYaku, const Table &table);
void pickLegalPair(vector<Card> *legalYaku, const vector<Card> &allYaku, const Table &table);
void pickLegalTanki(vector<Card> *legalYaku, const vector<Card> &allYaku, const Table &table);

void printCardVec(const vector<Card> &vecCards);
void makePass(vector<Card> *tky);

//役集合を弱い順に並べる（vecCards[0]が最弱となるようにする）
void sortYakuByRank( vector<Card> *vecCards, bool isKakumei );
#endif

