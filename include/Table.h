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
    inline bool isOnset() const{
        return (baBit&(IS_BA_ONSET))!=0;//��ꂩ�H
    }
    inline bool isKaidan() const{
        return (baBit&(IS_BA_KAIDAN))!=0;//�K�i���H
    }
    inline bool isPair() const{
        return (baBit&(IS_BA_PAIR))!=0;//�y�A���H
    }
    inline bool isTanki() const{
        return (baBit&(IS_BA_TANKI))!=0;//�P�R���H
    }
    inline bool isKakumei() const{
        return (baBit&(IS_BA_KAKUMEI))!=0;//�v�����H
    }
    inline bool isShibari() const{
        return (baBit&(IS_BA_SHIBARI))!=0;//���肩�H
    }
    inline bool isJTanki() const{
        return (baBit&(IS_BA_JOKER))!=0;//�W���[�J�[�P�R���H
    }
    inline void setOnset(bool flag){//���t���O���Z�b�g����
        if(flag)    baBit |=  IS_BA_ONSET;
        else        baBit &= ~IS_BA_ONSET;
    }
    inline void setKakumei(bool flag){//�v���t���O���Z�b�g����
        if(flag)    baBit |=  IS_BA_KAKUMEI;
        else        baBit &= ~IS_BA_KAKUMEI;
    }
    inline void revKakumei(){//�v���𔽓]����
        if(isKakumei()) setKakumei(0);//�v����Ԃł���Ȃ�߂�
        else            setKakumei(1);//�ʏ��Ԃł���Ȃ痧�Ă�
    }
    inline void setKaidan(bool flag){//�K�i�t���O���Z�b�g����
        if(flag)    baBit |=  IS_BA_KAIDAN;
        else        baBit &= ~IS_BA_KAIDAN;
    }
    inline void setPair(bool flag){//�y�A�t���O���Z�b�g����
        if(flag)    baBit |=  IS_BA_PAIR;
        else        baBit &= ~IS_BA_PAIR;
    }
    inline void setTanki(bool flag){//�P�R�t���O���Z�b�g����
        if(flag)    baBit |=  IS_BA_TANKI;
        else        baBit &= ~IS_BA_TANKI;
    }
    inline void setShibari(bool flag){//����t���O���Z�b�g����
        if(flag)    baBit |=  IS_BA_SHIBARI;
        else        baBit &= ~IS_BA_SHIBARI;
    }
    inline void setJTanki(bool flag){//�W���[�J�[�P�R�t���O���Z�b�g����
        if(flag)    baBit |=  IS_BA_JOKER;
        else        baBit &= ~IS_BA_JOKER;
    }
	
    inline int whoseTurn() const{//���݂̃^�[���̐l�̃v���C���[�ԍ���Ԃ�
        return mPlayers.turn;
    }
    int mNum;
    int mRank;
    int mRankR;         //�����N�i�����j
    int mRankL;         //�����N�i�����j
    int mSuits;
    Card mCard;         //��D
    Players mPlayers;   //�e�v���C���[�̏��
    
    Table();
    
    void firstGame(int cards[8][15]);
    void purge();
    void setBafuda(int cards[8][15]);
    void setBaInfo(int cards[8][15]);
    void print();
    
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