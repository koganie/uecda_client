
#include "Card.h"

using namespace std;

Card::Card(int64 cd, int suits, int num, int rank, int rank2, int jps, int jpr){
    mCardBit = cd;//���͂�cd�̑������͂��łɏo���オ�������̂�z�肵�Ă���
    
    mSuits = suits;
    mNum = num;
    mRankR = rank2;//�E�[
    mRankL = rank;  //���[
    mJposSuit = jps;
    mJposRank = jpr;
    
    bzero(mCards, sizeof(mCards));
    setBitTo815( mCards );//815�z��ɂ��i�[����
}

bool Card::isKaidan() const{
    return (mCardBit&(IS_KAIDAN))!=0;
}
bool Card::isPair() const{
    return (mCardBit&(IS_PAIR))!=0;
}
bool Card::isTanki() const{
    return mNum==1;
}
bool Card::isJTanki() const{
    return ( (mCardBit&IS_JUSED)!=0 && (mCardBit&IS_NUM(1))!=0);//���������Ă���
}
bool Card::isKakumei() const{
    if(isKaidan() && mNum>=5 || isPair() && mNum>=4)return 1;
    else return 0;
}

bool Card::is8giri() const{
    return (mCardBit&(IS_8GIRI))!=0;
}
bool Card::isSpade3() const{
    return (mCardBit&(IS_SPADE3))!=0;
}
bool Card::isPass() const{
    return (mNum==0) ? 1 : 0;
}
int64 Card::getCardBit() const{
    return mCardBit;
}
    
void Card::clear(){
    mCardBit = 0ull;
    mNum = 0;
    mRankR = 0;
    mRankL = 0;
    mJposSuit = -1;
    mJposRank = -1;
}
    
void Card::init(){
    clear();
    mNum=0;mRankR=0;mRankL=0;
}

void Card::demoPass(){
    clear();
}
    
void Card::setBitTo815(int dest[8][15]) const{
    int i,j;
    for(i=0;i<4;i++){
        for(j=1;j<=13;j++){
            if(mCardBit&BITull(i*13+(j-1))){
                dest[i][j]=1;
            }else{
                dest[i][j]=0;
            }
        }
    }
    if(mJposSuit>=0 && mJposRank>=0){
        dest[mJposSuit][mJposRank]=2;
    }
}

void Card::printBit() const{
    int temp[8][15]={{0}};
    std::cout << "kdn" << isKaidan() << ", pir" <<isPair() 
    << /*", jok" << isJoker() << */ ", kkm" << isKakumei()
    << /*", sbr" << isShibari() <<*/ ", 8g" << is8giri() 
    << ", num" << mNum << ", rktT" << mRankR << ", rkr" << mRankL 
    << ", suit" << mSuits << std::endl;
    
    setBitTo815(temp);
    print515(temp);
}

void Card::printBit2() const{
    for(int i=0;i<4;i++){
        for(int j=1;j<=13;j++){
            if( mCardBit&BITull(i*13+(j-1)) ){
                std::cout << "1 ";
            }else{
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "S3" << isSpade3() << " JT" << isJTanki() << " KA" << isKaidan()
    << " PA" << isPair() << " PA" << isPass() << " 8G" << is8giri() << std::endl;
    for(int i=0;i<5;i++){
        std::cout << "N" << i << " " << ((mCardBit&IS_NUM(i))!=0) << ",";
    }
    std::cout << "N" << 5 << " " << ((mCardBit&IS_NUM(5))!=0) << std::endl;
}

void Card::printBit3() const{
    std::string SUIT="SHDC";
    std::string RANK="-34567890JQKA2";
    for(int j=1;j<=13;j++){
        for(int i=0;i<4;i++){
            if( i==mJposSuit && j==mJposRank ){
                std::cout << SUIT[i] << RANK[j] << "*";
            }else if( (mCardBit&BITull(i*13+(j-1)))!=0 ){
                std::cout << SUIT[i] << RANK[j];
            }
        }
    }
}

void Card::set815ToBit(int src[8][15]){

    int i, j;
    mCardBit = 0ULL;
    for(i=0;i<4;i++){
        //joker�̈ʒu
        if(src[i][0]==2){
            mJposSuit = i;
            mJposRank = 0;
        }
        if(src[i][14]==2){
            mJposSuit = i;
            mJposRank = 14;
        }
        //�ʏ�J�[�h�̈ʒu
        for(j=1;j<=13;j++){
            if(src[i][j]==0){
            }else if(src[i][j]==1){
                mCardBit |= BITull(i*13 + (j-1));
            }else if(src[i][j]==2){
                mJposSuit = i;
                mJposRank = j;
            }
        }
    }
    //joker�̈ʒu
    for(j=0;j<=14;j++){
        if(src[4][j]==2){
            mJposSuit = 4;
            mJposRank = j;
        }
    }
    
}

void Card::setBit(int src[8][15]){
    //bit�ɖ��ߍ���53����
    mCardBit = 0ULL;
    mSuits = 0;
    set815ToBit(src);//card��bit�ɓ��ꍞ�ށB
    
    int i=0,j=0,count=0;
    //�J�[�h�̂���ʒu��T��
    while(j<15&&src[i][j]==0){
	    i++;
		if(i==4){
    		j++;
	    	i=0;
	    }
    }
    
    int joker_flag=0;
    if(src[i][j] == 2) joker_flag = 1;
    //�K�i���ۂ�
    if(j<14 && src[i][j+1]>0){
    	mCardBit |= IS_KAIDAN;
    }
    //�����𐔂��� �܂������𒲂ׂ�
   	if( isKaidan() ){
   		//�K�i
	    while(j+count<15 && src[i][j+count]>0){
		    if(j+count==6)  mCardBit |= IS_8GIRI;
		    count++;
	    }
   	    mRankR = j+count-1;
        mRankL = j;
	    mSuits = (1<<i);
    }else{
   		//�����g
        for(;i<5;i++){
    		if(src[i][j]>0){
	    		count++;
		    	mSuits |= (1<<i);
		    }
	    }
   		if(count==1&&joker_flag==1){//joker�P�R
    		mRankR = 14;
    		mRankL = 0;
   		}else{
    		mRankR = j;
    		mRankL = j;
	    }
	    if(count>1){//������
	        mCardBit |= IS_PAIR;
	        //if(count>=4)mCardBit |= IS_KAKUMEI;
	    }else if(count==1){//�P�R�o���t���O�͂Ȃ�
	        
	    }
	    if(j==6){//8�؂�
	        mCardBit |= IS_8GIRI;
	    }
   	}
    mNum = count;
    mCardBit |= (count<7) ? IS_NUM(count) : IS_NUM(7);//6���܂ł̓r�b�g���g����
}
Card::Card(){
}

void removeLap(vector<Card> *vecCard, int64 cdBit){
    //���W������Card���Ƃ菜��
    int i = 0;
    int64 mask = BITull(53)-1;//�J�[�h�̂Ԃ񂾂��i�J�[�h�̍����܂ł͌��Ȃ��j
    while( i < (*vecCard).size() ){//�J�[�h�W���̒���T�����Ă���
    	if( ( mask & (*vecCard)[i].getCardBit() & cdBit ) == 0 ){//bit�����Ԃ�Ȃ�
            i++;//����_��i�߂�
        }else{//�����
            (*vecCard).erase( (*vecCard).begin() + i);//�W�������菜��
        }
    }
}

void removePass(vector<Card> *vecCard){
    //���W������Pass���Ƃ菜��
    int i = 0;
    while( i < (*vecCard).size() ){//�J�[�h�W���̒���T�����Ă���
        if( (*vecCard)[i].isPass() == 0 ){
            (*vecCard).erase( (*vecCard).begin() + i);//�W�������菜��
        }
    }
}

bool compYakuRankL(const Card &c1, const Card &c2){
    return ( c1.mRankL > c2.mRankL);
}

bool compYakuRankR(const Card &c1, const Card &c2){
    return ( c1.mRankR < c2.mRankR);
}

int selectBigCards(const std::vector<Card> &vecCard){
    if(vecCard.size()==1){
        return 0;
    }
    
    int index = -1;
    int maxNum = 0;
    for(int i=0;i<vecCard.size();i++){
        if( vecCard[i].mNum > maxNum ){
            maxNum = vecCard[i].mNum;
            index = i;
        }
    }
    if(index >= 0){
        return index;
    }else{
        std::cout << "selectBigCards" << vecCard.size() << std::endl;
        exit(1);
    }
}

int selectLowCards(const std::vector<Card> &vecCard){
    if(vecCard.size()==1){
        return 0;
    }
    
    int index = -1;
    int minRank = 15;
    for(int i=0;i<vecCard.size();i++){
        if( vecCard[i].mRankR < minRank ){
            minRank = vecCard[i].mRankR;
            index = i;
        }
    }
    if(index >= 0){
        return index;
    }else{
        std::cout << "selectLowCards" << std::endl;
        exit(1);
    }
}