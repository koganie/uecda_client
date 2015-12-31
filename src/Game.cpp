
#include <iostream>

#include "Game.h"

Game::Game(int argc,char* argv[]){
    //server_name         = DEFAULT_SERVER;
    strncpy(server_name, DEFAULT_SERVER, sizeof(server_name));
    port                = DEFAULT_PORT;
    //�T�[�o�ɒʒm����N���C�A���g��
    //client_name         = DEFAULT_NAME;
    strncpy(client_name, DEFAULT_NAME, sizeof(client_name));
    
    first_game = true;
    all_game_end_flag   = false;    //�S�Q�[�����I��������
    one_game_end_flag   = false;
    game_count          = 0;           //�Q�[���̉񐔂��L������
    
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
    if(all_game_end_flag){  //�I����Ă���΂悢��
        return true;
    }
    else{                   //�܂��̏ꍇ��
        first_game = true;  //����t���O�𗧂Ă�
        game_count++;       //�Q�[���J�E���^�[��i�܂���
        one_game_end_flag = false;//�܂���蒼��
        return false;
    }
}
bool Game::isOneGameEnd(){
    return one_game_end_flag;
}

void Game::checkArg(int argc,char* argv[]){
  /*
    �n���ꂽ�R�}���h���C������^����ꂽ�����̏�����͂��A�K�v�ɉ�����
    �T�[�o�A�h���X�A�|�[�g�ԍ��A�N���C�A���g����ύX����B
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
    
    //�S�Ẵe�[�u���̗v�f���z�X�g�I�[�_�[����l�b�g���[�N�I�[�_�[�ɕϊ�
    for(int i=0; i<8; i++)
        for(int j=0; j<15; j++)
            net_table[i][j] = htonl(card[i][j]);
    
    //�ϊ������e�[�u���𑗐M
    int g_buf_len = write(g_sockfd, net_table, 480);
    
    if (g_buf_len < 0){
        std::cout << "fi" << std::endl;
        exit(1);
    }
}

int Game::isPassed(){
    int accept_flag;
    //accept_flag���T�[�o����󂯎��
    if((read(g_sockfd, &accept_flag, sizeof(accept_flag))) < 0 ){
        printf("failed to get accept sign.\n");
        exit(1);
    }
    else{
    }
    accept_flag =  ntohl(accept_flag);
    
    //UECda�̒ʐM�v���g�R���ł�8���Ԃ�ƃp�X�������ꂽ�Ƃ������Ƃ�����
    //����͈Ӑ}�I�ȃp�X�ł��A�s���Ȗ��̑��M�ł����Ȃ�
    if(accept_flag==8){
        return 1;
    }else{
        return 0;
    }
}


//���E���h�̍Ō�ɃQ�[�����I�������� �T�[�o����󂯂Ƃ� �t���O���X�V����
void Game::checkGameEnd(){
    int gameend_flag;
    //�Q�[���I���̃t���O���󂯎��
    if ((read(g_sockfd, &gameend_flag, sizeof(gameend_flag))) < 0 ){
    //��M���s�� ���b�Z�[�W��\������~
        printf("failed to check if the game was finished.\n");
        exit(1);
    }else{
        //��M������ �l�̃o�C�g�I�[�_�[�𒼂�
        gameend_flag=ntohl( gameend_flag);
    }
    //return one_gameend_flag;
    switch ( gameend_flag ){
        case 0: //0�̂Ƃ��Q�[���𑱂���
            one_game_end_flag=0;
            all_game_end_flag=0;
            break;
        case 1: //1�̂Ƃ� 1�Q�[���̏I��
            one_game_end_flag=1;
            all_game_end_flag=0;
            break;
        default: //���̑��̏ꍇ �S�Q�[���̏I��
            one_game_end_flag=1;
            all_game_end_flag=1;
            break;
    }
}

void Game::connectToServer(){
    //�\�P�b�g�̐���
    if ((g_sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        std::cout << "cannot make socket" << std::endl;
        //return(-1);
    }
    /* �|�[�g�ƃA�h���X�̐ݒ� */
    bzero((char*)&g_client_addr,sizeof(g_client_addr));
    g_client_addr.sin_family = PF_INET;
    g_client_addr.sin_port = htons(port);
    g_client_addr.sin_addr.s_addr = inet_addr(server_name);
    //IP�A�h���X�Ŏw�肳��Ă��Ȃ��Ƃ��A�z�X�g���̉��������݂�
    if (g_client_addr.sin_addr.s_addr == 0xffffffff) {
        struct hostent *host;
        host = gethostbyname(server_name);
        if (host == NULL) {
            printf("failed to gethostbyname() : %s.\n",server_name);
            //return -1;//�z�X�g�������Ɏ��s�����Ƃ��A-1��Ԃ�
            exit(1);
        }
        g_client_addr.sin_addr.s_addr = *(unsigned int *)host->h_addr_list[0];
    }
    /* �T�[�o�ɃR�l�N�g���� */
    if (connect(g_sockfd,(struct sockaddr *)&g_client_addr, sizeof(g_client_addr)) != 0){
        //return 0;
        //return;
        exit(1);
    }
    
    //sendProfile(user_name);     //�N���C�A���g�̏��𑗐M
    int profile[8][15]={{0}};
    profile[0][0] = PROTOCOL_VERSION;                   //2007�N�x�ł�錾
    for(int i=0;i<15;i++) profile[1][i] = (int)client_name[i];     //����Җ����e�[�u���Ɋi�[

    //���M
    sendCard(profile);

    //���g�̃v���C���[�ԍ����T�[�o������炤
    int my_playernum;
    if(read(g_sockfd, &my_playernum, sizeof(my_playernum)) > 0){
        my_playernum = ntohl(my_playernum);
    }
    else{
        printf("failed to get player number.\n");
        exit (1);
    }
    
    //return my_playernum; //���g�̃v���C���[�ԍ���Ԃ��B
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
