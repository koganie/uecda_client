#ifndef MY_FUNC_FILE
#define MY_FUNC_FILE

//#define DEBUG

//#include "Card.h"     //カードのクラス
//#include "Players.h"  //プレイヤーのクラス
#include "Table.h"    //テーブルのクラス

bool compCardAndCard(Card *c1, Card *c2, bool is_kakumei);
bool compCardAndTable(Card *c1, Table *table);
//int setDust(int dust[8][15], int hands[8][15]);
//void updateDust(int dust[8][15], int bafuda[8][15]);

#endif

