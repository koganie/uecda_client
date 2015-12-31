#include <algorithm>
#include "yaku.h"

//合法手役配列の操作用関数群である。
//vectorのsize()は符号無し整数が返るようなので
//のちのちいてれーたに変えよう。（なんだ？）
//引数の名前がよくわからないので後々これも変えよう。

void sortKaidan(vector<Card> *tky, const vector<Card> *atky, const Table &table){
    if(table.isKakumei()){//革命のとき
        for(int i=0;i<atky->size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( (*atky)[i].isKaidan() && 
                ((*atky)[i].mNum==table.mNum && (*atky)[i].mRankR<table.mRank)
                ){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==(*atky)[i].mSuits)){
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
                 (*atky)[i].mNum==table.mNum && (*atky)[i].mRankL>table.mRank)
                {
                if( !table.isShibari() || (table.isShibari() && table.mSuits==(*atky)[i].mSuits)){
                    tky->push_back((*atky)[i]);
                }
            }else if((*atky)[i].mNum==0){//パスは残す
                tky->push_back((*atky)[i]);
            }
        }
    }
}

void sortPair(vector<Card> *tky, const vector<Card> *atky, const Table &table){
    if(table.isKakumei()){//革命のとき
        for(int i=0;i<atky->size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( ((*atky)[i].isPair()) && 
               (*atky)[i].mNum==table.mNum && (*atky)[i].mRankL<table.mRank
               ){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==(*atky)[i].mSuits)){
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
                (*atky)[i].mNum==table.mNum && (*atky)[i].mRankR>table.mRank
                ){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==(*atky)[i].mSuits)){
                    tky->push_back((*atky)[i]);
                }
            }else if((*atky)[i].mNum==0){//パスは残す
                tky->push_back((*atky)[i]);
            }
        }
    }
}

void sortTanki(vector<Card> *tky, const vector<Card> *atky, const Table &table){
    
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
            if((*atky)[i].mNum==1 && (*atky)[i].mRankL<table.mRank){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==(*atky)[i].mSuits || (*atky)[i].isJTanki() )){
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
            if((*atky)[i].mNum==1 && (*atky)[i].mRankR>table.mRank){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==(*atky)[i].mSuits || (*atky)[i].isJTanki() )){
                    tky->push_back((*atky)[i]);
                }
            }else if((*atky)[i].mNum==0){//パスは残す
                tky->push_back((*atky)[i]);
            }
        }
    }
}


void makeYakuBFrom815(vector<Card> *tky, int hands[8][15], const Table &table){
    
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
            vector<Card> atky;
            makeKaidanFrom815(&atky, hands);
            //std::cout << "ak" << atky.size() << std::endl;
            //printVCard(&atky);
            sortKaidan(tky, &atky, table);
            //std::cout << "bk" << tky->size() << std::endl;
            //printVCard(tky);
        }else if(table.isPair()){
            vector<Card> atky;
            makePairFrom815(&atky, hands);
            //std::cout << "ap" << atky.size() << std::endl;
            //printVCard(&atky);
            sortPair(tky, &atky, table);
            //std::cout << "bp" << tky->size() << std::endl;
            //printVCard(tky);
        }else if(table.isTanki()){
            vector<Card> atky;
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

void makeAllYaku(vector<Card> *tky, const int hands[8][15]){
    
    /*
    if(table->isOnset()){
	    makeKaidanFrom815(tky, hands);
    	makePairFrom815(tky, hands);
    	makeTankiFrom815(tky, hands);
    	makePass(tky);
    }else{
	    vector<Card> atky;
    	if(table->isTanki()){
    		makeTankiFrom815(&atky, hands);
    		sortTanki(tky, &atky, table);
    	}
    	else if(table->isPair()){
    		makeTankiFrom815(&atky, hands);
    		sortPair(tky, &atky, table);
    	}
    	else if(table->isKaidan()){
    		makeKaidanFrom815(&atky, hands);
    		sortKaidan(tky, &atky, table);
    	}
    	makePass(tky);
    }
	*/
	makeKaidanFrom815(tky, hands);
    makePairFrom815(tky, hands);
    makeTankiFrom815(tky, hands);
    makePass(tky);
    
}
	    
void sortAllYaku(vector<Card> *tky, const vector<Card> *atky, const Table &table){
    
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

void sortKaidan2(vector<int> *parallel, const vector<Card> *atky, const Table &table){
    int i;
    
    if(table.isKakumei()){//革命のとき
        for(i=0;i<atky->size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( (*atky)[i].isKaidan() && 
                ((*atky)[i].mNum==table.mNum && (*atky)[i].mRankR<table.mRank)
                ){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==(*atky)[i].mSuits)){
                    parallel->push_back( i );
                }
            }else if((*atky)[i].mNum==0){//パスは残す
                parallel->push_back( i );
            }
        }
    }else{//革命ではないとき
        for(i=0;i<atky->size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( ((*atky)[i].isKaidan()) &&
                 (*atky)[i].mNum==table.mNum && (*atky)[i].mRankL>table.mRank)
                {
                if( !table.isShibari() || (table.isShibari() && table.mSuits==(*atky)[i].mSuits)){
                    parallel->push_back( i );
                }
            }else if((*atky)[i].mNum==0){//パスは残す
                parallel->push_back( i );
            }
        }
    }
}
	    
void sortPair2(vector<int> *parallel, const vector<Card> *atky, const Table &table){
    int i;
    
    if(table.isKakumei()){//革命のとき
        for(i=0;i<atky->size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( ((*atky)[i].isPair()) && 
               (*atky)[i].mNum==table.mNum && (*atky)[i].mRankL<table.mRank
               ){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==(*atky)[i].mSuits)){
                    parallel->push_back( i );
                }
            }else if((*atky)[i].mNum==0){//パスは残す
                parallel->push_back( i );
            }
        }
    }else{//革命ではないとき
        for(i=0;i<atky->size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( ((*atky)[i].isPair()) && 
                (*atky)[i].mNum==table.mNum && (*atky)[i].mRankR>table.mRank
                ){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==(*atky)[i].mSuits)){
                    parallel->push_back( i );
                }
            }else if((*atky)[i].mNum==0){//パスは残す
                parallel->push_back( i );
            }
        }
    }
}
	   
void sortTanki2(vector<int> *parallel, const vector<Card> *atky, const Table &table){
    int i;
    
    if(table.isJTanki()){//ジョーカー単騎はスペ３しか考えられない
        for(i=0;i<atky->size();i++){
            if((*atky)[i].isJTanki()==1){
                parallel->push_back( i );
                break;
            }else if((*atky)[i].mNum==0){//パスは残す
                parallel->push_back( i );
            }
        }
    }
    else if(table.isKakumei()){//革命のとき
        for(i=0;i<atky->size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if((*atky)[i].mNum==1 && (*atky)[i].mRankL<table.mRank){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==(*atky)[i].mSuits || (*atky)[i].isJTanki() )){
                    parallel->push_back( i );
                }
            }else if((*atky)[i].mNum==0){//パスは残す
                parallel->push_back( i );
            }
        }
    }
    else{//革命ではないとき
        for(i=0;i<atky->size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if((*atky)[i].mNum==1 && (*atky)[i].mRankR>table.mRank){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==(*atky)[i].mSuits || (*atky)[i].isJTanki() )){
                   parallel->push_back( i );
                }
            }else if((*atky)[i].mNum==0){//パスは残す
                parallel->push_back( i );
            }
        }
    }
}
	    
void sortAllYaku2(vector<int> *parallel, const vector<Card> *atky, const Table &table){
    //自分の手札から構成できる全合法手のうち（atky, 改名予定）
    //現在の場の状況において、（table）
    //出せる手役のみをピックアップする（parallel, 改名予定）
    if(table.isOnset()){
    	//パスだけ除外する（空場ではパスはすべきでないと信じている）
    	for(int i=0;i<atky->size()-1;i++){
    		parallel->push_back( i );
    	}
    }else{//各々の場に対して
    	if(table.isTanki()){
    		sortTanki2(parallel, atky, table);
    	}
    	else if(table.isPair()){
    		sortPair2(parallel, atky, table);
    	}
    	else if(table.isKaidan()){
    		sortKaidan2(parallel, atky, table);
    	}
    }
    
}

void pickKaidan(vector<Card> *parallel, const vector<Card> &atky){
    for(int i=0;i<atky.size();i++){
        if( atky[i].isKaidan() ){
            parallel->push_back( atky[i] );
        }
    }
}

void pickPair(vector<Card> *parallel, const vector<Card> &atky){
    for(int i=0;i<atky.size();i++){
        if( atky[i].isPair() ){
            parallel->push_back( atky[i] );
        }
    }
}

void pickTanki(vector<Card> *parallel, const vector<Card> &atky){
    for(int i=0;i<atky.size();i++){
        if( atky[i].isTanki() ){
            parallel->push_back( atky[i] );
        }
    }
}

void pickLegalKaidan(vector<Card> *parallel, const vector<Card> &atky, const Table &table){
    int i;
    
    if(table.isKakumei()){//革命のとき
        for(i=0;i<atky.size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( atky[i].isKaidan() && 
                (atky[i].mNum==table.mNum && atky[i].mRankR<table.mRank)
                ){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==atky[i].mSuits)){
                    parallel->push_back( atky[i] );
                }
            }
            /*
            else if(atky[i].mNum==0){//パスは残す
                parallel->push_back( atky[i] );
            }
            */
        }
    }else{//革命ではないとき
        for(i=0;i<atky.size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( (atky[i].isKaidan()) &&
                 atky[i].mNum==table.mNum && atky[i].mRankL>table.mRank)
                {
                if( !table.isShibari() || (table.isShibari() && table.mSuits==atky[i].mSuits)){
                    parallel->push_back( atky[i] );
                }
            }
            /*
            else if(atky[i].mNum==0){//パスは残す
                parallel->push_back( atky[i] );
            }
            */
        }
    }
}
	    
void pickLegalPair(vector<Card> *parallel, const vector<Card> &atky, const Table &table){
    int i;
    
    if(table.isKakumei()){//革命のとき
        for(i=0;i<atky.size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( atky[i].isPair() && 
               atky[i].mNum==table.mNum && atky[i].mRankL<table.mRank
               ){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==atky[i].mSuits)){
                    parallel->push_back( atky[i] );
                }
            }
            /*
            else if(atky[i].mNum==0){//パスは残す
                parallel->push_back( atky[i] );
            }
            */
        }
    }else{//革命ではないとき
        for(i=0;i<atky.size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( (atky[i].isPair()) && 
                atky[i].mNum==table.mNum && atky[i].mRankR>table.mRank
                ){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==atky[i].mSuits)){
                    parallel->push_back( atky[i] );
                }
            }
            /*
            else if(atky[i].mNum==0){//パスは残す
                parallel->push_back( atky[i] );
            }
            */
        }
    }
}
	   
void pickLegalTanki(vector<Card> *parallel, const vector<Card> &atky, const Table &table){
    int i;
    
    if(table.isJTanki()){//ジョーカー単騎はスペ３しか考えられない
        for(i=0; i < atky.size(); i++){
            if(atky[i].isSpade3()==1){
                parallel->push_back( atky[i] );
                break;
            }
            /*
            else if(atky[i].mNum==0){//パスは残す
                parallel->push_back( atky[i] );
            }
            */
        }
    }
    else if(table.isKakumei()){//革命のとき
        for(i=0; i < atky.size(); i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if(atky[i].mNum==1 && atky[i].mRankL<table.mRank){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==atky[i].mSuits || atky[i].isJTanki() )){
                    parallel->push_back( atky[i] );
                }
            }
            /*
            else if(atky[i].mNum==0){//パスは残す
                parallel->push_back( atky[i] );
            }
            */
        }
    }
    else{//革命ではないとき
        for(i=0; i < atky.size(); i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if(atky[i].mNum==1 && atky[i].mRankR>table.mRank){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==atky[i].mSuits || atky[i].isJTanki() )){
                   parallel->push_back( atky[i] );
                }
            }
            /*
            else if(atky[i].mNum==0){//パスは残す
                parallel->push_back( atky[i] );
            }
            */
        }
    }
}
	    
void pickAllLegalYaku(vector<Card> *parallel, const vector<Card> &atky, const Table &table){
    //自分の手札から構成できる全合法手のうち（atky, 改名予定）
    //現在の場の状況において、（table）
    //出せる手役のみをピックアップする（parallel, 改名予定）
    if(table.isOnset()){
    	//パスだけ除外する（空場ではパスはすべきでないと信じている）
    	for(int i=0;i<atky.size()-1;i++){
    		parallel->push_back( atky[i] );
    	}
    }else{//各々の場に対して
    	if(table.isTanki()){
    		pickLegalTanki(parallel, atky, table);
    	}
    	else if(table.isPair()){
    		pickLegalPair(parallel, atky, table);
    	}
    	else if(table.isKaidan()){
    		pickLegalKaidan(parallel, atky, table);
    	}
    }
    
}

void makeKaidanFrom815(vector<Card> *tky, const int hands[8][15]){
	//記述が品雑になるので場の状況は一切考えない
	//あとで合致するものだけ取り出す
	int joker = (hands[4][1]!=0);
	
	int suit, rank;
	for(suit=0; suit<4; suit++){//スートごと一列ずつ見る
		for(rank=0; rank<13;rank++){//始点を決定する（あり得るのは12 13 14マデ）
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
				    hd |= (length<7) ? IS_NUM(length) : IS_NUM(7);//6枚まではビットが使える
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
				    
				    if( rank<=6 && 6<=rank+length-1 )hd|=IS_8GIRI;//8切り扱いになる
					Card cd(hd, bitSuit, length, rank, rank+length-1, JposSuit, JposRank);
					tky->push_back(cd);
					if(joker_flag==1){//jokerを使わずに来ていれば、jokerに置き換えた階段も作ることができる
						for(i=rank;i<rank+length;i++){
							int64 mask = ~CARDBIT(suit, i);//joker使うとこだけ0
						    int64 hdj = (mask&hd)|IS_JUSED;//残すものは残す
							JposSuit=suit, JposRank=i;//jokerポジションは別変数のため全体を変える必要はない（のか？）
							Card cd(hdj, suit, length, rank, rank+length-1, JposSuit, JposRank);
							tky->push_back(cd);
					    }
					}
				}
			}//while(searching)
		}//for(order
	}//for(suit
}

void makePairFrom815(vector<Card> *tky, const int hands[8][15]){
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
		for(pat=0;pat<PATTERN_NUM; pat++){
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
						hd |= CARDBIT(suit, rank)|IS_NUM(num);
						bitSuit |= (1<<suit);
					}
				}
			    if(rank==6)hd|=IS_8GIRI;//8切り
				Card cd(hd, bitSuit, num, rank, rank, -1, -1);
				tky->push_back(cd);
				if(joker==1){//jokerに置き換えたバージョンを（8で使うくらいしか利点がわからない）
				    hd |= 0ull;
					for(suit=0;suit<4;suit++){//jokerに置き換えるスート
						if(PATTERN[pat][suit]==1){
						    int64 mask = ~CARDBIT(suit, rank);//ジョーカーを使うところだけ0
						    int64 hdj = (mask&hd)|IS_JUSED|IS_NUM(num);
							int JposSuit=suit, JposRank=rank;
							Card cd(hdj, bitSuit, num, rank, rank, JposSuit, JposRank);
				            tky->push_back(cd);
						}
					}
				}
			}else if(joker==1 && unmatch==1){//jokerを使えて、足りないのが1枚だけなら
				int64 hd = IS_PAIR|IS_JUSED|IS_NUM(num);
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
				Card cd(hd, bitSuit, num, rank, rank, JposSuit, JposRank);
				tky->push_back(cd);
			}
		}
		
		//最後に5カード
		if(hands[0][rank] && hands[1][rank] && hands[2][rank] && hands[3][rank] && joker){
		    int64 hd = IS_PAIR|IS_JUSED|IS_NUM(5);
		    int JposSuit=4, JposRank=rank;
			hd|=CARDBIT(0, rank);hd|=CARDBIT(1, rank);hd|=CARDBIT(2, rank);hd|=CARDBIT(3, rank);
			Card cd(hd, 15, 5, rank, rank, JposSuit, JposRank);
			tky->push_back(cd);
		}
	}//for(rank
}

void makeTankiFrom815(vector<Card> *tky, const int hands[8][15]){
	int suit, rank, pat;
    int joker = (hands[4][1]!=0);
	
	for(suit=0;suit<4;suit++){
		for(rank=1;rank<=13;rank++){
			if(hands[suit][rank]==1){
			    int bitSuit = (1<<suit);
			    int64 hd = CARDBIT(suit, rank)|IS_NUM(1);
				Card cd(hd, bitSuit, 1, rank, rank, -1, -1);
			    if(cd.isJTanki()){
			        std::cout << "hhhhhhh" << suit << " " << rank << " " << CARDBIT(suit, rank) << std::endl;
			        cd.printBit2();
			        exit(1);
			    }
			    tky->push_back(cd);
			}
		}
	}
	
	//joker単騎だしの検討
	if(joker){
	    int64 hd = IS_JUSED|IS_NUM(1);
		Card cd(hd, 0, 1, 14, 0, 0, 14);
	    tky->push_back(cd);
	}
}

void makePass(vector<Card> *tky){
	int64 hd = IS_PASS;
	Card cd(hd, 0, 0, 0, 0, -1, -1);
	tky->push_back(cd);
}

void sortYakuByRank( vector<Card> *vecCards, bool isKakumei ){
    //弱い順に並び替える
    if( isKakumei ){//革命のときは左側の大小を見る
        sort( vecCards->begin(), vecCards->end(), compYakuRankL );
    }else{
        sort( vecCards->begin(), vecCards->end(), compYakuRankR );
    }
}