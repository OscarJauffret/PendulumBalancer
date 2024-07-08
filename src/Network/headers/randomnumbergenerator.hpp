//
// Created by oscar on 07/07/2024.
//

#ifndef PENDULUMBALANCERAI_RANDOMNUMBERGENERATOR_HPP
#define PENDULUMBALANCERAI_RANDOMNUMBERGENERATOR_HPP


class RNG {
    public:
        static float randomFloatBetweenMinus1And1(bool random);
        static int randomIntBetween(int min, int max);
};


#endif //PENDULUMBALANCERAI_RANDOMNUMBERGENERATOR_HPP
