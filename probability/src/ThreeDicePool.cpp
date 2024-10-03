

#include "ThreeDicePool.hpp"

ThreeDicePool::ThreeDicePool(RandomValueInterface& value1, RandomValueInterface& value2, RandomValueInterface& value3) 
    : dice1(value1), dice2(value2), dice3(value3) {}

int ThreeDicePool::roll() {
    return dice1.roll() + dice2.roll() + dice3.roll();
}