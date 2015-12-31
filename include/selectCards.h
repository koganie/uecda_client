#ifndef SELECT_CARDS_FILE
#define SELECT_CARDS_FILE

#include "Delusion.h"

int selectByDelusion(Card &select_cards, const Table &table, const vector<Card> &yaku, const int dust[8][15], int hands[8][15]);
int selectLikeDefault(Card &select_cards, const Table &table, const vector<Card> &yaku, int unsubmitted[8][15], int hands[8][15]);


#endif
