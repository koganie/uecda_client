#include "common.h"

void print515(int cards[8][15]){
    int i,j;
    for(i=0;i<5;i++){
        for(j=0;j<15;j++){
            printf("%d ", cards[i][j]);
        }
        printf("\n");
    }
}

void print815(int cards[8][15]){
    int i,j;
    for(i=0;i<8;i++){
        for(j=0;j<15;j++){
            printf("%d ", cards[i][j]);
        }
        printf("\n");
    }
}

void copy815(int dest[8][15], int src[8][15]){
    int i,j;
    for(i=0;i<8;i++){
        for(j=0;j<15;j++){
            dest[i][j] = src[i][j];
        }
    }
}

int count815(int cards[8][15]){
    int i,j;
    int cnt=0;
    for(i=0;i<8;i++){
        for(j=0;j<15;j++){
            if(cards[i][j]!=0){
                cnt++;
            }
        }
    }
    return cnt;
}

int compCard(int a[8][15], int b[8][15]){
    int i,j;
    for(i=0;i<5;i++){
        for(j=0;j<15;j++){
            if(a[i][j]!=b[i][j]){
                return 0;
            }
        }
    }
    return 1;
}

void setUnsubmitted(int unsubmitted[8][15], int hands[8][15]){
    int i,j;
    for(i=0;i<4;i++){
        for(j=1;j<=13;j++){
            if(hands[i][j]!=0){
                unsubmitted[i][j] = 1;
            }
        }
    }
    if(hands[4][1]!=0){
        unsubmitted[4][1] = 1;
    }
}

void updateUnsubmitted(int unsubmitted[8][15], int bafuda[8][15]){
    int i,j;
    for(i=0;i<5;i++){
        for(j=0;j<15;j++){
            if(bafuda[i][j]!=0){
                if(bafuda[i][j]==2){
                    unsubmitted[4][1] = 1;
                }else{
                    unsubmitted[i][j] = 1;
                }
            }
        }
    }
}

void printBit3(int cards[8][15]){
    std::string SUIT="SHDC";
    std::string RANK="-34567890JQKA2";
    for(int j=1;j<=13;j++){
        for(int i=0;i<4;i++){
            if( cards[i][j]!=0 ){
                std::cout << SUIT[i] << RANK[j];
            }
        }
    }
    if(cards[4][1]!=0){
        std::cout << "*";
    }
}
