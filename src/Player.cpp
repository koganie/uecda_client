#include <iostream>
#include <cstdio>
#include <cstdlib>
#include"Player.h"

using namespace std;

void Player::setName(int card[8][15]){
    for(int i=0; i<=8; i++){
		name[i] = (char)card[1][i];
	}
	name[9]='\0';
}

void Player::setId(int num){
    id = num;
    sekijun = num;
}

void Players::sekigae( Random *random ){
    //�ȑւ�
    int a = (int)( (id.size()-1) * random->rand() );
    int b = (int)( (id.size()-1) * random->rand() );
    int c = sekijun[a];
    sekijun[a] = sekijun[b];
    sekijun[b] = c;
}

void Players::reset(){
    //�ȑւ��ƁA�����N�̃��Z�b�g
    //sekigae();//�ȑւ��͍s���Ȃ�
    for(int i=0; i<id.size(); i++){
        id[i].mibun = HEIMIN;
    }
}


void Players::setPlayers( int cards[8][15] ){
    int temp[5],temp1[5];
    for(int i=0;i<5;i++){
        id[i].cards_num = cards[6][i]; //�莝���̃J�[�h����
        id[i].mibun = cards[6][5+i];  //�e�v���[���̃����N
        //id[i].seats  = cards[6][10+i]; //��i�ɍ����Ă���v���C���[�ԍ�
        temp[i] = cards[6][10+i];//temp[i]�ɂ͐�i�ɍ����Ă���v���C���[�ԍ�
        id[cards[6][10+i]].sekijun = i;//�v���C���[�ԍ�i�̐Ȕԍ�
    }
    turn = 0;
    //sekijun.push_back(cards[5][3]);//�^�[���ł���v���C���[�ԍ�
    int index = id[cards[5][3]].sekijun;
    for(int i=0;i<5;i++){
        sekijun.push_back( temp[index] );
        index = (index+1)%5;
    }
}

void Player::initCard(){
    //�J�[�h������
    for(int i=0; i<8; i++){
        for(int j=0; j<15; j++){
            cards[i][j] = 0;
        }
    }
    //�������[��
    cards_num = 0;
    //�����폜
    yakus.clear();
}

Player::Player(){
    mibun = HEIMIN;
    passed = false;
}

void Player::printCards(){
    for(int i=0;i<5;i++){
        for(int j=0;j<15;j++){
            cout << cards[i][j] << " ";
        }
        cout << endl;
    }
}

void Player::subtraction(const int card[8][15]){
    int joker_num = 0;
    for(int i=0;i<5;i++){
        for(int j=0;j<15;j++){
            if(card[i][j]==1){
                cards[i][j]=0;
            }
            else if(card[i][j]==2){
                joker_num++;
            }
        }
    }
    if(joker_num==1){
        if(cards[4][2]!=0){
            cards[4][2]=0;
        }else{
            cards[4][1]=0;
        }
    }else if(joker_num==2){
        cards[4][1]=0;
        cards[4][2]=0;
    }
}

int Players::size(){
    return id.size();
}

bool Players::isInequality(){
    if(id[0].mibun != HEIMIN || id[1].mibun != HEIMIN){//�v���C���[�ɐg���������Ă����
        return true;
    }else{
        return false;
    };
}

int Players::mibunId(int num){
    for(int i=0; i<id.size(); i++){
        if(id[i].mibun == num){
            return i;
        }
    }
    return -1;
}

int Players::turnId(){
    return sekijun[turn];
}

int Players::convIDtoSekiNum(int num){
    for(int i=0; i<id.size(); i++){
        if(num==sekijun[i]){
            return i;
        }
    }
    return -1;
}


void Players::nextTurn(){
    int count = 0;
    int first = turn;//���̃v���C���[
    turn = (turn + 1) % sekijun.size();//���ɉ񂷃v���C���[

    for(int i=0; i<5; i++){
        //�p�X���Ă��邩�������Ă���
        if( id[turnId()].passed == true || id[turnId()].cards_num==0 ){
            turn = (turn + 1) % sekijun.size();//����Ɏ�������
        }else{
            //��o�����������A��
            return;
        }
    }
    //�S���ɒ�o���͂Ȃ�����
    turn = first;
}

void Players::recover(){
    for(int i=0;i<id.size();i++){
        id[i].passed = false;
    }
}

void Players::addAgari( int num ){
    agari.push_back( num );
}

void Players::print(){
    for(int i=0; i<sekijun.size(); i++){
        cout << sekijun[i] << " ";
    }
    cout << endl;
    for(int i=0; i<agari.size(); i++){
        cout << agari[i] << " ";
    }
    cout << endl;
    for(int i=0; i<id.size(); i++){
        cout << id[i].passed << " ";
    }
    cout << endl;
    for(int i=0; i<id.size(); i++){
        cout << id[i].cards_num << " ";
    }
    cout << endl;
}

void Players::setCardsNum(){
    for(int i=0; i<id.size(); i++){
        id[i].cards_num = countCard( id[i].cards );
    }
}

void Players::pass(){
    id[turnId()].passed = true;
}

void Players::update(int cards[8][15]){
    //�J�[�h��5�s�ڈȉ������čX�V����
    int index = turnId();
    if(id[index].cards_num == cards[6][index]){//�V������ƕς���Ă��Ȃ� = �p�X����
        id[index].passed = true;
    }else{
        id[index].cards_num = cards[6][index];   //�������X�V����
        if(id[index].cards_num == 0){           //0���ɂȂ�����
            agari.push_back( index );
        }
    }
    if(cards[5][4]==1){//�ꂪ���ꂽ
        for(int i=0;i<5;i++){
            id[i].passed = false;
        }
    }
    
    //turn = cards[5][3];     //�V�����v���C���[�ԍ��ɍX�V
    //turn = id[cards[5][3]].sekijun;
    for(int i=0;i<5;i++){
        if(sekijun[i]==cards[5][3])turn = i;
    }
}

void Players::setup(){
    for(int i=0;i<5;i++){
        Player player;
        id.push_back(player);
    }
}
