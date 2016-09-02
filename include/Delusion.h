#ifndef DELUSION_DEFINE
#define DELUSION_DEFINE

#include <iostream>
#include <vector>
#include "Table.h"
#include "Yaku.h"
#include "Random.h"

using namespace std;

template<typename T> void remove(vector<T>& vector, int index);
void printVC(vector<Yaku> yaku);


void makeDeck(vector<int> *deck, const int dust[8][15]);
void makeDeck(vector<int> *deck, const int64 dust);


class Delusion{
private:
    Table mTable;     //�ϑz�̃e�[�u�����
    Players mPlayers;    //�v���C���[
    vector< vector<Yaku> > mYakus;//�e�v���C���[�̍��@��W��
    int mTarget;    //���̃v���C���[������������ϑz���I���
    Random *random;
    
    void muddleVector(vector<int> *vec);
    void randomCardDevide(int hands[8][15], vector<int> *deck, int num);

public:
    Delusion(const Table &table, const int unsubmitted[8][15], const Players &players, const vector<Yaku> &yaku, Random *r, int target);
    Delusion(const Table &table, const int64 unsubmitted, const Players &players, const vector<Yaku> &yaku, Random *r, int target);
    
    int forwardDelusion(const Yaku &cd, int *depth);
    
    int startDelusion(int submit_id, int *depth);
    int startDelusion(const Yaku &submit_cards, int *depth);
    
    void simSubmit( const Yaku &yaku );
    void purge();
    void nextTurn();
    bool isBaAlive();
};

int selectSubmitCardsByDelusion(Yaku *select_cards, const Table &table, const Players &players, const vector<Yaku> &yaku, const int dust[8][15], int hands[8][15]);
int selectSubmitCardsByDelusion(Yaku *select_cards, const Table &table, const Players &players, const vector<Yaku> &yaku, const int64 gomi, int hands[8][15]);

#endif