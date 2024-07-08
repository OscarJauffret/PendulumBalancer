//
// Created by oscar on 07/07/2024.
//

#include "headers/genome.h"
#include "headers/randomnumbergenerator.hpp"

float RNG::randomFloatBetweenMinus1And1(bool random) {
    if (!random) {
        return 0.0f;
    }
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<float> dis(-1.0, 1.0);
    return dis(gen);
}

int RNG::randomIntBetween(int min, int max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dis(min, max);
    int random = dis(gen);
    return random;
}