#ifndef CARD_DEFINE
#define CARD_DEFINE

#include <iostream>
#include <vector>
#include "common.h"

class Card{
private:
    int64 mCardBit;       //�J�[�h�̃r�b�g�\��
    int mCards[8][15];  //�J�[�h�̔z��\��
    
    //�J�[�h�̓���
    int mKaidan;        //�K�i
    int mPair;          //�y�A
    int mTanki;         //�P�R
    int mPass;          //�p�X
    int mJoker;         //�W���[�J�[�P�R
    
    //����p
    int mKakumei;       //�v���������N����
    int mShibari;       //���΂�
    int m8giri;         //8�؂���N����
    
public:
    int mNum;           //����
    int mRankR;         //�����N�i�����j
    int mRankL;         //�����N�i�����j
    
    int mSuits;         //�X�[�g
    int mJposSuit;
    int mJposRank;
    bool mSpe3;
    
    bool isKaidan() const;
    bool isPair() const;
    bool isTanki() const;
    bool isJTanki() const;
    bool isKakumei() const;
    //bool isShibari() const;
    bool is8giri() const;
    bool isSpade3() const;
    bool isPass() const;
    int64 getCardBit() const;
    void printBit() const;
    void printBit2() const;
    void printBit3() const;
	
	Card();
    
    Card(int64 cd, int suits, int num, int rank, int rank2, int jps, int jpr);
    
    void clear();
    void init();
    void demoPass();
    
    void setBit(int src[8][15]);//[8][15]�z�񂩂�����i�[���� //��D�̉�͗p�ł���
    void set815ToBit(int src[8][15]);//815�z���bit�ɕϊ�����
    void setBitTo815(int dest[8][15]) const;//bit��815�z��ɕϊ�����
};

void removeLap(std::vector<Card> *vecCard, int64 cdBit);
void removePass(std::vector<Card> *vecCard);
bool compYakuRankL(const Card &c1, const Card &c2);
bool compYakuRankR(const Card &c1, const Card &c2);
int selectBigCards(const std::vector<Card> &vecCard);
int selectLowCards(const std::vector<Card> &vecCard);

#endif