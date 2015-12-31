#ifndef SUBMIT_CARD_DEFINE
#define SUBMIT_CARD_DEFINE

#include <vector>
//#include "mydef.h"
//#include "mt19937ar.h"
#include "Table.h"

using namespace std;

void makeKaidanFrom815(vector<Card> *tky, const int hands[8][15]);
void makePairFrom815(vector<Card> *tky, const int hands[8][15]);
void makeTankiFrom815(vector<Card> *tky, const int hands[8][15]);
void makePass(vector<Card> *tky);
void sortKaidan(vector<Card> *tky, const vector<Card> *atky, const Table &table);
void sortPair(vector<Card> *tky, const vector<Card> *atky, const Table &table);
void sortTanki(vector<Card> *tky, const vector<Card> *atky, const Table &table);
void makeYakuBFrom815(vector<Card> *tky, int hands[8][15], const Table &table);
void makeAllYaku(vector<Card> *tky, const int hands[8][15]);    
void sortAllYaku(vector<Card> *tky, const vector<Card> *atky, const Table &table);

//Card”z—ñ‚Ì“Y‚¦Žš‚¾‚¯”²‚«Žæ‚é
void sortKaidan2(vector<int> *parallel, const vector<Card> *atky, const Table &table);
void sortPair2(vector<int> *parallel, const vector<Card> *atky, const Table &table);
void sortTanki2(vector<int> *parallel, const vector<Card> *atky, const Table &table);
void sortAllYaku2(vector<int> *parallel, const vector<Card> *atky, const Table &table);
//
void pickKaidan(vector<Card> *parallel, const vector<Card> &atky);
void pickPair(vector<Card> *parallel, const vector<Card> &atky);
void pickTanki(vector<Card> *parallel, const vector<Card> &atky);
//
void pickLegalKaidan(vector<Card> *parallel, const vector<Card> &atky, const Table &table);
void pickLegalPair(vector<Card> *parallel, const vector<Card> &atky, const Table &table);
void pickLegalTanki(vector<Card> *parallel, const vector<Card> &atky, const Table &table);
void pickAllLegalYaku(vector<Card> *parallel, const vector<Card> &atky, const Table &table);

void sortYakuByRank( vector<Card> *vecCards, bool isKakumei );
#endif

