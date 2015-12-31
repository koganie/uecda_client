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

void randomCardDevide(int hands[5][8][15], vector<int> *deck, int target, int num);

class Delusion{
private:
    Table mTable;     //妄想のテーブル情報
    vector< vector<Card> > mYakus;//各プレイヤーの合法手集合
    int mTarget;
    
public:
    Delusion(const Table &table, const int unsubmitted[8][15], const vector<Card> &yaku, int target);
    
    Card submitVirtualDefault();
    
    void removeYaku(int64 cdBit);

    void updateSimTable(const Card &cd);
    
    int forwardDelusion(const Card &cd, int *depth);
    
    int startDelusion(int submit_id, int *depth);
    int startDelusion(const Card &submit_cards, int *depth);
};


#endif