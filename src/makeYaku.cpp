#include <iostream>
#include <algorithm>
#include "Yaku.h"
#include "makeYaku.h"
#include "debug.h"

using namespace std;

//役を作るようの関数群
//ただしjoker1枚ルールのみに対応しているため、のちのち拡充する

void pushYaku(vector<Yaku> *allYaku, int64 cd, int suits, int num, int rank, int rank2, int jps, int jpr){
    //左からカードビット、スート、枚数、左側のランク、右側のランク（階段、joker単騎のとき以外は同じ数字）、使うjokerのスート、使うjokerのランク（使わないときは-1）
    Yaku yaku(cd, suits, num, rank, rank2, jps, jpr);
    allYaku->push_back(yaku);
}

void makeAllYaku(vector<Yaku> *allYaku, const int hands[8][15]){
    //handsから作ることが可能なすべての役を作る
    //cout<<"a "<<allYaku->size()<<endl;
	makeKaidanFrom815(allYaku, hands);//階段
/*
int pa=0;
    for(int i=0;i<allYaku->size();i++){
    if((*allYaku)[i].isPass())pa++;
}    
cout<<"b "<<allYaku->size()<<" " <<pa<<endl;
*/
    makePairFrom815(allYaku, hands);//ペア
/*
pa=0;
for(int i=0;i<allYaku->size();i++){
    if((*allYaku)[i].isPass())pa++;
}    
cout<<"c "<<allYaku->size()<<" " <<pa<<endl;
*/
    makeTankiFrom815(allYaku, hands);//単騎
/*
pa=0;
for(int i=0;i<allYaku->size();i++){
    if((*allYaku)[i].isPass())pa++;
}    
cout<<"d "<<allYaku->size()<<" " <<pa<<endl;
*/
    makePass(allYaku);//パス
/*    
pa=0;
for(int i=0;i<allYaku->size();i++){
    if((*allYaku)[i].isPass())pa++;
}    
cout<<"d "<<allYaku->size()<<" " <<pa<<endl;
*/
}


void makeAllYaku2(vector<Yaku> *allYaku, const int hands[8][15], int64 handsbit){
    //handsから作ることが可能なすべての役を作る
    //cout<<"a "<<allYaku->size()<<endl;
    
    /*
    int x[8][15]={{0}};
    convBitTo815(x, handsbit);
    print815(x);
    cout<<endl;
    
    for(int i=0;i<5;i++){
        for(int j=0;j<15;j++){
            x[i][j] = hands[i][j];
        }
    }
    cout << endl;
    print815(x);
    //exit(1);
    */
    makeKaidanFromBit(allYaku, handsbit);//階段
/*
int pa=0;
    for(int i=0;i<allYaku->size();i++){
    if((*allYaku)[i].isPass())pa++;
}    
cout<<"b "<<allYaku->size()<<" " <<pa<<endl;
*/
    makePairFrom815(allYaku, hands);//ペア
/*
pa=0;
for(int i=0;i<allYaku->size();i++){
    if((*allYaku)[i].isPass())pa++;
}    
cout<<"c "<<allYaku->size()<<" " <<pa<<endl;
*/
    makeTankiFrom815(allYaku, hands);//単騎
/*
pa=0;
for(int i=0;i<allYaku->size();i++){
    if((*allYaku)[i].isPass())pa++;
}    
cout<<"d "<<allYaku->size()<<" " <<pa<<endl;
*/
    makePass(allYaku);//パス
/*    
pa=0;
for(int i=0;i<allYaku->size();i++){
    if((*allYaku)[i].isPass())pa++;
}    
cout<<"d "<<allYaku->size()<<" " <<pa<<endl;
*/
}


void pickKaidan(vector<Yaku> *kaidan, const vector<Yaku> &allYaku){
    for(int i=0;i<allYaku.size();i++){
        if( allYaku[i].isKaidan() ){
            kaidan->push_back( allYaku[i] );
        }
    }
}

void pickPair(vector<Yaku> *pair, const vector<Yaku> &allYaku){
    for(int i=0;i<allYaku.size();i++){
        if( allYaku[i].isPair() ){
            pair->push_back( allYaku[i] );
        }
    }
}

void pickTanki(vector<Yaku> *tanki, const vector<Yaku> &allYaku){
    for(int i=0;i<allYaku.size();i++){
        if( allYaku[i].isTanki() ){
            tanki->push_back( allYaku[i] );
        }
    }
}

void pickLegalKaidan(vector<Yaku> *legalYaku, const vector<Yaku> &allYaku, const Table &table){
    int i;
    
    if(table.isKakumei()){//革命のとき
        for(i=0;i<allYaku.size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( allYaku[i].isKaidan() && 
                (allYaku[i].mNum==table.mBafuda.mNum && allYaku[i].mRankR<table.mBafuda.mRankL)
                ){
                if( !table.isShibari() || (table.isShibari() && table.mBafuda.mSuits==allYaku[i].mSuits)){
                    legalYaku->push_back( allYaku[i] );
                }
            }
        }
    }else{//革命ではないとき
        for(i=0;i<allYaku.size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( (allYaku[i].isKaidan()) &&
                 allYaku[i].mNum==table.mBafuda.mNum && allYaku[i].mRankL>table.mBafuda.mRankR)
                {
                if( !table.isShibari() || (table.isShibari() && table.mBafuda.mSuits==allYaku[i].mSuits)){
                    legalYaku->push_back( allYaku[i] );
                }
            }
        }
    }
}
	    
void pickLegalPair(vector<Yaku> *legalYaku, const vector<Yaku> &allYaku, const Table &table){
    int i;
    
    if(table.isKakumei()){//革命のとき
        for(i=0;i<allYaku.size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( allYaku[i].isPair() && 
               allYaku[i].mNum==table.mBafuda.mNum && allYaku[i].mRankL<table.mBafuda.mRankL
               ){
                if( !table.isShibari() || (table.isShibari() && table.mBafuda.mSuits==allYaku[i].mSuits)){
                    legalYaku->push_back( allYaku[i] );
                }
            }
        }
    }else{//革命ではないとき
        for(i=0;i<allYaku.size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( (allYaku[i].isPair()) && 
                allYaku[i].mNum==table.mBafuda.mNum && allYaku[i].mRankR>table.mBafuda.mRankL
                ){
                if( !table.isShibari() || (table.isShibari() && table.mBafuda.mSuits==allYaku[i].mSuits)){
                    legalYaku->push_back( allYaku[i] );
                }
            }
        }
    }
}
	   
void pickLegalTanki(vector<Yaku> *legalYaku, const vector<Yaku> &allYaku, const Table &table){
    int i;
    
    if(table.mBafuda.isJTanki()){//ジョーカー単騎はスペ３しか考えられない
        for(i=0; i < allYaku.size(); i++){
            if(allYaku[i].isSpade3()==1){
                legalYaku->push_back( allYaku[i] );
                break;
            }
        }
    }
    else if(table.isKakumei()){//革命のとき
        for(i=0; i < allYaku.size(); i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if(allYaku[i].mNum==1 && allYaku[i].mRankL<table.mBafuda.mRankL){
                if( !table.isShibari() || (table.isShibari() && table.mBafuda.mSuits==allYaku[i].mSuits || allYaku[i].isJTanki() )){
                    legalYaku->push_back( allYaku[i] );
                }
            }
        }
    }
    else{//革命ではないとき
        for(i=0; i < allYaku.size(); i++){
            //階段で枚数が同じでかつ右側の強さが場札の強さより大きい
            if(allYaku[i].mNum==1 && allYaku[i].mRankR>table.mBafuda.mRankL){
                if( !table.isShibari() || (table.isShibari() && table.mBafuda.mSuits==allYaku[i].mSuits || allYaku[i].isJTanki() )){
                   legalYaku->push_back( allYaku[i] );
                }
            }
        }
    }
}
	    
void pickAllLegalYaku(vector<Yaku> *legalYaku, const vector<Yaku> &allYaku, const Table &table){
    //自分の手札から構成できる全合法手のうち
    //現在の場の状況において、（table）
    //出せる手役のみをピックアップする
    if(table.isOnset()){
    	//パスだけ除外する（空場ではパスはすべきでないと信じている）
    	for(int i=0;i<allYaku.size()-1;i++){
    		legalYaku->push_back( allYaku[i] );
    	}
    }else{//各々の場に対して
    	if(table.isTanki()){
    		pickLegalTanki(legalYaku, allYaku, table);
    	}
    	else if(table.isPair()){
    		pickLegalPair(legalYaku, allYaku, table);
    	}
    	else if(table.isKaidan()){
    		pickLegalKaidan(legalYaku, allYaku, table);
    	}
    }
}

void makeKaidanFrom815(vector<Yaku> *yaku, const int hands[8][15]){
    //handsから作ることの可能な階段役をyakuに入れる
	//記述が品雑になるので場の状況は一切考えない
	//あとで合致するものだけ取り出す
	int joker = (hands[4][1]!=0);
	
	int suit, rank;
	for(suit=0; suit<4; suit++){//スートごと一列ずつ見る
		for(rank=0; rank<13;rank++){//始点を決定する（あり得るのは[12-13-14]マデ）
			int length = 0;         //伸びる長さ（役の枚数）
			int joker_flag = joker; //jokerは使えるか。
			int searching = 1;      //探索中
			while(searching==1){
				if(rank+length<15 && hands[suit][rank+length]==1){//カードがあるなら
					length++;
				}else if(joker_flag==1){//なくてもジョーカーが使えるなら
					length++;
					joker_flag = 0;
				}else{//作れない場合はおしまい
					searching = 0;
				}
				if(searching==1 && length>=3){//階段が作れる
					int64 hd = IS_KAIDAN;
				    //hd |= (length<6) ? IS_NUM(length) : IS_NUM(6);//6?枚まではビットが使える
					int i, JposSuit=-1, JposRank=-1;
					int bitSuit = 0;  bitSuit|=(1<<suit);
					for(i=rank;i<rank+length;i++){
						if(hands[suit][i]==1){//1なるは1~13なり
							hd |= CARDBIT(suit, i);
						}else{//なければjokerを使う
			                hd |= IS_JUSED;
							JposSuit = suit;JposRank = i;
						}
					}
				    
				    //if( rank<=6 && 6<=rank+length-1 )hd|=IS_8GIRI;//8切り扱いになる
					Yaku cd(hd, bitSuit, length, rank, rank+length-1, JposSuit, JposRank);
					yaku->push_back(cd);

					if(joker_flag==1){//jokerを使わずに来ていれば、jokerに置き換えた階段も作ることができる
						for(i=rank;i<rank+length;i++){
							int64 mask = ~CARDBIT(suit, i);//joker使うとこだけ0
						    int64 hdj = (mask&hd)|IS_JUSED;//残すものは残す
							JposSuit=suit, JposRank=i;//jokerポジションは別変数のため全体を変える必要はない（のか？）
							Yaku cd(hdj, bitSuit, length, rank, rank+length-1, JposSuit, JposRank);
							yaku->push_back(cd);
					    }
					}

				}
			}//while(searching)
		}//for(order
	}//for(suit
}

void makeKaidanFromBit(vector<Yaku> *yaku, const int64 hands){
    int64 kaidan1 = 3ull;
    int64 kaidan2 = 5ull;
    //cout << "j"<<endl;
    //printBit(hands);
    if( hands&IS_JUSED ){//jokerを持っている
        for(int suit=0; suit<4; suit++){
            int bitSuit = (1<<suit);
            //int64 hands1 = hands<<(suit*13);//そのスートの始点を見る
            //for(int rank=1; rank<13; rank++){//11 12
            for(int rank=1; rank<13; rank++){//12 13
                int64 kaidan = kaidan1 << (suit*13 + rank-1);//始点を動かす
                //int64 hands2 = hands1<<(rank-1);//始点を動かす
                //int64 temp = hands2&kaidan1;
                int64 temp = hands&kaidan;
                int bitnum = popCount64bit(temp);

                //cout<<"k"<<endl;
                //printBit(hands);
                //printBit(kaidan);
                //cout << "kasanari " << bitnum << endl;
                if( bitnum==2 ){//2つともビットが立っている
                    //始点から11...で始まる
                    int64 hd = temp;
                    int JposSuit = -1;
                    int JposRank = -1;
                    bool j_flag = true;
                    int length = 2;
                    //joker + 2枚連続で作れる階段
                    
                        Yaku cd1(temp|IS_KAIDAN|IS_JUSED, bitSuit, 3, rank-1, rank+1, suit, rank-1);
                        yaku->push_back(cd1);
                    
                    
                        Yaku cd2(temp|IS_KAIDAN|IS_JUSED, bitSuit, 3, rank, rank+2, suit, rank+length);
                        yaku->push_back(cd2);
                    
                    for(int k=rank+2; k<=13; k++){//11 12 13の右端まで
                        if( hands&CARDBIT(suit,k) ){
                            length++;
                            temp|=CARDBIT(suit,k);
                            //cout<<suit<<" "<<rank<<" "<<1<<endl;
                            //printBit(temp);
                            {
                                Yaku cd(temp|IS_KAIDAN, bitSuit, length, rank, rank+length-1, JposSuit, JposRank);
                                yaku->push_back(cd);
                            }
                            if( j_flag ){//jokerを使っていなければ
                                {
                                    Yaku cd(temp|IS_KAIDAN|IS_JUSED, bitSuit, length, rank, rank+length-1, suit, rank-1);
                                    yaku->push_back(cd);
                                }
                                {
                                    Yaku cd(temp|IS_KAIDAN|IS_JUSED, bitSuit, length, rank, rank+length-1, suit, rank+length);
                                    yaku->push_back(cd);
                                }
                                for(int l=rank+1; l<k; l++){//階段の始点と終点を除く箇所をjokerに置き換えたバージョンを作る
                                    int64 jtemp = (temp&(~CARDBIT(suit,l)))|IS_JUSED;//jokerだけ0に返す
                                    //cout<<suit<<" "<<rank<<" "<<2<<endl;
                                    //printBit(jtemp);
                                    Yaku cd(jtemp|IS_JUSED|IS_KAIDAN, bitSuit, length, rank, rank+length-1, suit, l);
                                    yaku->push_back(cd);
                                }
                            }
                        }else if( j_flag ){//ないけどjokerを使う
                            /*
                            if(length>=3){//これまでで階段が作れていれば、jokerと置き換えるバージョンも作る
                                for(int l=rank+1; l<k-1; l++){
                                    int64 jtemp = (temp&(~CARDBIT(suit,l)))|IS_JUSED;//jokerだけ0に返す
cout<<suit<<" "<<rank<<" "<<2<<endl;
                            printBit(jtemp);
                                    Yaku cd(jtemp|IS_JUSED|IS_KAIDAN, bitSuit, length, rank, rank+length-1, suit, l);
                                    yaku->push_back(cd);
                                }
                            }
                            */
                            /*
                            else{
                                int64 jtemp = (temp&(~CARDBIT(suit,k+1)))|IS_JUSED;//jokerだけ0に返す
                                Yaku cd(jtemp|IS_JUSED|IS_KAIDAN, bitSuit, length, rank, rank+length-1, suit, l);
                                yaku->push_back(cd);
                            }
                            */
                            //jokerに置き換えたバージョンを作る
                            JposSuit = suit;
                            JposRank = k;
                            length++;
                            //cout<<suit<<" "<<rank<<" "<<3<<endl;
                            //printBit(temp);
                            //Yaku cd(temp|IS_JUSED|IS_KAIDAN, bitSuit, length, rank, rank+length-1, JposSuit, JposRank);
                            //yaku->push_back(cd);
                            j_flag = false;
                        }else{
                            k=15;
                        }
                    }
                    //break;
                }else if(bitnum==1 && rank<12){//11 12 13が最大
                    //始点から101...で始まる
                    //jokerは101の0に使うので、後ろが0ならその時点で終了
                    kaidan = kaidan2 << (suit*13+rank-1);//始点を動かす
                    temp = hands&kaidan;
                    
                    if( popCount64bit(temp)==2 ){
                        int length = 3;
                        //101を追加
                        //cout<<suit<<" "<<rank<<" "<<4<<endl;
                        //printBit(temp);
                        {
                        Yaku cd1(temp|IS_JUSED|IS_KAIDAN, bitSuit, length, rank, rank+length-1, suit, rank+1);
                        yaku->push_back(cd1);
                        }
                        //伸ばす
                        for(int k=rank+3; k<=13; k++){//見る点は13まで
                            if( hands&CARDBIT(suit,k) ){
                                length++;
                                temp|=CARDBIT(suit,k);
                                //cout<<suit<<" "<<rank<<" "<<5<<endl;
                                //printBit(temp);
                                Yaku cd(temp|IS_JUSED|IS_KAIDAN, bitSuit, length, rank, rank+length-1, suit, rank+1);
                                yaku->push_back(cd);
                            }else{
                                break;
                            }
                        }
                    }else{
                        rank+=2;
                    }
                }else{
                    rank++;
                }
            }
        }

    }else{
//cout<<"9090"<<endl;
        for(int suit=0; suit<4; suit++){
            int bitSuit = (1<<suit);
            //int64 hands1 = hands<<(suit*13);//そのスートの始点を見る
            for(int rank=1; rank<12; rank++){//11 12 13 が最長（jokerはないので14は考えない）
                int64 kaidan = kaidan1 << (suit*13+rank-1);//始点を動かす
                int64 temp = hands&kaidan;
                //cout<<"k"<<endl;
                //printBit(hands);
                //printBit(kaidan);
                //cout << "kasanari " << popCount64bit(temp) << endl;
                if( popCount64bit(temp)==2 ){//2つともビットが立っている
                    //int64 hd = temp;
                    int length = 2;
                    for(int k=rank+2; k<14; k++){
                        if( hands&CARDBIT(suit, k) ){
                            length++;
                            temp|=CARDBIT(suit, k);
                            Yaku cd(temp|IS_KAIDAN, bitSuit, length, rank, rank+length-1, -1, -1);
                            yaku->push_back(cd);
                        }else{
                            break;
                        }
                    }
                }else{
                    rank++;
                }
                //jokerはないので、その他は考えられない
            }
        }
    }
}


void makePairFrom815(vector<Yaku> *yaku, const int hands[8][15]){
	//記述が品雑になるので場の状況は一切考えない
	//あとで合致するものだけ取り出す
	
	#define PATTERN_NUM 11
	int PATTERN[PATTERN_NUM][4] = {
		{1,1,0,0},{1,0,1,0},{1,0,0,1},{0,1,1,0},{0,1,0,1},{0,0,1,1},//6個は2枚
		{1,1,1,0},{1,1,0,1},{1,0,1,1},{0,1,1,1},                    //4個は3枚
		{1,1,1,1}                                                   //1個は4枚
	};//ペアの各スートの可能性パターン
	//これに合致するように探していく
	
	int suit, rank, pat;
    int joker = (hands[4][1]!=0);
	for(rank=1;rank<=13;rank++){//各ランクについてみていく
		for(pat=0;pat<PATTERN_NUM; pat++){//それぞれのパターンについて
			int num = 0, match = 0, unmatch = 0;
			for(suit=0;suit<4;suit++){//スートを調べていく
				if(PATTERN[pat][suit]==1){//当該のパターンについて
					num++;//枚数
					if(hands[suit][rank]==1){//手札から出せる
						match++;
					}else{//出せない
						unmatch++;
					}
				}
			}//for(suit
			if(num == match){//jokerを使わずに作ることができる
				int64 hd = IS_PAIR;
				int bitSuit = 0;
				for(suit=0;suit<4;suit++){
					if(PATTERN[pat][suit]==1){
						//hd |= CARDBIT(suit, rank)|IS_NUM(num);
					    hd |= CARDBIT(suit, rank);
						bitSuit |= (1<<suit);
					}
				}
			    //if(rank==6)hd|=IS_8GIRI;//8切り
				Yaku cd(hd, bitSuit, num, rank, rank, -1, -1);
				yaku->push_back(cd);
				if(joker==1){//jokerに置き換えたバージョンを（8で使うくらいしか利点がわからない）
				    //hd |= 0ull;
					for(suit=0;suit<4;suit++){//jokerに置き換えるスート
						if(PATTERN[pat][suit]==1){
						    int64 mask = ~CARDBIT(suit, rank);//ジョーカーを使うところだけ0
						    //int64 hdj = (mask&hd)|IS_JUSED|IS_NUM(num);
						    int64 hdj = (mask&hd)|IS_JUSED;
							int JposSuit=suit, JposRank=rank;//jokerの位置
							Yaku cdj(hdj, bitSuit, num, rank, rank, JposSuit, JposRank);
				            yaku->push_back(cdj);
						}
					}
				}
			}else if(joker==1 && unmatch==1){//jokerを使えて、足りないのが1枚だけなら
				//int64 hd = IS_PAIR|IS_JUSED|IS_NUM(num);
				int64 hd = IS_PAIR|IS_JUSED;
			    int bitSuit = 0;
				int JposSuit=-1, JposRank=-1;
				for(suit=0;suit<4;suit++){
					if(PATTERN[pat][suit]==1){
					    bitSuit |= (1<<suit);
						if(hands[suit][rank] == 1){
							hd |= CARDBIT(suit, rank);
						}else{
							JposSuit=suit, JposRank=rank;
						}
					}
				}
				Yaku cd(hd, bitSuit, num, rank, rank, JposSuit, JposRank);
				yaku->push_back(cd);
			}
		}
		
		//最後に5カード
		if(hands[0][rank] && hands[1][rank] && hands[2][rank] && hands[3][rank] && joker){//全部出せる
		    //int64 hd = IS_PAIR|IS_JUSED|IS_NUM(5);
		    int64 hd = IS_PAIR|IS_JUSED;
		    int JposSuit=4, JposRank=rank;
			hd|=CARDBIT(0, rank);hd|=CARDBIT(1, rank);hd|=CARDBIT(2, rank);hd|=CARDBIT(3, rank);
			Yaku cd(hd, 15, 5, rank, rank, JposSuit, JposRank);
			yaku->push_back(cd);
		}
        
	}//for(rank
}

void makeTankiFrom815(vector<Yaku> *yaku, const int hands[8][15]){
    //815配列から単騎役を作る
    int suit, rank;
    int joker = (hands[4][1]!=0);//jokerを持っている
	
	for(suit=0;suit<4;suit++){
		for(rank=1;rank<=13;rank++){
			if(hands[suit][rank]==1){
			    int bitSuit = (1<<suit);
			    //int64 hd = CARDBIT(suit, rank)|IS_NUM(1);
			    int64 hd = CARDBIT(suit, rank)|IS_TANKI;
				Yaku cd(hd, bitSuit, 1, rank, rank, -1, -1);
			    yaku->push_back(cd);
			}
		}
	}
	
	//joker単騎だしの検討
	if(joker){
	    //int64 hd = IS_JUSED|IS_NUM(1);
	    int64 hd = IS_JUSED|IS_TANKI;
		Yaku cd(hd, 0, 1, 0, 14, 0, 14);
	    yaku->push_back(cd);
	}
}

void printYakuVec(const vector<Yaku> &vecCards){
    for(int i=0;i<vecCards.size();i++){
        cout << i << endl;
        vecCards[i].printBit();
        cout << endl;
    }
}
void makePass(vector<Yaku> *yaku){
    //役集合にパスを入れる
	int64 hd = IS_PASS;
	Yaku cd(hd, 0, 0, 0, 0, -1, -1);
	yaku->push_back(cd);
}

bool isYaku1HigherThanYaku2(const Yaku &c1, const Yaku &c2){
    //革命のとき、第1引数が第2引数よりも小さいとき1を返す
    return ( c1.mRankR > c2.mRankR);
}

bool isYaku1LowerThanYaku2(const Yaku &c1, const Yaku &c2){
    //通常時（革命でない）とき、第1引数が第2引数よりも小さいとき1を返す
    return ( c1.mRankL < c2.mRankL);
}

void sortYakuByRank( vector<Yaku> *vecCards, bool isKakumei ){
    //弱い順に並び替える
    if( isKakumei ){//革命のとき
        sort( vecCards->begin(), vecCards->end(), isYaku1HigherThanYaku2 );
    }else{
        sort( vecCards->begin(), vecCards->end(), isYaku1LowerThanYaku2 );
    }
}

void makeYakuBFrom815(vector<Yaku> *tky, int hands[8][15], const Table &table){
    
    if(table.isOnset()){//空場
        makeKaidanFrom815(tky, hands);
        //std::cout << "kaidan" << tky->size() << std::endl;
        makePairFrom815(tky, hands);
        //std::cout << "pair" << tky->size() << std::endl;
        makeTankiFrom815(tky, hands);
        //std::cout << "tanki" << tky->size() << std::endl;
        //printVCard(tky);
    }else{
        if(table.isKaidan()){
            vector<Yaku> atky;
            makeKaidanFrom815(&atky, hands);
            //std::cout << "ak" << atky.size() << std::endl;
            //printVCard(&atky);
            sortKaidan(tky, &atky, table);
            //std::cout << "bk" << tky->size() << std::endl;
            //printVCard(tky);
        }else if(table.isPair()){
            vector<Yaku> atky;
            makePairFrom815(&atky, hands);
            //std::cout << "ap" << atky.size() << std::endl;
            //printVCard(&atky);
            sortPair(tky, &atky, table);
            //std::cout << "bp" << tky->size() << std::endl;
            //printVCard(tky);
        }else if(table.isTanki()){
            vector<Yaku> atky;
            makeTankiFrom815(&atky, hands);
            //printVCard(&atky);
            //std::cout << "at" << atky.size() << std::endl;
            sortTanki(tky, &atky, table);
            //std::cout << "bt" << tky->size() << std::endl;
            //printVCard(tky);
            
        }
        //printVCard(tky);
        makePass(tky);
    }
}	    
void sortAllYaku(vector<Yaku> *tky, const vector<Yaku> *atky, const Table &table){
    
    if(table.isOnset()){
    	//パスだけ除外する
    	for(int i=0;i<atky->size()-1;i++){
    		tky->push_back( (*atky)[i] );
    	}
    }else{
    	if(table.isTanki()){
    		sortTanki(tky, atky, table);
    	}
    	else if(table.isPair()){
    		sortPair(tky, atky, table);
    	}
    	else if(table.isKaidan()){
    		sortKaidan(tky, atky, table);
    	}
    }
	
}

void sortKaidan(vector<Yaku> *tky, const vector<Yaku> *atky, const Table &table){
    if(table.isKakumei()){//革命のとき
        for(int i=0;i<atky->size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( (*atky)[i].isKaidan() && 
                ((*atky)[i].mNum==table.mBafuda.mNum && (*atky)[i].mRankR<table.mBafuda.mRankL)
                ){
                if( !table.isShibari() || (table.isShibari() && table.mBafuda.mSuits==(*atky)[i].mSuits)){
                    tky->push_back((*atky)[i]);
                }
            }else if((*atky)[i].mNum==0){//パスは残す
                tky->push_back((*atky)[i]);
            }
        }
    }else{//革命ではないとき
        for(int i=0;i<atky->size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( ((*atky)[i].isKaidan()) &&
                 (*atky)[i].mNum==table.mBafuda.mNum && (*atky)[i].mRankL>table.mBafuda.mRankR)
                {
                if( !table.isShibari() || (table.isShibari() && table.mBafuda.mSuits==(*atky)[i].mSuits)){
                    tky->push_back((*atky)[i]);
                }
            }else if((*atky)[i].mNum==0){//パスは残す
                tky->push_back((*atky)[i]);
            }
        }
    }
}

void sortPair(vector<Yaku> *tky, const vector<Yaku> *atky, const Table &table){
    if(table.isKakumei()){//革命のとき
        for(int i=0;i<atky->size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( ((*atky)[i].isPair()) && 
               (*atky)[i].mNum==table.mBafuda.mNum && (*atky)[i].mRankL<table.mBafuda.mRankL
               ){
                if( !table.isShibari() || (table.isShibari() && table.mBafuda.mSuits==(*atky)[i].mSuits)){
                    tky->push_back((*atky)[i]);
                }
            }else if((*atky)[i].mNum==0){//パスは残す
                tky->push_back((*atky)[i]);
            }
        }
    }else{//革命ではないとき
        for(int i=0;i<atky->size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( ((*atky)[i].isPair()) && 
                (*atky)[i].mNum==table.mBafuda.mNum && (*atky)[i].mRankR>table.mBafuda.mRankR
                ){
                if( !table.isShibari() || (table.isShibari() && table.mBafuda.mSuits==(*atky)[i].mSuits)){
                    tky->push_back((*atky)[i]);
                }
            }else if((*atky)[i].mNum==0){//パスは残す
                tky->push_back((*atky)[i]);
            }
        }
    }
}

void sortTanki(vector<Yaku> *tky, const vector<Yaku> *atky, const Table &table){
    
    if(table.isJTanki()){//ジョーカー単騎はスペ３しか考えられない
        for(int i=0;i<atky->size();i++){
            if((*atky)[i].isSpade3()==1){//スぺ3を持っている
                tky->push_back((*atky)[i]);
                break;
            }else if((*atky)[i].mNum==0){//パスは残す
                tky->push_back((*atky)[i]);
            }
        }
    }
    else if(table.isKakumei()){//革命のとき
        for(int i=0;i<atky->size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if((*atky)[i].mNum==1 && (*atky)[i].mRankL<table.mBafuda.mRankL){
                if( !table.isShibari() || (table.isShibari() && table.mBafuda.mSuits==(*atky)[i].mSuits || (*atky)[i].isJTanki() )){
                    tky->push_back((*atky)[i]);
                }
            }else if((*atky)[i].mNum==0){//パスは残す
                tky->push_back((*atky)[i]);
            }
        }
    }
    else{//革命ではないとき
        for(int i=0;i<atky->size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if((*atky)[i].mNum==1 && (*atky)[i].mRankR>table.mBafuda.mRankR){
                if( !table.isShibari() || (table.isShibari() && table.mBafuda.mSuits==(*atky)[i].mSuits || (*atky)[i].isJTanki() )){
                    tky->push_back((*atky)[i]);
                }
            }else if((*atky)[i].mNum==0){//パスは残す
                tky->push_back((*atky)[i]);
            }
        }
    }
}
	    
	    /*
void removeLap(vector<Yaku> *vecCard, int64 cdBit){
    //役集合からCardをとり除く
    int i = 0;
    int64 mask = BITull(53)-1;//カードのぶんだけ（カードの左側までは見ない）
    while( i < (*vecCard).size() ){//カード集合の中を探索していく
    	if( ( mask & (*vecCard)[i].getCardBit() & cdBit ) == 0 ){//bitがかぶらない
            i++;//操作点を進める
        }else{//被った
            (*vecCard).erase( (*vecCard).begin() + i);//集合から取り除く
        }
    }
}
*/
	    