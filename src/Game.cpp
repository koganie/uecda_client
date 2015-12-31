
#include <iostream>

#include "Game.h"

Game::Game(int argc,char* argv[]){
    //server_name         = DEFAULT_SERVER;
    strncpy(server_name, DEFAULT_SERVER, sizeof(server_name));
    port                = DEFAULT_PORT;
    //サーバに通知するクライアント名
    //client_name         = DEFAULT_NAME;
    strncpy(client_name, DEFAULT_NAME, sizeof(client_name));
    
    first_game = true;
    all_game_end_flag   = false;    //全ゲームが終了したか
    one_game_end_flag   = false;
    game_count          = 0;           //ゲームの回数を記憶する
    
    const char Option[]="[-h server_adress] [-p port] [-n user_name]";
    int        arg_count=1;

    while(arg_count<argc){
        if( strcmp(argv[arg_count],"--help")==0){
            printf("usage : %s %s\n",argv[0],Option);
            exit(0);
	    }else if (strcmp(argv[arg_count],"-h")==0){
            arg_count++;
            if (arg_count<argc){
	            strcpy(server_name,argv[arg_count]);
            }else{
	            printf("%s -h hostname\n",argv[0]);
	            exit(1);
            }
        }else if ((strcmp(argv[arg_count],"-p"))==0){
            arg_count++;
            if (arg_count<argc){
	            port = (uint16_t)atoi(argv[arg_count]);
            }else{
    	        printf("%s -p port\n",argv[0]);
	            exit(1);
            }
        }else if ((strcmp(argv[arg_count],"-n"))==0){
            arg_count++;
            if (arg_count<argc){
	            strcpy(client_name ,argv[arg_count]);
            }else{
    	        printf("%s -n user_name\n",argv[0]);
	            exit(1);
            }
        }else{
            printf("%s : unknown option : %s \n",argv[0],argv[arg_count]);
            printf("usage : %s %s\n",argv[0],Option);
            exit(1);
        }
        arg_count++;
    }
}

bool Game::isAllGameEnd(){
    if(all_game_end_flag){  //終わっていればよいが
        return true;
    }
    else{                   //まだの場合は
        first_game = true;  //初回フラグを立てる
        game_count++;       //ゲームカウンターを進ませる
        one_game_end_flag = false;//またやり直し
        return false;
    }
}
bool Game::isOneGameEnd(){
    return one_game_end_flag;
}

void Game::checkArg(int argc,char* argv[]){
  /*
    渡されたコマンドラインから与えられた引数の情報を解析し、必要に応じて
    サーバアドレス、ポート番号、クライアント名を変更する。
  */
    const char Option[]="[-h server_adress] [-p port] [-n user_name]";
    int        arg_count=1;

    while(arg_count<argc){
        if( strcmp(argv[arg_count],"--help")==0){
            printf("usage : %s %s\n",argv[0],Option);
            exit(0);
	    }else if (strcmp(argv[arg_count],"-h")==0){
            arg_count++;
            if (arg_count<argc){
	            strcpy(server_name,argv[arg_count]);
            }else{
	            printf("%s -h hostname\n",argv[0]);
	            exit(1);
            }
        }else if ((strcmp(argv[arg_count],"-p"))==0){
            arg_count++;
            if (arg_count<argc){
	            port = (uint16_t)atoi(argv[arg_count]);
            }else{
    	        printf("%s -p port\n",argv[0]);
	            exit(1);
            }
        }else if ((strcmp(argv[arg_count],"-n"))==0){
            arg_count++;
            if (arg_count<argc){
	            strcpy(client_name ,argv[arg_count]);
            }else{
    	        printf("%s -n user_name\n",argv[0]);
	            exit(1);
            }
        }else{
            printf("%s : unknown option : %s \n",argv[0],argv[arg_count]);
            printf("usage : %s %s\n",argv[0],Option);
            exit(1);
        }
        arg_count++;
    }
}

void Game::receiveCards(int card[8][15]){
    uint32_t net_table[8][15];
    int g_buf_len = read(g_sockfd,net_table, 480);
    for(int i=0; i<8; i++)
        for(int j=0; j<15; j++)
            card[i][j] = ntohl(net_table[i][j]);
    
    if (g_buf_len < 0){
        std::cout << "fa" << std::endl;
        exit(1);
    }
}

void Game::sendCard(int card[8][15]){
    uint32_t net_table[8][15];
    
    //全てのテーブルの要素をホストオーダーからネットワークオーダーに変換
    for(int i=0; i<8; i++)
        for(int j=0; j<15; j++)
            net_table[i][j] = htonl(card[i][j]);
    
    //変換したテーブルを送信
    int g_buf_len = write(g_sockfd, net_table, 480);
    
    if (g_buf_len < 0){
        std::cout << "fi" << std::endl;
        exit(1);
    }
}

int Game::isPassed(){
    int accept_flag;
    //accept_flagをサーバから受け取る
    if((read(g_sockfd, &accept_flag, sizeof(accept_flag))) < 0 ){
        printf("failed to get accept sign.\n");
        exit(1);
    }
    else{
    }
    accept_flag =  ntohl(accept_flag);
    
    //UECdaの通信プロトコルでは8が返るとパス扱いされたということを示す
    //これは意図的なパスでも、不正な役の送信でも違わない
    if(accept_flag==8){
        return 1;
    }else{
        return 0;
    }
}


//ラウンドの最後にゲームか終ったかを サーバから受けとり フラグを更新する
void Game::checkGameEnd(){
    int gameend_flag;
    //ゲーム終了のフラグを受け取る
    if ((read(g_sockfd, &gameend_flag, sizeof(gameend_flag))) < 0 ){
    //受信失敗時 メッセージを表示し停止
        printf("failed to check if the game was finished.\n");
        exit(1);
    }else{
        //受信成功時 値のバイトオーダーを直す
        gameend_flag=ntohl( gameend_flag);
    }
    //return one_gameend_flag;
    switch ( gameend_flag ){
        case 0: //0のときゲームを続ける
            one_game_end_flag=0;
            all_game_end_flag=0;
            break;
        case 1: //1のとき 1ゲームの終了
            one_game_end_flag=1;
            all_game_end_flag=0;
            break;
        default: //その他の場合 全ゲームの終了
            one_game_end_flag=1;
            all_game_end_flag=1;
            break;
    }
}

void Game::connectToServer(){
    //ソケットの生成
    if ((g_sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        std::cout << "cannot make socket" << std::endl;
        //return(-1);
    }
    /* ポートとアドレスの設定 */
    bzero((char*)&g_client_addr,sizeof(g_client_addr));
    g_client_addr.sin_family = PF_INET;
    g_client_addr.sin_port = htons(port);
    g_client_addr.sin_addr.s_addr = inet_addr(server_name);
    //IPアドレスで指定されていないとき、ホスト名の解決を試みる
    if (g_client_addr.sin_addr.s_addr == 0xffffffff) {
        struct hostent *host;
        host = gethostbyname(server_name);
        if (host == NULL) {
            printf("failed to gethostbyname() : %s.\n",server_name);
            //return -1;//ホスト名解決に失敗したとき、-1を返す
            exit(1);
        }
        g_client_addr.sin_addr.s_addr = *(unsigned int *)host->h_addr_list[0];
    }
    /* サーバにコネクトする */
    if (connect(g_sockfd,(struct sockaddr *)&g_client_addr, sizeof(g_client_addr)) != 0){
        //return 0;
        //return;
        exit(1);
    }
    
    //sendProfile(user_name);     //クライアントの情報を送信
    int profile[8][15]={{0}};
    profile[0][0] = PROTOCOL_VERSION;                   //2007年度版を宣言
    for(int i=0;i<15;i++) profile[1][i] = (int)client_name[i];     //制作者名をテーブルに格納

    //送信
    sendCard(profile);

    //自身のプレイヤー番号をサーバからもらう
    int my_playernum;
    if(read(g_sockfd, &my_playernum, sizeof(my_playernum)) > 0){
        my_playernum = ntohl(my_playernum);
    }
    else{
        printf("failed to get player number.\n");
        exit (1);
    }
    
    //return my_playernum; //自身のプレイヤー番号を返す。
    MY_PLAYER_NUM = my_playernum;
}

void Game::disconnectToServer(){
    if( close(g_sockfd)!=0 ){
        printf("failed to close socket\n");
        exit(1);
    }
}

bool Game::firstGame(){
    if(first_game){
        first_game = false;
        return true;
    }
    else{
        return false;
    }
}

int Game::myPlayerNum(){
    return MY_PLAYER_NUM;
}
