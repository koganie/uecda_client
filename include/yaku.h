#ifndef SUBMIT_CARD_DEFINE
#define SUBMIT_CARD_DEFINE

#include <vector>
#include "Table.h"

using namespace std;

void makeAllYaku(vector<Card> *allYaku, const int hands[8][15]);//���ׂĂ̖������
void makeKaidanFrom815(vector<Card> *yaku, const int hands[8][15]);//�K�i�����
void makePairFrom815(vector<Card> *yaku, const int hands[8][15]);//�y�A�����
void makeTankiFrom815(vector<Card> *yaku, const int hands[8][15]);//�P�R�����
void makePass(vector<Card> *yaku);//�p�X�����

//�����͕s�v�ɂ���
void sortKaidan(vector<Card> *tky, const vector<Card> *atky, const Table &table);
void sortPair(vector<Card> *tky, const vector<Card> *atky, const Table &table);
void sortTanki(vector<Card> *tky, const vector<Card> *atky, const Table &table);
void sortAllYaku(vector<Card> *tky, const vector<Card> *atky, const Table &table);
void makeYakuBFrom815(vector<Card> *tky, int hands[8][15], const Table &table);
/*
//Card�z��̓Y���������������
void sortKaidan2(vector<int> *parallel, const vector<Card> *atky, const Table &table);
void sortPair2(vector<int> *parallel, const vector<Card> *atky, const Table &table);
void sortTanki2(vector<int> *parallel, const vector<Card> *atky, const Table &table);
void sortAllYaku2(vector<int> *parallel, const vector<Card> *atky, const Table &table);
*/

//allYaku���炷�ׂĂ̊K�i������Atable�͌��Ȃ�
void pickKaidan(vector<Card> *kaidan, const vector<Card> &allYaku);
void pickPair(vector<Card> *pair, const vector<Card> &allYaku);
void pickTanki(vector<Card> *tanki, const vector<Card> &allYaku);

//allYaku�̖��W������table�ɒ�o�\�Ȃ��̂�legalYaku�ɓ���Ă���
//makeAllYaku���g������ɂ���ɓn�����ƂŁA�S�Ă̍��@��W�������
void pickAllLegalYaku(vector<Card> *legalYaku, const vector<Card> &allYaku, const Table &table);
void pickLegalKaidan(vector<Card> *legalYaku, const vector<Card> &allYaku, const Table &table);
void pickLegalPair(vector<Card> *legalYaku, const vector<Card> &allYaku, const Table &table);
void pickLegalTanki(vector<Card> *legalYaku, const vector<Card> &allYaku, const Table &table);

void printCardVec(const vector<Card> &vecCards);
void makePass(vector<Card> *tky);

//���W�����ア���ɕ��ׂ�ivecCards[0]���Ŏ�ƂȂ�悤�ɂ���j
void sortYakuByRank( vector<Card> *vecCards, bool isKakumei );
#endif

