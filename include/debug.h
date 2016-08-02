#ifndef DEBUG_H
#define DEBUG_H

#if 0
//Ç–ÇΩÇ∑ÇÁèoóÕÉÇÅ[Éh
#define COUT cout
#define PRINT815(data) print815(data)
#define DEBUGMODE
#else
#define COUT 0 && cout
#define PRINT815(data) 0
#endif

void print815(int data[8][15]);
void print515(int data[5][15]);
void printCardStr(int cards[8][15]);

#endif

