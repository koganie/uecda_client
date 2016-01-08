#include <math.h>
#include "default.h"
#include "yaku.h"

//#define DEBUG

int selectSubmitCardsLikeDefault(Card *select_cards, const Table &table, const vector<Card> &yaku){
    //UECda公式のデフォルトクライアントをまねた提出方法
    //手札から生成できる役の集合（yaku）から、
    //現在の局面（table）に対して提出する手を
    //select_cardsに代入する
    //（一部異なる動きをする）
    int index=0;
    if(table.isOnset()){//リード局面（場が空である）
        //空場なら何をだしてもよい
        
        //まず階段を探す
        vector<Card> kaidan;
        pickKaidan( &kaidan, yaku );//階段だけ集める
        if( kaidan.size() > 0 ){//階段を出せる！
            sortYakuByRank( &kaidan, table.isKakumei() );//弱い順に並び替える
            selectBigCards( select_cards, kaidan );//もっともビッグ（多数枚, 塊が大きい）な役を入れる
            return index;
        }
        
        //階段が見つからなかったらペアを探す
        vector<Card> pair;
        pickPair( &pair, yaku );//ペアだけ集める
        if( pair.size() > 0 ){//ペアを出せる！
            sortYakuByRank( &pair, table.isKakumei() );//弱い順に並び替える
            selectBigCards( select_cards, pair );//もっともビッグ（多数枚, 塊が大きい）な役を入れる
            return index;
        }
        
        //ペアも見つからなかったら単騎を探す
        vector<Card> tanki;
        pickTanki( &tanki, yaku);//単騎だけ集める
        if( tanki.size() > 0 ){//単騎を出せる！
            sortYakuByRank( &tanki, table.isKakumei() );//弱い順に並び替える
            *select_cards = tanki[0];//先頭（一番弱い）を入れる
            return 1;
        }
        //単騎も見つからなかったら、手札はゼロのはず
        std::cout << "tefuda ga okashii no ja naika !?" << std::endl;
        table.print();
        printCardVec(yaku);
        exit(1);
    }else{//フォロー局面（場が何かしらある）
        //場札に沿った提出をする必要があるので、まず出せる役だけを集める
        vector<Card> legalYaku;//操作用役集合
        pickAllLegalYaku( &legalYaku, yaku, table );//パスを除きこの局面で出せるすべての合法手を選定する
        
        if(table.isKaidan()){//場が階段のとき
            if( legalYaku.size() > 0 ){//出せる役があるのか
                sortYakuByRank( &legalYaku, table.isKakumei() );//弱い順に並び替える
                *select_cards = legalYaku[0];//先頭（一番弱い）を入れる
                return 1;
            }else{
                select_cards->demoPass();//パスを明示する
                return 0;
            }
        }else if(table.isPair()){//場がペアの場合
            vector<Card> kasu = legalYaku;//合法手をコピーしてここから温存カードを取り除いていく（しぼりかす）
            
            if(!table.isShibari()){//縛りではないときは
                for( int i=0; i < yaku.size(); i++ ){//手札から生成できる役のうち
                    if( (!yaku[i].isJUsed()) && yaku[i].isPair() && table.mNum < yaku[i].mNum ){//jokerを使わないペアでかつ枚数が場札よりも大きいものがある
                        removeLap( &kasu, yaku[i].getCardBit() );//そのカードを使うものを消す（しぼる）
                    }
                }
            }
            vector<Card> kasuOfKasu = kasu;//かす中のかす
            removeLap( &kasuOfKasu, IS_JUSED );//かすからさらにジョーカーを使うものを消す
            if( kasuOfKasu.size() > 0 ){//jokerを温存しても出せるか
                sortYakuByRank( &kasuOfKasu, table.isKakumei() );//弱い順に並べる
                *select_cards = kasuOfKasu[0];//先頭（一番弱いもの）を出す
                return 1;
            }else if( kasu.size() > 0 ){//多数枚を取り除きだせるか
                sortYakuByRank( &kasu, table.isKakumei() );//弱い順に並べる
                *select_cards = kasu[0];//先頭（一番弱いもの）を出す
                return 1;
            }
            /*
            //デフォルトクライアントはこの時提出しない
            else if( legalYaku.size() > 0 ){//温存しなければ出せる？
                sortYakuByRank( &legalYaku, table.isKakumei() );//弱い順に並べる
                select_cards = legalYaku[0];//先頭（一番弱いもの）を出す
                return 1;
            }
            */
            else{//提出すべきものがない
                select_cards->demoPass();//パスを明示する
                return 0;
            }
        }else if(table.isTanki()){
            //階段・ペアで使うことのできるカードを温存してみる
            vector<Card> kasu = legalYaku;//コピーしてここから温存カードを取り除く（しぼりかす）
            for( int i=0; i < yaku.size(); i++ ){//手札から生成できる役の集合のうち
                if(!yaku[i].isJUsed()){//jokerを使わずに
                    if(yaku[i].isKaidan() || yaku[i].isPair()){//階段かペアを作ることができるなら
                        removeLap( &kasu, yaku[i].getCardBit() );//役集合からそのカードを使うものを消す（しぼる）
                    }
                }
            }
            if( kasu.size() > 0 ){//温存しても（絞り切っても）残っているなら
                sortYakuByRank( &kasu, table.isKakumei() );//低い順に並び替える
                *select_cards = kasu[0];//もっとも低い（先頭）役を入れる
                return 1;
            }
            /*
            //デフォルトクライアントはこの時提出しない
            else if( legalYaku.size() > 0 ){//温存しなければ出せる？
                sortYakuByRank( &legalYaku, table.isKakumei() );//弱い順に並べる
                select_cards = legalYaku[0];//先頭（一番弱いもの）を出す
                return 1;
            }
            */
            else{
                select_cards->demoPass();//パスを明示する
                return 0;
            }
        }else{
            table.print();
            std::cout << "sonnna kyokumen ha nai..." << std::endl;
            exit(1);
        }
    }
}

