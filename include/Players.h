#ifndef PLAYERS_DEFINE
#define PLAYERS_DEFINE

class Players{
public:
    int cards_num[5];//cards_num[i]��"�v���C���[�ԍ�i�̎����D��"�i�c��̎�D�����j
    int grades[5];  //grades[i]��"�v���C���[�ԍ�i�̐g��"
    int seats[5];   //seats[i]��"��i�ɍ����Ă���v���C���[�ԍ�"
    int sekijun[5]; //sekijun[i]��"�v���C���[�ԍ�i�̐Ȕԍ�"
    
    int turn;       //���݂̃^�[���i��o����Ԃł���j�� "�v���C���[�ԍ�"
    
    int isPassed;   //�v���C���[�ԍ�i�̓p�X�����Ă��邩�i�r�b�g�\�L�A(isPassed&(1<<i))!=0�Ȃ�p�X���Ă���A������͊܂܂�Ȃ��j
    int isGoaled;   //�v���C���[�ԍ�i�͂������Ă��邩�i�r�b�g�\�L�A(isGoaled&(1<<i))!=0�Ȃ炠�����Ă���j
    
    int getSeats();//���݂̃^�[���̐l�������Ă���Ȕԍ���Ԃ�
    int getCardsNum();//���݂̃^�[���̐l�̎����D����Ԃ�
    
    
    void set(int cards[8][15]);//���͂̓T�[�o���瑗���Ă����D�̔z��B�Q�[���J�n���Ɋe�v���C���[�̏����i�[����B
    void update(int cards[8][15]);//���͂̓T�[�o���瑗���Ă����D�̔z��Bset�����l��z���5�s�ڈȉ������čX�V����B
    
    void init();//�g���̂��H
    
    void recover();//�p�X��Ԃ��畜�A������
    
    //�V�~�����[�V�����p�̊֐��i�ʏ�̓T�[�o���瑗���Ă����񂩂�X�V����̂Ŏg���K�v���Ȃ��j
    void simGoal();//���݂̃v���C���[���オ�����ꍇ��isGoaled���X�V����
    int simPass();//���݂̃v���C���[���p�X�������ꍇ��isPassed���X�V���A�S���p�X������i�ꂪ���ꂽ�j1��Ԃ��B�łȂ����nextTurn()���ĂԁB
    void nextTurn();//turn�����̐l�ɂ���B
    void simSubmit(const Card &cd);//�J�[�h���o�����㏈���B�p�X�������ꍇ��simPass���ĂԂ̂ł���͌Ă΂Ȃ��B
    
    void print() const;//�e�ϐ��̒l�̏o�́i�f�o�b�O�p�j
};

#endif