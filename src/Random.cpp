#include <random>
#include <ctime>
#include <functional>
#include "Random.h"

auto dice = std::bind(std::uniform_int_distribution<int>(1,6), std::mt19937(static_cast<unsigned int>(time(nullptr))));

auto genrand_real = bind(uniform_real_distribution<double>(0,1), mt19937(static_cast<unsigned int>(time(nullptr))));

Random::Random(){
    
}
double Random::rand(){
    return genrand_real();
}

