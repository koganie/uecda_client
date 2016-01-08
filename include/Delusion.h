#ifndef DELUSION_DEFINE
#define DELUSION_DEFINE

#include <iostream>
#include <vector>
//#include "Table.h"
#include "yaku.h"

using namespace std;

template<typename T> void remove(vector<T>& vector, int index);
void printVC(vector<Card> yaku);

void muddleVector(vector<int> *vec);
void makeDeck(vector<int> *deck, const int dust[8][15]);

void randomCardDevide(int hands[8][15], vector<int> *deck, int num);

class Delusion{
private:
    Table mTable;     //妄想のテーブル情報
    vector< vector<Card> > mYakus;//各プレイヤーの合法手集合
    int mTarget;    //このプレイヤーがあがったら妄想が終わる
    
public:
    Delusion(const Table &table, const int unsubmitted[8][15], const vector<Card> &yaku, int target);
    
    int forwardDelusion(const Card &cd, int *depth);
    
    int startDelusion(int submit_id, int *depth);
    int startDelusion(const Card &submit_cards, int *depth);
};

int selectSubmitCardsByDelusion(Card *select_cards, const Table &table, const vector<Card> &yaku, const int dust[8][15], int hands[8][15]);

#endif