#ifndef CARD_DEFINE
#define CARD_DEFINE

#include <iostream>
#include <vector>
#include "common.h"
#include "bit.h"

/*
cardBit�̒��g�Adefine��common.h�ɂ���
�E����
13*3+13-1 = 39+12 = 51
�̍��ڂ�joker�ȊO�̃J�[�h���܂Ƃ܂��Ă���B�̂�
#define CARDBIT(suit, rank)	BITull(suit*13 + (rank-1))
���g����815�z��Ɠ����悤�Ȋ��o��bit���Z���s�����Ƃ��ł���B

52�Ԗڈȍ~�̃r�b�g�͎��̂悤�Ȓ�`�Ńr�b�g���t���O�Ƃ��Ďg���Ă���
#define IS_SPADE3   BITull(0)
#define IS_JUSED	BITull(52)//joker���g���Ă��邩
#define IS_KAIDAN   BITull(53)//�K�i��
#define IS_PAIR     BITull(54)//�y�A��
#define IS_PASS     BITull(55)//�p�X��
#define IS_8GIRI    BITull(56)//8�؂肩
#define IS_NUM(num) BITull(56+num)//�J�[�h�����͉�����?1�ȏオ����

*/

class Card{
private:
    int64 mCardBit;       //�J�[�h�̃r�b�g�\��
    int mCards[8][15];  //�J�[�h�̔z��\��
    
    //�J�[�h�̓���
    //bit�Əd��������̂���������̂ł���܂�g��Ȃ�����
    //��{�I�ɂ�bool is�`()���g���Ė₢���킹��΂悢
    int mKaidan;        //�K�i
    int mPair;          //�y�A
    int mTanki;         //�P�R
    int mPass;          //�p�X
    int mJoker;         //�W���[�J�[�P�R
    
    //����p
    int mKakumei;       //�v���������N����
    //int mShibari;       //���΂�
    int m8giri;         //8�؂���N����
    
public:
    int mNum;           //����
    int mRankR;         //�����N�i�����j
    int mRankL;         //�����N�i�����j
    
    int mSuits;         //�X�[�g
    int mJposSuit;
    int mJposRank;
    bool mSpe3;
    
    bool isKaidan() const;//�K�i�Ȃ�True�A�ȉ����l��
    bool isPair() const;
    bool isTanki() const;
    bool isJTanki() const;
    bool isJUsed() const;
    bool isKakumei() const;
    //bool isShibari() const;
    bool is8giri() const;
    bool isSpade3() const;
    bool isPass() const;
    
    int64 getCardBit() const;//�J�[�h�r�b�g��Ԃ�
    void printBit() const;
    void printBit2() const;
    void printBit3() const;
	
	Card();
    
    //�R���X�g���N�^
    //������J�[�h�r�b�g�A�X�[�g�A�����A�����̃����N�A�E���̃����N�i�K�i�Ajoker�P�R�̂Ƃ��ȊO�͓��������j�A�g��joker�̃X�[�g�A�g��joker�̃����N�i�g��Ȃ��Ƃ���-1�j
    Card(int64 cd, int suits, int num, int rank, int rank2, int jps, int jpr);
    //joker�g��Ȃ��R���X�g���N�^��p�ӂ��Ă�����
    
    //��������
    void clear();
    void init();
    void demoPass();
    
    //�Ⴂ���悭�킩���̂ŉ�������
    void setBit(int src[8][15]);//[8][15]�z�񂩂�����i�[���� //��D�̉�͗p�ł���
    void set815ToBit(int src[8][15]);//815�z���bit�ɕϊ�����
    void setBitTo815(int dest[8][15]) const;//bit��815�z��ɕϊ�����
};

void removeLap(std::vector<Card> *vecCard, int64 cdBit);
void removePass(std::vector<Card> *vecCard);
bool isCard1WeakerThanCard2WhenNotKakumei(const Card &c1, const Card &c2);
bool isCard1WeakerThanCard2WhenKakumei(const Card &c1, const Card &c2);
int selectBigCards(Card *card, const std::vector<Card> &vecCard);
//int selectLowCards(const std::vector<Card> &vecCard);

#endif