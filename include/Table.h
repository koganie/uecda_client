#ifndef TABLE_DEFINE
#define TABLE_DEFINE

#include "Card.h"
#include "Players.h"

class Table{
private:
    uint32_t baBit;//��̏���32bit
	//�E����
    // 0:���
	// 1:�K�i
	// 2:�y�A
	// 3:�P�R
	// 4:�v��
	// 5:����
	// 6:�W���[�J�[�P�R
	
public:
    bool isOnset() const;
    bool isKaidan() const;
    bool isPair() const;
    bool isTanki() const;
    bool isKakumei() const;
    bool isShibari() const;
    bool isJTanki() const;
    void setOnset(bool flag);//���t���O���Z�b�g����
    void setKakumei(bool flag);//�v���t���O���Z�b�g����
    void revKakumei();//�v���𔽓]����
    void setKaidan(bool flag);//�K�i�t���O���Z�b�g����
    void setPair(bool flag);//�y�A�t���O���Z�b�g����
    void setTanki(bool flag);//�P�R�t���O���Z�b�g����
    void setShibari(bool flag);//����t���O���Z�b�g����
    void setJTanki(bool flag);//�W���[�J�[�P�R�t���O���Z�b�g����
	int whoseTurn() const;//���݂̃^�[���̐l�̃v���C���[�ԍ���Ԃ�
    
    int mNum;
    int mRank;
    //int mRankR;         //�����N�i�����j
    //int mRankL;         //�����N�i�����j
    int mSuits;
    Card mCard;         //��D
    Players mPlayers;   //�e�v���C���[�̏��
    
    Table();
    
    void firstGame(int cards[8][15]);
    void purge();
    void setBafuda(int cards[8][15]);
    void setBaInfo(int cards[8][15]);
    void print() const;
    
    bool isTurn(int player_num);
    
    /* �ȉ��V�~�����[�V�����p�̊֐�      */
    /* �ʏ��table�̍X�V�Ɏg�����Ƃ͂Ȃ� */
    /* �T�[�o�I�Ȗ������ɂȂ��̂ł��� */
    
    void simGoal();
    int simPass();
    void sim8giri(Card &cd);
    void simSubmit(const Card &cd);
};


#endif