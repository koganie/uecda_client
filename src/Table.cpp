#include "Table.h"

using namespace std;

Table::Table(){
}

void Table::firstGame(int cards[8][15]){//�Q�[���̏�����
    baBit = 0;
    mNum = 0;
    mRank = 0;
    mSuits = 0;
    setOnset(1);//���ɃZ�b�g
    mCard.init();//�J�[�h�͍폜
    mPlayers.set(cards);//�J�[�h��5�s�ڈȍ~�̏��ŃZ�b�g
}

void Table::purge(){//��𗬂��i�p��\�����킩��Ȃ������j
    baBit &= (IS_BA_KAKUMEI);   //�v����Ԃ͏����邱�Ƃ͂Ȃ�
    baBit |= (IS_BA_ONSET);     //���ɂ���
    mNum = 0;
    mRank = 0;
    mSuits = 0;
    mCard.clear();      //�J�[�h������
    mPlayers.recover(); //�v���C���[�̃p�X��Ԃ���������
}
    
void Table::setBafuda(int cards[8][15]){//��D��ۑ��i��D����ǂݎ�����̂����X�V����j
    mCard.clear();
    mCard.setBit(cards);
    
    if( mCard.isKakumei() ) revKakumei();//�J�[�h���v���𔭐�������Ȃ��Ԃ𔽓]����
    setKaidan( mCard.isKaidan() );      //�K�i
    setPair( mCard.isPair() );          //�y�A
    
    mNum = mCard.mNum;                  //����
    if(mNum==1){//�J�[�h����            //�P�R
        setTanki( 1 );
        //setJoker( mCard.isJoker() );    //joker�P�R
        setJTanki( mCard.isJTanki() );    //joker�P�R
    }else if(mNum==0){//�����炭�����͂߂����ɂ͂���Ȃ�
        setOnset( 1 );
    }
    if( isKakumei() ){                  //�����A�v���Ȃ獶�[���A�ʏ�Ȃ�E�[��
        mRank = mCard.mRankL;//���[
    }else{
        mRank = mCard.mRankR;//�E�[
    }
    
    mSuits = mCard.mSuits;//�X�[�c
}
    
void Table::setBaInfo(int cards[8][15]){//���ʎ󂯎��͎̂�D�ł���A5�s�ڈȉ��̏�̏����X�V����
    if(cards[5][4]>0)   baBit |=  IS_BA_ONSET;  //���
    else                baBit &= ~IS_BA_ONSET;
    if(cards[5][6]>0)   baBit |=  IS_BA_KAKUMEI;//�v��
    else                baBit &= ~IS_BA_KAKUMEI;
    if(cards[5][7]>0)   baBit |=  IS_BA_SHIBARI;//����
    else                baBit &= ~IS_BA_SHIBARI;
	
    if( isOnset() ){//��𗬂�
        purge();
    }
	mPlayers.update(cards);
}
    
void Table::print(){
    std::cout << "ON" << isOnset() 
     <<", KA" << isKaidan()
     <<", PA" << isPair()
     << ", TN" << isTanki() 
     << ", NU" << mNum << ", RN" << mRank << std::endl;
    std::cout << "KK" << isKakumei() 
    << ", SH"<< isShibari() 
    << ", SS " << mSuits << std::endl;
    std::cout << "bafuda" << std::endl;
    //int temp[8][15]={{0}};
    mCard.printBit2();
    mPlayers.print();
}

bool Table::isTurn(int player_num){
    return whoseTurn() == player_num;
}

void Table::simGoal(){
    //���݂̐l�����������Ƃ��̍X�V
    mPlayers.simGoal();
}

int Table::simPass(){
    //���݂̐l���p�X�����Ƃ��̍X�V
    return mPlayers.simPass();
}
    
void Table::sim8giri(Card &cd){
    //���݂̐l��8�؂�������Ƃ��̍X�V
    mPlayers.simSubmit(cd);//�v���C���[���X�V
    purge();//��𗬂�
}
    
void Table::simSubmit(const Card &cd){
    //�J�[�hcd���o�������̍X�V
	//cout << "submit " << endl;
	//cd.printBit();
    setOnset(0);            //onset����
    if(cd.mNum==0){         //�p�X������
        if(simPass()==1){   //�S���ɒ�o�����Ȃ��Ȃ�
            purge();        //�ꂪ�����
        }
    }
    else{//�Ȃ�炩�o����
        mPlayers.simSubmit(cd);//�v���C���[���̍X�V
        
        if(cd.is8giri()==1){//8�؂肾����
            purge();        //��𗬂�
        }else{
            mCard = cd;     //��D��u��������
            setKaidan( mCard.isKaidan() );
            setPair( mCard.isPair() );
            
            mNum = mCard.mNum;
            if(mNum==1){//�J�[�h����
                setTanki( 1 );
                //setJoker( mCard.isJoker() );
                setJTanki( mCard.isJTanki() );
            }
            if( isKakumei() ){
                mRank = mCard.mRankL;//���[
            }else{
                mRank = mCard.mRankR;//�E�[
            }
            
            mSuits = mCard.mSuits;//�X�[�c
        }
    }
    #ifdef DEBUG
    cout << "table after submit cd" << endl;
	print();
    #endif
	//exit(1);
}
