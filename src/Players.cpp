#include <iostream>

#include "Card.h"
#include "Table.h"
#include "Players.h"

using namespace std;

int Players::getSeats(){
    //���݂̃^�[���̐l�������Ă���Ȕԍ�
    for(int i=0;i<5;i++){
        if(seats[i]==turn)return i;
    }
    return -1;
}

int Players::getCardsNum(){
    //���݂̃^�[���̐l�̎����D��
    return cards_num[turn];
}

void Players::print() const{
    int i;
    printf("num=");
    for(i=0;i<5;i++)printf("%d,", cards_num[i]);
    printf("\ngra=");
    for(i=0;i<5;i++)printf("%d,", grades[i]);
    printf("\nseat=");
    for(i=0;i<5;i++)printf("%d,", seats[i]);
    
    printf("\npass=%d ", isPassed);
    for(i=0;i<5;i++)printf("%d,", (isPassed&(1<<i))!=0 );
    
    printf("\ngoal=%d ", isGoaled);
    for(i=0;i<5;i++)printf("%d,", (isGoaled&(1<<i))!=0 );
    
    printf("\nturn=%d \n", turn);
}

void Players::update(int cards[8][15]){
    //�J�[�h��5�s�ڈȉ������čX�V����
    if(cards_num[turn] == cards[6][turn]){//�V������ƕς���Ă��Ȃ� = �p�X����
        isPassed |= (1 << turn);
    }else{
        cards_num[turn] = cards[6][turn];   //�������X�V����
        if(cards_num[turn] == 0){           //0���ɂȂ�����
            isGoaled |= (1 << turn);        //��������I
        }
    }
    /*
	cout <<"cn" << endl;
	for(int i=0;i<5;i++){
		cout << cards_num[i] <<":"<< cards[6][i]<<endl;
	}
    */
    turn = cards[5][3];     //�V�����v���C���[�ԍ��ɍX�V
}
    
void Players::set(int cards[8][15]){
    //�Q�[���J�n���Ɋe�v���C���[�̏����i�[����
    for(int i=0;i<5;i++){
        cards_num[i] = cards[6][i]; //�莝���̃J�[�h����
        grades[i] = cards[6][5+i];  //�e�v���[���̃����N
        seats[i]  = cards[6][10+i]; //��i�ɍ����Ă���v���C���[�ԍ�
        sekijun[cards[6][10+i]] = i;//�v���C���[�ԍ�i�̐Ȕԍ�
    }
    isPassed = 0;
    isGoaled = 0;
    turn = cards[5][3];//�^�[���ł���v���C���[�ԍ�
}
    
void Players::init(){//������
    turn = -1;
    isPassed = 0;
    isGoaled = 0;
}

void Players::recover(){//�p�X���畜�A
    isPassed = 0;
}
    
void Players::simGoal(){
    isGoaled |= (1 << turn);
}

void Players::nextTurn(){
    int nowSeki = sekijun[turn];//���̐Ȕԍ�
    nowSeki = (nowSeki+1)%5;    //1�Ȃ����炷
    
    int GP = isGoaled|isPassed; //������܂��̓p�X�̏W��
    if( GP == (BITi(5)-1) ){    //�݂�Ȃɒ�o�����Ȃ��Ȃ���
        recover();//�p�X�𕜋A������
        GP = isGoaled;
    }
    while( (GP&BITi(seats[nowSeki]))!=0 ){//���łɂ������Ă���
        nowSeki = (nowSeki+1)%5;    //1�Ȃ����炷
    }
    
    //std::cout << "old turn is " << turn  << std::endl;
    turn = seats[nowSeki];
    //std::cout << "new turn is " << turn  << std::endl;
}

int Players::simPass(){
    isPassed |= (1 << turn);
    if( (isPassed|isGoaled) == (1<<5)-1 ){//�S���ɒ�o�����Ȃ��Ȃ�
        isPassed = 0;
        return 1;
    }else{
        nextTurn();
    }
    return 0;
}

void Players::simSubmit(const Card &cd){//�J�[�h���o�����㏈��
    //�p�X�͂����ɂ͗��Ȃ�
    
    cards_num[turn] = cards_num[turn] - cd.mNum;//�J�[�h��������������
    if(cards_num[turn]==0){//��������
        isGoaled |= BITi(turn);
    }else if(cards_num[turn]<0){
        printf("okasisi!!\n");
        printf("%d %d\n", cards_num[turn], cd.mNum);
        cd.printBit();
        cd.printBit3();
        exit(1);
    }
    
    if(cd.is8giri()==0){//8�؂�ł͂Ȃ�
        nextTurn();
    }
    else{//8�؂肾����
        isPassed = 0;//�p�X�𕜋A������
        if(cards_num[turn]==0){//�������Ă����玟�̐l
            nextTurn();
        }
    }
}
