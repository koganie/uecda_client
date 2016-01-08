#include "Table.h"

using namespace std;

Table::Table(){
}

bool Table::isOnset() const{
    return (baBit&(IS_BA_ONSET))!=0;//空場か？
}
bool Table::isKaidan() const{
    return (baBit&(IS_BA_KAIDAN))!=0;//階段か？
}
bool Table::isPair() const{
    return (baBit&(IS_BA_PAIR))!=0;//ペアか？
}
bool Table::isTanki() const{
    return (baBit&(IS_BA_TANKI))!=0;//単騎か？
}
bool Table::isKakumei() const{
    return (baBit&(IS_BA_KAKUMEI))!=0;//革命か？
}
bool Table::isShibari() const{
    return (baBit&(IS_BA_SHIBARI))!=0;//縛りか？
}
bool Table::isJTanki() const{
    return (baBit&(IS_BA_JOKER))!=0;//ジョーカー単騎か？
}
void Table::setOnset(bool flag){//空場フラグをセットする
    if(flag)    baBit |=  IS_BA_ONSET;
    else        baBit &= ~IS_BA_ONSET;
}
void Table::setKakumei(bool flag){//革命フラグをセットする
    if(flag)    baBit |=  IS_BA_KAKUMEI;
    else        baBit &= ~IS_BA_KAKUMEI;
}
void Table::revKakumei(){//革命を反転する
    if(isKakumei()) setKakumei(0);//革命状態であるなら戻す
    else            setKakumei(1);//通常状態であるなら立てる
}
void Table::setKaidan(bool flag){//階段フラグをセットする
    if(flag)    baBit |=  IS_BA_KAIDAN;
    else        baBit &= ~IS_BA_KAIDAN;
}
void Table::setPair(bool flag){//ペアフラグをセットする
    if(flag)    baBit |=  IS_BA_PAIR;
    else        baBit &= ~IS_BA_PAIR;
}
void Table::setTanki(bool flag){//単騎フラグをセットする
    if(flag)    baBit |=  IS_BA_TANKI;
    else        baBit &= ~IS_BA_TANKI;
}
void Table::setShibari(bool flag){//縛りフラグをセットする
    if(flag)    baBit |=  IS_BA_SHIBARI;
    else        baBit &= ~IS_BA_SHIBARI;
}
void Table::setJTanki(bool flag){//ジョーカー単騎フラグをセットする
    if(flag)    baBit |=  IS_BA_JOKER;
    else        baBit &= ~IS_BA_JOKER;
}

int Table::whoseTurn() const{//現在のターンの人のプレイヤー番号を返す
    return mPlayers.turn;
}

void Table::firstGame(int cards[8][15]){//ゲームの初期化
    baBit = 0;
    mNum = 0;
    mRank = 0;
    mSuits = 0;
    setOnset(1);//空場にセット
    mCard.init();//カードは削除
    mPlayers.set(cards);//カードの5行目以降の情報でセット
}

void Table::purge(){//場を流す（英語表現がわからなかった）
    baBit &= (IS_BA_KAKUMEI);   //革命状態は消えることはない
    baBit |= (IS_BA_ONSET);     //空場にする
    mNum = 0;
    mRank = 0;
    mSuits = 0;
    mCard.clear();      //カードを消す
    mPlayers.recover(); //プレイヤーのパス状態を解除する
}
    
void Table::setBafuda(int cards[8][15]){//場札を保存（場札から読み取れるものだけ更新する）
    mCard.clear();
    mCard.setBit(cards);
    
    if( mCard.isKakumei() ) revKakumei();//カードが革命を発生させるなら状態を反転する
    setKaidan( mCard.isKaidan() );      //階段
    setPair( mCard.isPair() );          //ペア
    
    mNum = mCard.mNum;                  //枚数
    if(mNum==1){//カード枚数            //単騎
        setTanki( 1 );
        //setJoker( mCard.isJoker() );    //joker単騎
        setJTanki( mCard.isJTanki() );    //joker単騎
    }else if(mNum==0){//おそらくここはめったにはいらない
        setOnset( 1 );
    }
    if( isKakumei() ){                  //強さ、革命なら左端を、通常なら右端を
        mRank = mCard.mRankL;//左端
    }else{
        mRank = mCard.mRankR;//右端
    }
    
    mSuits = mCard.mSuits;//スーツ
}
    
void Table::setBaInfo(int cards[8][15]){//普通受け取るのは手札であり、5行目以下の場の情報を更新する
    if(cards[5][4]>0)   baBit |=  IS_BA_ONSET;  //空場
    else                baBit &= ~IS_BA_ONSET;
    if(cards[5][6]>0)   baBit |=  IS_BA_KAKUMEI;//革命
    else                baBit &= ~IS_BA_KAKUMEI;
    if(cards[5][7]>0)   baBit |=  IS_BA_SHIBARI;//縛り
    else                baBit &= ~IS_BA_SHIBARI;
	
    if( isOnset() ){//場を流す
        purge();
    }
	mPlayers.update(cards);
}
    
void Table::print() const{
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
    //現在の人があがったときの更新
    mPlayers.simGoal();
}

int Table::simPass(){
    //現在の人がパスしたときの更新
    return mPlayers.simPass();
}
    
void Table::sim8giri(Card &cd){
    //現在の人が8切りをしたときの更新
    mPlayers.simSubmit(cd);//プレイヤー情報更新
    purge();//場を流す
}
    
void Table::simSubmit(const Card &cd){
    //カードcdを提出した時の更新
	//cout << "submit " << endl;
	//cd.printBit();
    
    if(cd.mNum==0){         //パスをした
        if(simPass()==1){   //全員に提出権がなくなる
            purge();        //場が流れる
        }
    }
    else{//なんらか出した
        
        mPlayers.simSubmit(cd);//プレイヤー情報の更新（手札枚数・あがり）
        if(mCard.isKakumei())revKakumei();//革命を起こしたら反転
        
        if(cd.is8giri()==1){//8切りだった
            purge();        //場を流す
        }else{
            setOnset(0);            //onset解除
            
            mCard = cd;     //場札を置き換える
            
            setKaidan( mCard.isKaidan() );
            setPair( mCard.isPair() );
            
            mNum = mCard.mNum;
            if(mNum==1){//カード枚数
                setTanki( 1 );
                //setJoker( mCard.isJoker() );
                setJTanki( mCard.isJTanki() );
            }
            if( isKakumei() ){
                mRank = mCard.mRankL;//左端
            }else{
                mRank = mCard.mRankR;//右端
            }
            
            mSuits = mCard.mSuits;//スーツ
        }
    }
    #ifdef DEBUG
    cout << "table after submit cd" << endl;
	print();
    #endif
	//exit(1);
}
