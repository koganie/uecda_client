#include "Table.h"
#include <iostream>

using namespace std;

Table::Table(){
    baBit = 0ull;
    /*
    mNum = 0;
    mRankR = 0;
    mRankL = 0;
    mSuits = 0;
    */
    setOnset(1);//空場にセット
    mBafuda.init();//カードは削除
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
    //return (baBit&(IS_BA_TANKI))!=0;//単騎か？
    return mBafuda.isTanki();
}
bool Table::isKakumei() const{
    return (baBit&(IS_BA_KAKUMEI))!=0;//革命か？
}
bool Table::isShibari() const{
    return (baBit&(IS_BA_SHIBARI))!=0;//縛りか？
}
bool Table::isJTanki() const{
    return mBafuda.isTanki()&&(baBit&(IS_BA_JOKER))!=0;//ジョーカー単騎か？
}
bool Table::is11back() const{
    return (baBit&(IS_BA_11BACK))!=0;//11バックか？
}
bool Table::isChangePhase() const{
    return (baBit&(IS_BA_CHANGE_PHASE))!=0;//カード交換のタイミングか？
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

/*
int Table::whoseTurn() const{//現在のターンの人のプレイヤー番号を返す
    return mPlayers.turn;
}
*/

void Table::firstGame(int cards[8][15]){//ゲームの初期化
    baBit = 0;
    /*
    mNum = 0;
    mRankR = 0;
    mRankL = 0;
    mSuits = 0;
    */
    setOnset(1);//空場にセット
    mBafuda.init();//カードは削除
    //mPlayers.set(cards);//カードの5行目以降の情報でセット
}

void Table::purge(){//場を流す（英語表現がわからなかった）
    baBit &= (IS_BA_KAKUMEI);   //革命状態は消えることはない
    baBit |= (IS_BA_ONSET);     //空場にする
    /*
    mNum = 0;
    mRankR = 0;
    mRankL = 0;
    mSuits = 0;
    */
    mBafuda.clear();      //カードを消す
    //mPlayers.recover(); //プレイヤーのパス状態を解除する
}

/*
void Table::setBafuda(int cards[8][15]){//場札を保存（場札から読み取れるものだけ更新する）
    mBafuda.clear();
    mBafuda.setBit(cards);
    
    if( mBafuda.isKakumei() ) revKakumei();//カードが革命を発生させるなら状態を反転する
    setKaidan( mBafuda.isKaidan() );      //階段
    setPair( mBafuda.isPair() );          //ペア
    
    mNum = mBafuda.mNum;                  //枚数
    if(mNum==1){//カード枚数            //単騎
        setTanki( 1 );
        //setJoker( mBafuda.isJoker() );    //joker単騎
        setJTanki( mBafuda.isJTanki() );    //joker単騎
    }else if(mNum==0){//おそらくここはめったにはいらない
        setOnset( 1 );
    }
    /*
    if( isKakumei() ){                  //強さ、革命なら左端を、通常なら右端を
        mRank = mBafuda.mRankL;//左端
    }else{
        mRank = mBafuda.mRankR;//右端
    }
    
    mRankL = mBafuda.mRankL;//左端
    mRankR = mBafuda.mRankR;//右端
    
    mSuits = mBafuda.mSuits;//スーツ
}
*/
    
/*
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
	//mPlayers.update(cards);
}
*/

void Table::print() const{
    
    cout << "ON" << isOnset() 
     <<", KA" << isKaidan()
     <<", PA" << isPair()
     << ", TN" << isTanki() 
     << ", NU" << mBafuda.mNum << ", RNL" << mBafuda.mRankL<< ", RNR" << mBafuda.mRankR << endl;
    cout << "KK" << isKakumei() 
    << ", SH"<< isShibari() 
    << ", SS " << mBafuda.mSuits << endl;
    //cout << "bafuda" << endl;
    //int temp[8][15]={{0}};
    //mCard.printBit2();
    //mPlayers.print();
}

void Table::print2(){
    cout << "OKPTSJ|";
    cout << isOnset() << isKaidan() << isPair() << isTanki() << isShibari() << isJTanki();
    
}

bool Table::sameBafuda(int bafuda[8][15]){
    for(int i=0;i<4;i++){
        for(int j=0;j<15;j++){
            if( !(bafuda[i][j]==0 && (mBafuda.getCardBit()&CARDBIT(i,j))==0) || !(bafuda[i][j]!=0 && (mBafuda.getCardBit()&CARDBIT(i,j))!=0) ){
                return false;
            }
        }
    }
    return true;
}

void Table::setBaInfo(int cards[8][15]){
    if(cards[5][4]>0)   baBit |=  IS_BA_ONSET;  //空場
    else                baBit &= ~IS_BA_ONSET;
    if(cards[5][6]>0)   baBit |=  IS_BA_KAKUMEI;//革命
    else                baBit &= ~IS_BA_KAKUMEI;
    if(cards[5][7]>0)   baBit |=  IS_BA_SHIBARI;//縛り
    else                baBit &= ~IS_BA_SHIBARI;
	
    if( isOnset() ){//場を流す
        purge();
    }
	//mPlayers.update(cards);
}

void Table::setBafuda(const Yaku &yaku){
    //場札を更新する
    if(mBafuda.mSuits==yaku.mSuits){
        setShibari(1);
    }else{
        setShibari(0);
    }
    if( yaku.isKakumei() ){
        revKakumei();//反転
    }

    if(yaku.isKaidan()){
        setKaidan(1);setPair(0);setTanki(0);
    }else if(yaku.isPair()){
        setKaidan(0);setPair(1);setTanki(0);
    }else if(yaku.isTanki()){
        setKaidan(0);setPair(0);setTanki(1);
    }

    mBafuda = yaku;//場札を取り換える
}

