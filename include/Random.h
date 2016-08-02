#ifndef DEFINE_RANDOM
#define DEFINE_RANDOM

using namespace std;

//0から1の乱数は標準ライブラリを用いる
//auto genrand_real = bind(uniform_real_distribution<>(0,1), mt19937(static_cast<unsigned int>(time(nullptr))));

class Random{
private:
    
public:
    Random();
    double rand();
};

#endif