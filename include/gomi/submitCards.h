#ifndef SUBMIT_CARD_DEFINE
#define SUBMIT_CARD_DEFINE

#include <vector>
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
int selectSubmitCardsB(int select_cards[8][15], int hands[8][15], const Table &table);
Card selectSubmitCardsBLikeDefault(int select_cards[8][15], int hands[8][15], const Table &table);
void makeAllYaku(vector<Card> *tky, const int hands[8][15]);    
void sortAllYaku(vector<Card> *tky, const vector<Card> *atky, const Table &table);
void sortKaidan2(vector<int> *parallel, const vector<Card> *atky, const Table &table);    
void sortPair2(vector<int> *parallel, const vector<Card> *atky, const Table &table);   
void sortTanki2(vector<int> *parallel, const vector<Card> *atky, const Table &table);    
void sortAllYaku2(vector<int> *parallel, const vector<Card> *atky, const Table &table);
	    
#endif

