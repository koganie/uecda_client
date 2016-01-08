#ifndef COMMON_FILE
#define COMMON_FILE

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
/*
typedef unsigned long long int cardBit;
typedef unsigned long long int fieldBit;
*/
typedef unsigned long long int int64;

#define BITi(num)	(1		<<	(num))//int�ɑ΂���
#define BITu(num)	(1ul	<<	(num))//unsigned int�ɑ΂���
#define BITull(num)	(1ull	<<	(num))//unsigned long long int�ɑ΂���
#define CARDBIT(suit, rank)	BITull(suit*13 + (rank-1))//815�z��Ɠ����悤�Ȋ��o��bit���Z���s��
//�J�[�h�r�b�g�ɑ΂��鏈��
/*
#define SUITS(s)    BITull(53+s)
#define IS_KAIDAN   BITull(58)
#define IS_PAIR     BITull(59)
//#define IS_TANKI    BIT(61)
//#define IS_PASS     BIT(61)
#define IS_JOKER    BITull(60)//joker�P�R�̂��ƁAjoker���g���Ă��邩�ł͂Ȃ�
#define IS_KAKUMEI  BITull(61)
#define IS_SHIBARI  BITull(62)
#define IS_8GIRI    BITull(63)
*/
//13*3+13-1 = 39+12 = 51
#define IS_SPADE3   BITull(0)
#define IS_JUSED	BITull(52)//joker���g���Ă���
#define IS_KAIDAN   BITull(53)
#define IS_PAIR     BITull(54)
//#define IS_TANKI    BITull(55)
#define IS_PASS     BITull(55)
//#define IS_JTANKI   BITull(57)//joker�P�R�̂��ƁAjoker���g���Ă��邩�ł͂Ȃ�
//#define IS_KAKUMEI  BITull(58)
//#define IS_SHIBARI  BITull(59)
#define IS_8GIRI    BITull(56)
#define IS_NUM(num) BITull(56+num)//�J�[�h�����͉�����?1�ȏオ����


/*
#define IS_BA_ONSET     BITi(0)
#define IS_BA_KAIDAN    BITi(1)
#define IS_BA_PAIR      BITi(2)
#define IS_BA_TANKI     BITi(3)
#define IS_BA_KAKUMEI   BITi(4)
#define IS_BA_SHIBARI   BITi(5)
#define IS_BA_JOKER     BITi(6)
*/
//��r�b�g�ɑ΂��鏈��
#define IS_BA_ONSET     BITu(0)
#define IS_BA_KAIDAN    BITu(1)
#define IS_BA_PAIR      BITu(2)
#define IS_BA_TANKI     BITu(3)
#define IS_BA_KAKUMEI   BITu(4)
#define IS_BA_SHIBARI   BITu(5)
#define IS_BA_JOKER     BITu(6)

void print515(int cards[8][15]);	//5*15�`���ŕ\�������� //�J�[�h�W���͂���
void print815(int cards[8][15]);	//8*15�`���ŕ\�������� //�Q�[���̏����܂߂�Ƃ��Ƃ�
void printBit3(int cards[8][15]);   //
void copy815(int dest[8][15], int src[8][15]);	//8*15�`���̔z��̃R�s�[
int count815(int cards[8][15]);		//8*15�`����0�łȂ�����Ԃ�
int compCard(int a[8][15], int b[8][15]);
void setGomi(int gomi[8][15], int hands[8][15]);
void updateGomi(int gomi[8][15], int hands[8][15]);

#endif
