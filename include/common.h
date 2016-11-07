#include "bit.h"

void addCard(int c1[8][15], int c2[8][15]);
void deleteCard(int c1[8][15], int c2[8][15]);
void addCard2(int c1[8][15], int c2[8][15]);
void deleteCard2(int c1[8][15], int c2[8][15]);
void copyCard(int c1[8][15], int c2[8][15]);
void selectHighCard(int dest[8][15], int src[8][15], int num);
int countCard(int card[8][15]);

void addCardToBit(int64 *c1, int c2[8][15]);
