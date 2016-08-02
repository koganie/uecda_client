
#include "myfunc.h"

bool compCardAndCard(Yaku *c1, Yaku *c2, bool is_kakumei){
    if(is_kakumei==1){//
        return (c1->mRankL < c2->mRankL);
    }
    else{
        return (c1->mRankR > c2->mRankR);
    }
}

/*
bool compCardAndTable(Yaku *c1, Table *table){
    if(table->isKakumei()==1){//
        return (c1->mRankL < table->mRank);
    }
    else{
        return (c1->mRankR > table->mRank);
    }
}
*/

/*
int setDust(int dust[8][15], int hands[8][15]){
    int i,j;
    for(i=0;i<4;i++){
        for(j=1;j<=13;j++){
            if(hands[i][j]!=0){
                dust[i][j] = 1;
            }
        }
    }
    if(hands[4][1]!=0){
        dust[4][1] = 1;
    }
}

void updateDust(int dust[8][15], int bafuda[8][15]){
    int i,j;
    for(i=0;i<5;i++){
        for(j=0;j<15;j++){
            if(bafuda[i][j]!=0){
                if(bafuda[i][j]==2){
                    dust[4][1] = 1;
                }else{
                    dust[i][j] = 1;
                }
            }
        }
    }
}
*/

