#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

#include "common.h"
#include "myfunc.h"

#include "Game.h"
#include "changeCards.h"
#include "yaku.h"
#include "delusion.h"
#include "selectCards.h"

const int g_logging=0;                     //ログ取りをするか否かを判定するための変数

using namespace std;

int main(int argc,char* argv[]){
    //引数のチェック 引数に従ってサーバアドレス、接続ポート、クライアント名を変更
    Game game(argc, argv);
    
    //ゲームに参加
    game.connectToServer();
    
    while( !game.isAllGameEnd() ){//まだ全試合が終わっていないなら
        /* 新しい1ゲームの始まり */
        /* ここで1ゲームの間使う変数の準備を行う */

        //tableや手札等もgameに含めてもいいのかもしれないが、
        //一応1試合中に継続して使うものは出しておいてみる
        
        Table table;            //場の情報用の構造体 //中にPlayersもある
        
        int hands[8][15]={{0}};       //手札をおさめる変数
        int bafuda[8][15]={{0}};      //場札をおさめる変数
        int unsubmitted[8][15]={{0}};  //未提出カード集合（相手の持ちうるカード）
        
        /*ここまで*/
        
        game.receiveCards( hands );//最初のカードを受け取る
        //ここで富豪・大富豪の場合、貧民・大貧民から強いカードを搾取した後の手札が来ている。
        //つまり本来の手札+1,2枚の札が来ている
        //ここから貧民・大貧民にあげるカードを選ばなければいけない
        //UECdaのプロトコルによれば、手札としてもらう配列の[5][1]に交換するカードの枚数が入っている
        int give_cards_num = hands[5][1];//あげなきゃいけないカードは何枚あるか
        if( give_cards_num > 0 ){//交換する必要がある
            int change[8][15]={{0}};
            selectChangeCards(change, hands, give_cards_num);//交換する（押し付ける）カードを選択する
            game.sendCard(change);      //いらないカードをサーバに提示する
        }else{//カードを交換する必要がない場合
            //貧民・大貧民の場合、交換されるカードは"サーバーに勝手にとられてしまう"が
            //この時点では交換される前の手札が来ている。
            //つまりこの後、ゲームでもらう手札とこの時点での手札を比べると
            //富豪・大富豪から何を押し付けられたのかが確認できる。
        }
        
        while( !game.isOneGameEnd() ){            //1ゲームが終わるまでの繰り返し
            
            game.receiveCards( hands );//そのターンの手札を受け取り
            
            if( game.firstGame() ){ //最初回であれば
                table.firstGame(hands); //各プレイヤーの情報を保存
                //getState(hands);        //デフォルトの場の状態の読み出し
                setUnsubmitted(unsubmitted, hands);   //ごみに自分の手札を入れる
            }
            else{           //次回からは更新していく
                //getState(hands);        //デフォルトの場の状態の読み出し
                table.setBaInfo(hands); //場の状況の更新
            }
            
            //if( table.whoseTurn() == MY_PLAYER_NUM ){  //自分のターンであるなら
            if( table.isTurn( game.myPlayerNum() ) ){
                int cards[8][15]={{0}};
                Card select_cards;
                bool is_passed;
                
                vector<Card> myYaku;//自分の手札から生成できる合法手の集合体
                makeAllYaku(&myYaku, hands);//合法手をリストアップする
                
                selectByDelusion( select_cards, table, myYaku, unsubmitted, hands);//妄想による選択
                //selectLikeDefault( select_cards, table, myYaku, unsubmitted, hands );//標準クライアントライクな選択
                select_cards.setBitTo815( cards );//815配列に成形する
                
                game.sendCard( cards );//サーバに提示する
                is_passed = game.isPassed();//受理されたかどうか確認する
                
                if(is_passed && select_cards.mNum>0){//提出したつもりだったのに受理されなかった
                	cout << "sippai!" << endl;
                    table.print();
                	cout << "hands" << endl;
                    print815(hands);
                    cout << "bafuda" << endl;
                    print815(bafuda);
                    cout << "submit" << endl;
                    select_cards.printBit2();
                    cout << select_cards.isJTanki() << endl;
                	exit(1);
                }
                else{//提出した
                    cout << "BFD:";
                    table.mCard.printBit3();//場札は何か？
                    cout << " TFD:";
                    printBit3(hands);//何を持っているか
                    cout << "(" << myYaku.size()-1 << ")";//いくつの合法手が作れるか
                    cout <<  "=>";//そんな中
                    select_cards.printBit3();//提出した札は
                    cout << endl;
                }
                
            }
            
            game.receiveCards(bafuda);//場札を取得する
            table.setBafuda(bafuda);//tableに保存する
            updateUnsubmitted(unsubmitted, bafuda);//未提出札の更新

            game.checkGameEnd();
        }//1ゲームが終わるまでの繰り返しここまで
    }
        
    game.disconnectToServer();

    return 0;
}
