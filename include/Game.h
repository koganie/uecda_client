#ifndef GAME_DEFINE
#define GAME_DEFINE

/* クライアントは、サーバと接続する部分と、思考する部分と、大きく二つ分けることができる */
/* 接続部分は思考の記述に当たっては特に必要がない */
/* 思考をサーバに乗せる「座」としてクラスを定義する */

/* connection.c を大いに参考にして作成する（再構築） */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>

#define PROTOCOL_VERSION	20070		//プロトコルヴァージョンを表す整数
#define DEFAULT_SERVER		"127.0.0.1"	//デフォルトのサーバのアドレス 文字列で指定
#define DEFAULT_PORT		42485		//デフォルトのポート番号 整数で指定
#define DEFAULT_NAME		"simple"	//デフォルトのクライアント名 文字列で指定

class Game{
private:
    //ソケット通信用の変数
    int g_sockfd;
    struct sockaddr_in g_client_addr;
    
    //接続するサーバ、ポートを格納する変数
    char server_name[256];
    uint16_t port;
    
    //サーバに通知するクライアント名
    char client_name[15];
    
    int MY_PLAYER_NUM;          //自分のプレイヤー番号
    
    bool all_game_end_flag;    //全ゲームが終了したか
    bool one_game_end_flag;
    int game_count;           //ゲームの回数を記憶する
    
    bool first_time;            //ゲームの初回

public:
    Game(int argc,char* argv[]);
    
    void checkArg(int argc,char* argv[]);//引数の確認
    void connectToServer();//サーバーに接続する
    void disconnectToServer();//サーバーとの接続を解除する
    
    void checkGameEnd();//ゲームが終了したかサーバーに確認する
    bool isAllGameEnd();
    bool isOneGameEnd();
    void receiveCards(int card[8][15]);
    void sendCard(int card[8][15]);
    
    int isPassed();
    int myPlayerNum();
    
    bool isFirstTime();
};

#endif