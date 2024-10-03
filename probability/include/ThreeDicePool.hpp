
#pragma once
#include "Dice.hpp"

class ThreeDicePool : public RandomValueInterface {
public:
    ThreeDicePool(RandomValueInterface&, RandomValueInterface&, RandomValueInterface&);
    int roll() override;
private:
    RandomValueInterface& dice1;
    RandomValueInterface& dice2;
    RandomValueInterface& dice3;
};