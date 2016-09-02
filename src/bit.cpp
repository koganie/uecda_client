#include <iostream>
#include "bit.h"

using namespace std;

int64 popCount64bit(int64 x){
    //64bit’†‚Ì1‚Ì”‚ð”‚¦‚é
    x = ((x & 0xaaaaaaaaaaaaaaaaUL) >> 1) 
      +  (x & 0x5555555555555555UL); 
    x = ((x & 0xccccccccccccccccUL) >> 2) 
      +  (x & 0x3333333333333333UL); 
    x = ((x & 0xf0f0f0f0f0f0f0f0UL) >> 4) 
      +  (x & 0x0f0f0f0f0f0f0f0fUL); 
    x = ((x & 0xff00ff00ff00ff00UL) >> 8) 
      +  (x & 0x00ff00ff00ff00ffUL); 
    x = ((x & 0xffff0000ffff0000UL) >> 16) 
      +  (x & 0x0000ffff0000ffffUL); 
    x = ((x & 0xffffffff00000000UL) >> 32) 
      +  (x & 0x00000000ffffffffUL); 
    return x; 
}

int64 conv815toBit(int x[8][15]){
    int64 temp = 0ull;
    for(int i=0;i<4;i++){
        for(int j=1;j<=13;j++){
            if( x[i][j]!=0) temp|=CARDBIT(i,j);
            //cout << x[i][j];
        }
        //cout<<endl;
    }
    if(x[4][1]!=0){
        temp|=IS_JUSED;
    }
    //printBit(temp);
    return temp;
}

void convBitTo815(int x[8][15], int64 y){
    for(int i=0;i<4;i++){
        for(int j=1;j<=13;j++){
            if( y&CARDBIT(i,j) ) x[i][j]=1;
        }
    }
    if( y&IS_JUSED ){
        x[4][1] = 2;
    }
}

void printBit(int64 x){
    for(int i=0;i<64; i++){
        int s = x&BITull(i) ? 1 : 0;
        cout << s;
    }
    cout<<endl;
}
