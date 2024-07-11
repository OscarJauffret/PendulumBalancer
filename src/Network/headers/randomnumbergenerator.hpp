//
// Created by oscar on 07/07/2024.
//

#ifndef PENDULUMBALANCERAI_RANDOMNUMBERGENERATOR_HPP
#define PENDULUMBALANCERAI_RANDOMNUMBERGENERATOR_HPP


class RNG {
    public:
        static float get();
        static float randomFloatBetweenMinus1And1(bool random);
        static int randomIntBetween(int min, int max);
        static float randomFloatBetween(float min, float max);
        static bool proba(float probability);
};


#endif //PENDULUMBALANCERAI_RANDOMNUMBERGENERATOR_HPP
