#ifndef PLAYERS_DEFINE
#define PLAYERS_DEFINE

#include <iostream>

using namespace std;

class Players{
public:
    int cards_num[5];//�v���C���[�ԍ�i�̎����D��
    int grades[5];  //�v���C���[�ԍ�i�̐g��i
    int seats[5];   //seats[i]�͐�[i]�ɍ����Ă���v���C���[�ԍ�
    int sekijun[5]; //�v���C���[�ԍ�i�̐Ȕԍ�
    
    int turn;       //���݂̃^�[���� "�v���C���[�ԍ�"
    
    int isPassed;   //�v���C���[�ԍ�i�̓p�X�����Ă��邩
    int isGoaled;   //�v���C���[�ԍ�i�͂������Ă��邩
    
    int getSeats();
    int getCardsNum();
    
    void print();
    void update(int cards[8][15]);
    
    void set(int cards[8][15]);
    
    void init();
    
    void recover();
    
    void simGoal();
    
    void nextTurn();
    
    int simPass();
    
    void simSubmit(const Card &cd);//�J�[�h���o�����㏈��
    
};

#endif