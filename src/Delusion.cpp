#include<cstdio>
#include<cstdlib>
#include "Delusion.h"
#include "Yaku.h"
#include "makeYaku.h"
#include "default.h"
#include "debug.h"
#include "common.h"

//#define DEBUG 

using namespace std;

void printVC(vector<Yaku> yaku){
    int i;
    for(i=0;i<yaku.size();i++){
        cout << i << endl;
        yaku[i].printBit();
    }
}

Delusion::Delusion(const Table &table, const int unsubmitted[8][15], const Players &players, const vector<Yaku> &yaku, Random *r, int target){
    //場情報、未提出札、自分の合法手集合、観測するプレイヤー番号
    mTable = table;     //テーブルをコピー
	mPlayers = players;
    mTarget = target;   //観測したい人
    random = r;
    vector<int> deck;   //未提出札集合
    makeDeck(&deck, unsubmitted);//未提出札を構成する
	muddleVector(&deck);//シャッフルする
    int playersHand[5][8][15] = {{0}};
    for(int i=0;i<5;i++){//手札を振り分ける
    	if(i != target){
        	randomCardDevide(playersHand[i], &deck, mPlayers.id[i].cards_num);//手札を振り分ける
        	vector<Yaku> temp;
            makeAllYaku(&temp, playersHand[i]);//役を生成して
            mYakus.push_back(temp);//入れる
    	}else{
            mYakus.push_back(yaku);//自分のを入れる
        }
    }
    //cout<<"this "<<mYakus[0].size()<<" "<<mYakus[1].size()<<" "<<mYakus[2].size()<<" "<<mYakus[3].size()<<" "<<mYakus[4].size()<<endl;
    //print515(playersHand[0]);
}

Delusion::Delusion(const Table &table, const int64 unsubmitted, const Players &players, const vector<Yaku> &yaku, Random *r, int target){
    //場情報、未提出札、自分の合法手集合、観測するプレイヤー番号
    mTable = table;     //テーブルをコピー
	mPlayers = players;
    mTarget = target;   //観測したい人
    random = r;
    vector<int> deck;   //未提出札集合
    makeDeck(&deck, ~unsubmitted);//未提出札を構成する
	muddleVector(&deck);//シャッフルする
    int playersHand[5][8][15] = {{0}};
    for(int i=0;i<5;i++){//手札を振り分ける
    	if(i != target){
        	randomCardDevide(playersHand[i], &deck, mPlayers.id[i].cards_num);//手札を振り分ける
        	vector<Yaku> temp;
            makeAllYaku(&temp, playersHand[i]);//役を生成して
            mYakus.push_back(temp);//入れる
    	}else{
            mYakus.push_back(yaku);//自分のを入れる
        }
    }
    //cout<<"this "<<mYakus[0].size()<<" "<<mYakus[1].size()<<" "<<mYakus[2].size()<<" "<<mYakus[3].size()<<" "<<mYakus[4].size()<<endl;
    //print515(playersHand[0]);
}

int Delusion::forwardDelusion(const Yaku &cd, int *depth){
    //仮想提出手による場の更新
    //これを再帰させていき、終局まで行ったら点数を返す
    #ifdef DEBUG
    cout << "forwardDelusion" << endl;
    mTable.print();
    printf("\n %d is submit\n", mPlayers.turnId());
    cd.printBit();
    //cout << "before " << mYakus[mPlayers.turnId()].size() << std::endl;
    //printVC(mYakus[mPlayers.turnId()]);
    #endif
    
    //出した人の合法手役集合から提出札を使った役を取り除く
    if(cd.mNum!=0){
        removeLap(&mYakus[mPlayers.turnId()], cd.getCardBit());//取り除く
    }
    simSubmit(cd);//提出手による更新
    
    //あがりのチェック（ターゲットの順位がわかったらその時点で点数を返す）
    if( mPlayers.agari.size()>0 && mPlayers.agari[mPlayers.agari.size()-1] == mTarget ){//ターゲットがゴールした
        return 6-mPlayers.agari.size();
    }else if( mPlayers.agari.size() == 4 ){//PE-KE
        return 1;
    }
    
    //まだゲームは終わっちゃいないぜ
    #ifdef DEBUG
    cout << "new player is " << mPlayers.turnId() << endl;
    #endif
    
    //提出札を選択する
    Yaku submit;
    selectSubmitCardsLikeDefault(&submit, mTable, mYakus[mPlayers.turnId()]);
    
    //深さを増やして
    *depth = *depth+1;
    //さらに妄想を深める
    return forwardDelusion(submit, depth);
}

int Delusion::startDelusion(int submit_id, int *depth){
    //入力は自分の仮想提出手の位置
	Yaku cd = mYakus[mPlayers.turnId()][submit_id];//提出札をコピーする
    
    //深さを0に設定して
	*depth = 0;
    //妄想を開始する
    return forwardDelusion(cd, depth);
}

int Delusion::startDelusion(const Yaku &submit_cards, int *depth){
    //入力は自分の仮想提出手
	Yaku cd = submit_cards;//提出札をコピーする
    
	//深さを0に設定して
	*depth = 0;
    //妄想を開始する
    return forwardDelusion(cd, depth);
}

void Delusion::muddleVector(vector<int> *vec){
    //配列をかき混ぜる
    for(int i=0;i<vec->size()/2;i++){
        int a = (int)( (vec->size()-1) * (double)random->rand());
        int b = (int)( (vec->size()-1) * (double)random->rand());
        int c = (*vec)[a];
        (*vec)[a] = (*vec)[b];
        (*vec)[b] = c;
    }
    //cout << "muddle" << endl;
}

void Delusion::randomCardDevide(int hand[8][15], vector<int> *deck, int num){
    //handにnum枚分deckの上から渡していく
    
    while(num > 0){//handに入れる枚数
        hand[(*deck)[0]/14][(*deck)[0]%14] = 1;//deckの先頭のカードを入れる
        num--;//1枚引く
        if(deck->size()==0){//もう割り当てるカードがない
            cout << "ha?" <<endl;
            exit(1);
        }
        else{//消す
            deck->erase(deck->begin());
        }
    }
    
}

void makeDeck(vector<int> *deck, const int gomi[8][15]){
    //敵の持ちうるカード集合を作る
    //入力はすでにゲーム中で提出されたカードが1が入った配列
    //なのでまだ0の項目が未提出のカード
    int i,j;
    for(i=0;i<4;i++){
        for(j=1;j<=13;j++){
            if(gomi[i][j]==0){
                deck->push_back( i*14 + j );
            }
        }
    }
    if(gomi[4][1]==0){
        deck->push_back( 14*4 + 1 );
    }
}

void makeDeck(vector<int> *deck, const int64 gomi){
    //敵の持ちうるカード集合を作る
    //入力はすでにゲーム中で提出されたカードが1が入った配列
    //なのでまだ0の項目が未提出のカード
    int i,j;
    for(i=0;i<4;i++){
        for(j=1;j<=13;j++){
            if( gomi&CARDBIT(i, j) ){
                deck->push_back( i*14 + j );
            }
        }
    }
    if( gomi&IS_JUSED ){
        deck->push_back( 14*4 + 1 );
    }
}

int selectSubmitCardsByDelusion(Yaku *select_cards, const Table &table, const Players &players, const vector<Yaku> &yaku, const int gomi[8][15], int hands[8][15]){
    //モンテカルロによる提出
    
    //現在出せる合法手分だけ考える
    Table simTable = table;
    Players simPlayers = players;
    vector<Yaku> legalYaku;//操作用役集合
    pickAllLegalYaku( &legalYaku, yaku, table );//パスを除きこの局面で出せるすべての合法手を選定する
	makePass( &legalYaku );//パスも含める

    Random random;
	
    if( legalYaku.size() == 1 ){//出せる役がパスしかない
	    *select_cards = legalYaku[0];//パスを載せて終わり
		return 0;
	}
    
	//パス以外にできるのならばこちらにもくる
    
    vector<int> SIM_SCORE(yaku.size(), 0), SIM_COUNT(yaku.size(), 0);//シミュレーションで使う得点用の配列を用意しておく
    /*
    for(int i=0;i < yaku.size(); i++){
        SIM_SCORE.push_back(0);
        SIM_COUNT.push_back(0);
    }
    */
    
    //ここでようやく妄想を始める
    for(int idx=0;idx < legalYaku.size();idx++){//すべての合法手に対して
    	for(int cnt=0;cnt < 200;cnt++){//200回のシミュレーションを行う
    	    vector<Yaku> tempYaku;
    	    tempYaku = yaku;//全部の役集合をコピーする
    	    Delusion del(simTable, gomi, simPlayers, tempYaku, &random, simPlayers.turnId());//妄想環境のセットアップ
        	int depth = 0;//妄想の深さ（特に使わないが）
            SIM_SCORE[idx] += del.startDelusion( legalYaku[idx], &depth );//得点を加算する
            //cout << SIM_SCORE[idx] << endl;
            SIM_COUNT[idx]++;//その手に対して割り当てたシミュレーション回数を加算する
            //exit(1);
        }
    }
    
	//シミュレーションを回した合法手の中から評価が最大のものを探す
    vector<double> fin_score;
    int maxIdx = 0;
    for(int cnt=0;cnt < legalYaku.size(); cnt++){
        if(SIM_COUNT[cnt]!=0){
            fin_score.push_back( (double)SIM_SCORE[cnt]/ SIM_COUNT[cnt]);//期待値を得点とする
            if(fin_score[cnt] > fin_score[maxIdx]){
                maxIdx = cnt;
            }
        }else{//シミュレーションを割り当ていなければ得点は0とする
            fin_score.push_back( 0 );
        }
    }
    
    *select_cards = legalYaku[maxIdx];
    return 1;//全合法手リストでの対応する番号を送る
}

int selectSubmitCardsByDelusion(Yaku *select_cards, const Table &table, const Players &players, const vector<Yaku> &yaku, const int64 gomi, int hands[8][15]){
    //モンテカルロによる提出
    
    //現在出せる合法手分だけ考える
    Table simTable = table;
    Players simPlayers = players;
    vector<Yaku> legalYaku;//操作用役集合
    pickAllLegalYaku( &legalYaku, yaku, table );//パスを除きこの局面で出せるすべての合法手を選定する
	makePass( &legalYaku );//パスも含める

    Random random;
	
    if( legalYaku.size() == 1 ){//出せる役がパスしかない
	    *select_cards = legalYaku[0];//パスを載せて終わり
		return 0;
	}
    
	//パス以外にできるのならばこちらにもくる
    
    vector<int> SIM_SCORE(yaku.size(), 0), SIM_COUNT(yaku.size(), 0);//シミュレーションで使う得点用の配列を用意しておく
    /*
    for(int i=0;i < yaku.size(); i++){
        SIM_SCORE.push_back(0);
        SIM_COUNT.push_back(0);
    }
    */
    
    //ここでようやく妄想を始める
    for(int idx=0;idx < legalYaku.size();idx++){//すべての合法手に対して
    	for(int cnt=0;cnt < 200;cnt++){//200回のシミュレーションを行う
    	    vector<Yaku> tempYaku;
    	    tempYaku = yaku;//全部の役集合をコピーする
    	    Delusion del(simTable, gomi, simPlayers, tempYaku, &random, simPlayers.turnId());//妄想環境のセットアップ
        	int depth = 0;//妄想の深さ（特に使わないが）
            SIM_SCORE[idx] += del.startDelusion( legalYaku[idx], &depth );//得点を加算する
            //cout << SIM_SCORE[idx] << endl;
            SIM_COUNT[idx]++;//その手に対して割り当てたシミュレーション回数を加算する
            //exit(1);
        }
    }
    
	//シミュレーションを回した合法手の中から評価が最大のものを探す
    vector<double> fin_score;
    int maxIdx = 0;
    for(int cnt=0;cnt < legalYaku.size(); cnt++){
        if(SIM_COUNT[cnt]!=0){
            fin_score.push_back( (double)SIM_SCORE[cnt]/ SIM_COUNT[cnt]);//期待値を得点とする
            if(fin_score[cnt] > fin_score[maxIdx]){
                maxIdx = cnt;
            }
        }else{//シミュレーションを割り当ていなければ得点は0とする
            fin_score.push_back( 0 );
        }
    }
    
    *select_cards = legalYaku[maxIdx];
    return 1;//全合法手リストでの対応する番号を送る
}

void Delusion::simSubmit( const Yaku &yaku ){
    if( yaku.isPass() ){         //パスをした
        mPlayers.id[mPlayers.turnId()].passed = true;
    }
    else{//なんらか出した
        mPlayers.id[mPlayers.turnId()].cards_num -= yaku.mNum;//枚数も差し引く
        if(mPlayers.id[mPlayers.turnId()].cards_num<0){
            cout << "maisuugaokasii" << endl;
            yaku.print();
            exit(1);
        }
        
        if( mPlayers.id[mPlayers.turnId()].cards_num == 0 ){//あがった
            mPlayers.addAgari( mPlayers.turnId() );
        }
        
        if( yaku.is8giri()|| (mTable.mBafuda.isJTanki() && yaku.isSpade3()) ){
            //8切り、スペ3
            mTable.setOnset(true);//流れる
            //purge();
        }else{
            mTable.setOnset(false);
        }
        
        mTable.setBafuda( yaku );
        
    }
    
    if( mTable.isOnset() ){//流れた
        purge();
    }else if( isBaAlive() ){//まだ流れない
        mPlayers.nextTurn();
    }else{//やっぱり流れる
        purge();
    }
    
}

void Delusion::purge(){//場を流す
    //場札情報を初期化する
    mTable.purge();
    
    //パスから復帰させる
    mPlayers.recover();
    
    //turnは最後にパスした人（つまり現在の人）なので変更しない
    //が、あがっていればその限りでない
    if( mPlayers.id[mPlayers.turnId()].cards_num == 0){
        mPlayers.nextTurn();
    }
}

bool Delusion::isBaAlive(){
    //ターンを回せるのか、場が流れないのか
    for(int i=0;i<5;i++){
        if(mPlayers.id[i].passed == false && mPlayers.id[i].cards_num!=0 ){//あがってなくてかつパスしていない人がいるなら
            return true;
        }
    }
    return false;
}
