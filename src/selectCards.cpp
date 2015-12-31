#include <math.h>
#include "selectCards.h"

int selectByDelusion(Card &select_cards, const Table &table, const vector<Card> &yaku, const int dust[8][15], int hands[8][15]){
    
    vector<int> SIM_SCORE, SIM_COUNT;
    
    for(int i=0;i < yaku.size(); i++){
        SIM_SCORE.push_back(0);
        SIM_COUNT.push_back(0);
    }
    #ifdef DEBUG
    int count2 = 0;
    for(int j=0;j<5;j++){
        for(int k=0;k<15;k++){
            if(hands[j][k]!=0){
                count2++;
            }
        }
    }
    if(count2!=table.mPlayers.cards_num[table.mPlayers.turn]){
        cout << "zen" <<  count2 << " " << table.mPlayers.cards_num[table.mPlayers.turn] << " oreno tefuda cards num bukkoware!" << endl;
        exit(1);
    }
    #endif
    
    //各手に対してシミュレーションを行う
    //現在出せる合法手分だけ
    Table simTable = table;
    vector<Card> legalYaku;//操作用役集合
    pickAllLegalYaku( &legalYaku, yaku, table );//パスを除きこの局面で出せるすべての合法手を選定する
	
	//出せるものがないのならパスをする
	if( legalYaku.size() == 0 ){
	    makePass( &legalYaku );
	    select_cards = legalYaku[0];
		return 0;
	}
    
    //場が空ではなければパスも合法手に含める
    if( table.isOnset() ){
        makePass( &legalYaku );
    }
    
	//パス以外にできるのならば
    for(int idx=0;idx < legalYaku.size();idx++){
    	for(int cnt=0;cnt < 200;cnt++){
    	    vector<Card> tempYaku;
    	    //vecCopy(tempYaku, yaku);//全部の役集合をコピーする
    	    tempYaku = yaku;
    	    Delusion del(simTable, dust, tempYaku, simTable.mPlayers.turn);//妄想環境のセットアップ
        	int depth = 0;
            SIM_SCORE[idx] += del.startDelusion( legalYaku[idx], &depth );//idx
            SIM_COUNT[idx]++;
            #ifdef DEBUG
            cout << cnt << "sim done! " << "score is " << (double)SIM_SCORE[idx]/SIM_COUNT[idx] << " depth is "<< depth << endl;
            #endif
        }
    }
    
    #ifdef DEBUG1
    for(int idx=0;idx < legalYaku.size();idx++){
        std::cout << idx << ":" << SIM_SCORE[idx] << " " << SIM_COUNT[idx] << std::endl;
    }
    #endif
    
	//シミュレーションを回した合法手の中から評価が最大のものを探す
    vector<double> fin_score;
    int maxIdx = 0;
    for(int cnt=0;cnt < legalYaku.size(); cnt++){
        if(SIM_COUNT[cnt]!=0){
            fin_score.push_back( (double)SIM_SCORE[cnt]/ SIM_COUNT[cnt]);
            if(fin_score[cnt] > fin_score[maxIdx]){
                maxIdx = cnt;
            }
        }else{
            fin_score.push_back( 0 );
        }
    }
    
    select_cards = legalYaku[maxIdx];
    return 1;//全合法手リストでの対応する番号を送る
}

int selectLikeDefault(Card &select_cards, const Table &table, const vector<Card> &yaku, int unsubmitted[8][15], int hands[8][15]){
    
    int index;
    if(table.isOnset()){//リード局面（場が空である）
        //階段を探す
        vector<Card> kaidan;
        pickKaidan( &kaidan, yaku );//階段だけ集める
        if( kaidan.size() > 0 ){//階段を出せる！
            index = selectBigCards( kaidan );//もっともビッグ（多数枚, 塊が大きい）な役を入れる
            select_cards = kaidan[index];
            return index;
        }
        //階段が見つからなかったらペアを探す
        vector<Card> pair;
        pickPair( &pair, yaku );//ペアだけ集める
        if( pair.size() > 0 ){//ペアを出せる！
            index = selectBigCards( pair );//もっともビッグ（多数枚, 塊が大きい）な役を入れる
            select_cards = pair[index];
            return index;
        }
        //ペアも見つからなかったら単騎を探す
        vector<Card> tanki;
        pickTanki( &tanki, yaku);//単騎だけ集める
        if( tanki.size() > 0 ){//単騎を出せる！
            index = selectLowCards( tanki );//もっともな役を入れる
            select_cards = tanki[index];
            return index;
        }
        //単騎も見つからなかったら、手札はゼロのはず
        std::cout << "tefuda ga okashii no ja naika !?" << std::endl;
        exit(1);
    }else{//フォロー局面（場が何かしらある）
        vector<Card> legalYaku, kasu;//操作用役集合
        pickAllLegalYaku( &legalYaku, yaku, table );//パスを除きこの局面で出せるすべての合法手を選定する
        kasu = legalYaku;//コピーしてここから温存カードを取り除く（しぼりかす）
        if(table.isKaidan()){//場が階段のとき
            removeLap( &kasu, IS_JUSED );//役集合からjokerを使うものを消す（しぼる）
            if( kasu.size() > 0 ){//温存しても（絞り切っても）残っているなら
                sortYakuByRank( &kasu, table.isKakumei() );//役を弱い順に並び替える
                index = selectBigCards( kasu );//もっともビッグ（多数枚, 塊が大きい）な役を入れる
                select_cards = kasu[index];
                return index;
            }else if( legalYaku.size() > 0 ){//温存しないなら出せるか
                sortYakuByRank( &legalYaku, table.isKakumei() );//合法手役集合より
                index = selectBigCards( legalYaku );//もっともビッグな役を入れる
                select_cards = legalYaku[index];
                return index;
            }else{
                select_cards.demoPass();//パスを明示する
                return yaku.size();
            }
        }else if(table.isPair()){//場がペアの場合
            removeLap( &kasu, IS_JUSED );//役集合からjokerを使うものを消す（しぼる）
            if( kasu.size() > 0 ){//温存しても（絞り切っても）残っているなら
                sortYakuByRank( &kasu, table.isKakumei() );//役を弱い順に並び替える
                index = selectBigCards( kasu );//もっともビッグ（多数枚, 塊が大きい）な役を入れる
                select_cards = kasu[index];
                return index;
            }else if( legalYaku.size() > 0 ){//温存しないなら出せるか
                sortYakuByRank( &legalYaku, table.isKakumei() );//合法手役集合より
                index = selectBigCards( legalYaku );//もっともビッグな役を入れる
                select_cards = legalYaku[index];
                return index;
            }else{
                select_cards.demoPass();//パスを明示する
                return yaku.size();
            }
        }else if(table.isTanki()){
            //階段・ペアで使うことのできるカードを温存してみる
            for( int i=0; i < yaku.size(); i++ ){
                if(yaku[i].isKaidan()){//階段で出せるなら
                    removeLap( &kasu, yaku[i].getCardBit() );//役集合からそのカードを使うものを消す（しぼる）
                }
                else if(yaku[i].isPair()){//ペアで出せるなら
                    removeLap( &kasu, yaku[i].getCardBit() );//役集合からそのカードを使うものを消す（しぼる）
                }
            }
            removeLap( &kasu, IS_JUSED );//役集合からjokerを使うものを消す（しぼる）
            if( kasu.size() > 0 ){//温存しても（絞り切っても）残っているなら
                index = selectLowCards( kasu );//もっとも低い役を入れる
                select_cards = kasu[index];
                return index;
            }else if( legalYaku.size() > 0 ){//温存しないなら出せるか
                index = selectLowCards( legalYaku );//もっとも低い役を入れる
                select_cards = legalYaku[index];
                return index;
            }else{
                select_cards.demoPass();//パスを明示する
                return yaku.size();
            }
        }else{
            std::cout << "sonnna kyokumen ha nai..." << std::endl;
            exit(1);
        }
    }
}
