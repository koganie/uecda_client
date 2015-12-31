#include <iostream>

#include "changeCards.h"

using namespace std;

void selectChangeCards(int select_cards[8][15], int hands[8][15], int give_cards_num){
    if(hands[5][1] > 0 && hands[5][1]<100){
        int num = hands[5][1];          //カードの交換枚数
        int i, j;
        
        for(i=0;i<15 && num>0;i++){
            for(j=0;j<4 && num>0;j++){
                if(hands[j][i]==1){
                    select_cards[j][i] = 1;
                    num--;
                }
            }
        }
    }
}