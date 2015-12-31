
#include "Delusion.h"
#include "Card.h"

//#define DEBUG 

using namespace std;

void printVC(vector<Card> yaku){
    int i;
    for(i=0;i<yaku.size();i++){
        cout << i << endl;
        yaku[i].printBit();
    }
}

Delusion::Delusion(const Table &table, const int unsubmitted[8][15], const vector<Card> &yaku, int target){
    //場情報、未提出札、自分の合法手集合、観測するプレイヤー番号
    mTable = table;     //テーブルをコピー
	//mTable.print();
	mTarget = target;   //観測したい人
    vector<int> deck;   //未提出札集合
    makeDeck(&deck, unsubmitted);//未提出札を構成する
	muddleVector(&deck);//シャッフルする
    int playersHand[5][8][15] = {{0}};
    for(int i=0;i<5;i++){//手札を振り分ける
    	if(i != target){
        	randomCardDevide(playersHand, &deck, i, mTable.mPlayers.cards_num[i]);//手札を振り分ける
        	vector<Card> temp;
            makeAllYaku(&temp, playersHand[i]);//役を生成して
            mYakus.push_back(temp);//入れる
    	}else{
            mYakus.push_back(yaku);//自分のを入れる
        }
    }
}

void Delusion::updateSimTable(const Card &cd){
    //テーブルをcdにより更新する
    
    if(cd.mNum==0){//パスした
        mTable.simPass();
    }
    else{//何かしら出した
        if( cd.mNum == mTable.mPlayers.getCardsNum() ){//あがった
            mTable.simGoal();//あがり処理 //あがりフラグを立てるだけ
        }
        //提出札によるtableの更新
        mTable.simSubmit(cd);//table更新
    }
}

int Delusion::forwardDelusion(const Card &cd, int *depth){
    //仮想提出手による場の更新
    //これを再帰させていき、終局まで行ったら点数を返す
    #ifdef DEBUG
    cout << "forwardDelusion" << endl;
    mTable.print();
    printf("\n %d is submit\n", mTable.mPlayers.turn);
    cd.printBit();
    cout << "before " << mYakus[mTable.mPlayers.turn].size() << std::endl;
    printVC(mYakus[mTable.mPlayers.turn]);
    #endif
    
	//合法手役集合から取り除く
    if(cd.mNum!=0){
        removeLap(&mYakus[mTable.whoseTurn()], cd.getCardBit());//取り除く
    }
    mTable.simSubmit(cd);//提出手による更新
    
    int isGoaled = mTable.mPlayers.isGoaled, goal_num=0;
    for(int i=0;i<5;i++)if( (isGoaled&(1<<i))!=0 )goal_num++;
    if( (isGoaled&(1<<mTarget)) != 0 ){//ターゲットがゴールしている
       return 6-goal_num;//最新のgoal_num番目にあがった。最高位が5点となる
    }else if( goal_num==4 ){//他の4人があがった
        return 1;//peke
    }
    
    //まだゲームは終わっちゃいない
    #ifdef DEBUG
    cout << "new player is " << mTable.mPlayers.turn << endl;
    #endif
    Card submit = submitVirtualDefault();
    
    *depth = *depth+1;
    
    #ifdef DEBUG
    mTable.mPlayers.print();
    #endif
    return forwardDelusion(submit, depth);
}

int Delusion::startDelusion(int submit_id, int *depth){
    //入力は自分の仮想提出手
	#ifdef DEBUG
    cout << "startDelusion" << endl;
    #endif
    Card cd = mYakus[mTable.whoseTurn()][submit_id];//提出札をコピーする
    
	*depth = 0;
    return forwardDelusion(cd, depth);
}

int Delusion::startDelusion(const Card &submit_cards, int *depth){
    //入力は自分の仮想提出手
	#ifdef DEBUG
    cout << "startDelusion" << endl;
    #endif
    //Card cd = mYakus[mTable.whoseTurn()][submit_id];//提出札をコピーする
    Card cd = submit_cards;
    
	*depth = 0;
    return forwardDelusion(cd, depth);
}

Card Delusion::submitVirtualDefault(){
    vector<Card> &yaku = mYakus[mTable.whoseTurn()];
	//cout << yaku.size() << endl;
	
    if(mTable.isOnset()){
        //printf("on\n");
        int i, cKaidan=-1, cPair=-1, cTanki=-1, maxKN=0, maxPN=0;
        int cnt=0;
        for(i=0;i<yaku.size();i++){
            if( yaku[i].isKaidan() ){
                cnt++;
                if(cKaidan==-1 || maxKN < yaku[i].mNum){//見つかっていないか、枚数が多いものを入れる
                    cKaidan = i;
                    maxKN = yaku[i].mNum;
                }else if(maxKN == yaku[i].mNum){//枚数が同じなら、より弱い方を入れる
                    if( (mTable.isKakumei()&&yaku[i].mRankL>yaku[cKaidan].mRankL)||(!mTable.isKakumei()&&yaku[i].mRankR<yaku[cKaidan].mRankR) ){
                        cKaidan = i;
                    }
                }
            }else if(yaku[i].isPair() ){
                cnt++;
                if(cPair==-1 || maxPN < yaku[i].mNum){
                    cPair = i;
                    maxPN = yaku[i].mNum;
                }else if(maxPN == yaku[i].mNum){
                    if((mTable.isKakumei()&&yaku[i].mRankL>yaku[cPair].mRankL)||(!mTable.isKakumei()&&yaku[i].mRankR<yaku[cPair].mRankR) ){
                        cPair = i;
                    }
                }
            }else if(yaku[i].mNum == 1){
                if( cTanki==-1 || (mTable.isKakumei()&&yaku[i].mRankL>yaku[cTanki].mRankL)||(!mTable.isKakumei()&&yaku[i].mRankR<yaku[cTanki].mRankR) ){
                    cTanki = i;
                }
            }else if(yaku[i].mNum==0){
                
            }else{
                cout << "card is bukkoware\n" << endl;
                yaku[i].printBit();
                exit(1);
            }
        }
        if(cKaidan!=-1)return yaku[cKaidan];
        if(cPair!=-1)return yaku[cPair];
        if(cnt>0){
            printf("ba-ka\n");
            exit(1);
        }
        if(cTanki!=-1)return yaku[cTanki];
        printf("yaku size is %d\n", yaku.size() );
        printf("okassi on!\n");exit(1);
    }
    else{
        vector< Card > ATKY;
        int target = 0, i;
        //cout << "all yaku" << endl;
        //printVCyaku;
        if(mTable.isKaidan()){
            sortKaidan(&ATKY, &yaku, mTable);
        }
        else if(mTable.isPair()){
            sortPair(&ATKY, &yaku, mTable);
        }
        else{
            sortTanki(&ATKY, &yaku, mTable);
        }
        //cout << "atky is" << endl;
        //printVC(ATKY);
        //cout << "atky size = " << ATKY.size() << endl;
        if(ATKY.size() <= 2){   //出せるのが1つないし2つ
            target = 0;         //（出すかパスかなら出す）
        }else{                  //それ以外
            for(i=1;i<ATKY.size()-1;i++){
                if((mTable.isKakumei()&&ATKY[i].mRankL>ATKY[target].mRankL)||(!mTable.isKakumei()&&ATKY[i].mRankR<ATKY[target].mRankR) ){
                    target = i;
                }
            }
        }
        return ATKY[target];
        printf("okassi! fo\n");exit(1);
    }
}

void muddleVector(vector<int> *vec){
    for(int i=0;i<vec->size()/2;i++){
        int a = (int)( (vec->size()-1) * ((double)random()/RAND_MAX));
        int b = (int)( (vec->size()-1) * ((double)random()/RAND_MAX));
        int c = (*vec)[a];
        (*vec)[a] = (*vec)[b];
        (*vec)[b] = c;
    }
    //cout << "muddle" << endl;
}

void randomCardDevide(int hands[5][8][15], vector<int> *deck, int target, int num){
    int nums = num;
    #ifdef DEBUG
    cout << target << " " << num << " " << deck->size() << endl;
    #endif
    while(nums>0 ){
        hands[target][(*deck)[0]/14][(*deck)[0]%14] = 1;
        nums--;
        if(deck->size()==0){//もう終わっちゃった
            cout << "ha?" <<endl;
            exit(1);
        }
        else{//消す
            deck->erase(deck->begin());
        }
    }
    
    //cout << "dev" << endl;
}

void makeDeck(vector<int> *deck, const int dust[8][15]){
    int i,j;
    for(i=0;i<4;i++){
        for(j=1;j<=13;j++){
            if(dust[i][j]==0){
                deck->push_back( i*14 + j );
            }
        }
    }
    if(dust[4][1]==0){
        deck->push_back( 14*4 + 1 );
    }
    //print515(dust);
    //printf("%d\n", deck->size());
    
    //cout << "make" << endl;
}

