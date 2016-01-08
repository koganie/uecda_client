#ifndef PLAYERS_DEFINE
#define PLAYERS_DEFINE

class Players{
public:
    int cards_num[5];//cards_num[i]は"プレイヤー番号iの持ち札数"（残りの手札枚数）
    int grades[5];  //grades[i]は"プレイヤー番号iの身分"
    int seats[5];   //seats[i]は"席iに座っているプレイヤー番号"
    int sekijun[5]; //sekijun[i]は"プレイヤー番号iの席番号"
    
    int turn;       //現在のターン（提出する番である）の "プレイヤー番号"
    
    int isPassed;   //プレイヤー番号iはパスをしているか（ビット表記、(isPassed&(1<<i))!=0ならパスしている、あがりは含まれない）
    int isGoaled;   //プレイヤー番号iはあがっているか（ビット表記、(isGoaled&(1<<i))!=0ならあがっている）
    
    int getSeats();//現在のターンの人が座っている席番号を返す
    int getCardsNum();//現在のターンの人の持ち札数を返す
    
    
    void set(int cards[8][15]);//入力はサーバから送られてくる手札の配列。ゲーム開始時に各プレイヤーの情報を格納する。
    void update(int cards[8][15]);//入力はサーバから送られてくる手札の配列。setした値を配列の5行目以下を見て更新する。
    
    void init();//使うのか？
    
    void recover();//パス状態から復帰させる
    
    //シミュレーション用の関数（通常はサーバから送られてくる情報から更新するので使う必要がない）
    void simGoal();//現在のプレイヤーが上がった場合にisGoaledを更新する
    int simPass();//現在のプレイヤーがパスをした場合にisPassedを更新し、全員パスしたら（場が流れた）1を返す。でなければnextTurn()を呼ぶ。
    void nextTurn();//turnを次の人にする。
    void simSubmit(const Card &cd);//カードを提出した後処理。パスをした場合はsimPassを呼ぶのでこれは呼ばない。
    
    void print() const;//各変数の値の出力（デバッグ用）
};

#endif