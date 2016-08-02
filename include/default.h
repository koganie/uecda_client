#ifndef DEFAULT_FILE
#define DEFAULT_FILE

#include <iostream>
#include <vector>

#include "Yaku.h"
#include "Table.h"

int selectSubmitCardsLikeDefault(Yaku *select_cards, const Table &table, const std::vector<Yaku> &yaku);
int selectBigCards(Yaku *yaku, const std::vector<Yaku> &allYaku);

#endif
