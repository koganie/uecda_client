#include <algorithm>
#include "yaku.h"

//合法手役配列の操作用関数群である。
//vectorのsize()は符号無し整数が返るようなので
//のちのちいてれーたに変えよう。（なんだ？）
//引数の名前がよくわからないので後々これも変えよう。



void makeAllYaku(vector<Card> *allYaku, const int hands[8][15]){
    //handsから作ることが可能なすべての役を作る
	makeKaidanFrom815(allYaku, hands);//階段
    makePairFrom815(allYaku, hands);//ペア
    makeTankiFrom815(allYaku, hands);//単騎
    makePass(allYaku);//パス
}

void pickKaidan(vector<Card> *kaidan, const vector<Card> &allYaku){
    for(int i=0;i<allYaku.size();i++){
        if( allYaku[i].isKaidan() ){
            kaidan->push_back( allYaku[i] );
        }
    }
}

void pickPair(vector<Card> *pair, const vector<Card> &allYaku){
    for(int i=0;i<allYaku.size();i++){
        if( allYaku[i].isPair() ){
            pair->push_back( allYaku[i] );
        }
    }
}

void pickTanki(vector<Card> *tanki, const vector<Card> &allYaku){
    for(int i=0;i<allYaku.size();i++){
        if( allYaku[i].isTanki() ){
            tanki->push_back( allYaku[i] );
        }
    }
}

void pickLegalKaidan(vector<Card> *legalYaku, const vector<Card> &allYaku, const Table &table){
    int i;
    
    if(table.isKakumei()){//革命のとき
        for(i=0;i<allYaku.size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( allYaku[i].isKaidan() && 
                (allYaku[i].mNum==table.mNum && allYaku[i].mRankR<table.mRank)
                ){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==allYaku[i].mSuits)){
                    legalYaku->push_back( allYaku[i] );
                }
            }
        }
    }else{//革命ではないとき
        for(i=0;i<allYaku.size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( (allYaku[i].isKaidan()) &&
                 allYaku[i].mNum==table.mNum && allYaku[i].mRankL>table.mRank)
                {
                if( !table.isShibari() || (table.isShibari() && table.mSuits==allYaku[i].mSuits)){
                    legalYaku->push_back( allYaku[i] );
                }
            }
        }
    }
}
	    
void pickLegalPair(vector<Card> *legalYaku, const vector<Card> &allYaku, const Table &table){
    int i;
    
    if(table.isKakumei()){//革命のとき
        for(i=0;i<allYaku.size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( allYaku[i].isPair() && 
               allYaku[i].mNum==table.mNum && allYaku[i].mRankL<table.mRank
               ){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==allYaku[i].mSuits)){
                    legalYaku->push_back( allYaku[i] );
                }
            }
        }
    }else{//革命ではないとき
        for(i=0;i<allYaku.size();i++){
            //階段で枚数が同じでかつ左側の強さが場札の強さより大きい
            if( (allYaku[i].isPair()) && 
                allYaku[i].mNum==table.mNum && allYaku[i].mRankR>table.mRank
                ){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==allYaku[i].mSuits)){
                    legalYaku->push_back( allYaku[i] );
                }
            }
        }
    }
}
	   
void pickLegalTanki(vector<Card> *legalYaku, const vector<Card> &allYaku, const Table &table){
    int i;
    
    if(table.isJTanki()){//ジョーカー単騎はスペ３しか考えられない
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
            if(allYaku[i].mNum==1 && allYaku[i].mRankL<table.mRank){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==allYaku[i].mSuits || allYaku[i].isJTanki() )){
                    legalYaku->push_back( allYaku[i] );
                }
            }
        }
    }
    else{//革命ではないとき
        for(i=0; i < allYaku.size(); i++){
            //階段で枚数が同じでかつ右側の強さが場札の強さより大きい
            if(allYaku[i].mNum==1 && allYaku[i].mRankR>table.mRank){
                if( !table.isShibari() || (table.isShibari() && table.mSuits==allYaku[i].mSuits || allYaku[i].isJTanki() )){
                   legalYaku->push_back( allYaku[i] );
                }
            }
        }
    }
}
	    
void pickAllLegalYaku(vector<Card> *legalYaku, const vector<Card> &allYaku, const Table &table){
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

void makeKaidanFrom815(vector<Card> *yaku, const int hands[8][15]){
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
				    hd |= (length<6) ? IS_NUM(length) : IS_NUM(6);//6?枚まではビットが使える
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
					yaku->push_back(cd);
					if(joker_flag==1){//jokerを使わずに来ていれば、jokerに置き換えた階段も作ることができる
						for(i=rank;i<rank+length;i++){
							int64 mask = ~CARDBIT(suit, i);//joker使うとこだけ0
						    int64 hdj = (mask&hd)|IS_JUSED;//残すものは残す
							JposSuit=suit, JposRank=i;//jokerポジションは別変数のため全体を変える必要はない（のか？）
							Card cd(hdj, suit, length, rank, rank+length-1, JposSuit, JposRank);
							yaku->push_back(cd);
					    }
					}
				}
			}//while(searching)
		}//for(order
	}//for(suit
}

void makePairFrom815(vector<Card> *yaku, const int hands[8][15]){
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
				yaku->push_back(cd);
				if(joker==1){//jokerに置き換えたバージョンを（8で使うくらいしか利点がわからない）
				    hd |= 0ull;
					for(suit=0;suit<4;suit++){//jokerに置き換えるスート
						if(PATTERN[pat][suit]==1){
						    int64 mask = ~CARDBIT(suit, rank);//ジョーカーを使うところだけ0
						    int64 hdj = (mask&hd)|IS_JUSED|IS_NUM(num);
							int JposSuit=suit, JposRank=rank;//jokerの位置
							Card cd(hdj, bitSuit, num, rank, rank, JposSuit, JposRank);
				            yaku->push_back(cd);
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
				yaku->push_back(cd);
			}
		}
		
		//最後に5カード
		if(hands[0][rank] && hands[1][rank] && hands[2][rank] && hands[3][rank] && joker){//全部出せる
		    int64 hd = IS_PAIR|IS_JUSED|IS_NUM(5);
		    int JposSuit=4, JposRank=rank;
			hd|=CARDBIT(0, rank);hd|=CARDBIT(1, rank);hd|=CARDBIT(2, rank);hd|=CARDBIT(3, rank);
			Card cd(hd, 15, 5, rank, rank, JposSuit, JposRank);
			yaku->push_back(cd);
		}
	}//for(rank
}

void makeTankiFrom815(vector<Card> *yaku, const int hands[8][15]){
    //815配列から単騎役を作る
    int suit, rank;
    int joker = (hands[4][1]!=0);//jokerを持っている
	
	for(suit=0;suit<4;suit++){
		for(rank=1;rank<=13;rank++){
			if(hands[suit][rank]==1){
			    int bitSuit = (1<<suit);
			    int64 hd = CARDBIT(suit, rank)|IS_NUM(1);
				Card cd(hd, bitSuit, 1, rank, rank, -1, -1);
			    yaku->push_back(cd);
			}
		}
	}
	
	//joker単騎だしの検討
	if(joker){
	    int64 hd = IS_JUSED|IS_NUM(1);
		Card cd(hd, 0, 1, 0, 14, 0, 14);
	    yaku->push_back(cd);
	}
}

void printCardVec(const vector<Card> &vecCards){
    for(int i=0;i<vecCards.size();i++){
        cout << i << endl;
        vecCards[i].printBit();
        cout << endl;
    }
}
void makePass(vector<Card> *yaku){
    //役集合にパスを入れる
	int64 hd = IS_PASS;
	Card cd(hd, 0, 0, 0, 0, -1, -1);
	yaku->push_back(cd);
}

void sortYakuByRank( vector<Card> *vecCards, bool isKakumei ){
    //弱い順に並び替える
    if( isKakumei ){//革命のとき
        sort( vecCards->begin(), vecCards->end(), isCard1WeakerThanCard2WhenKakumei );
    }else{
        sort( vecCards->begin(), vecCards->end(), isCard1WeakerThanCard2WhenNotKakumei );
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
/*
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
*/