
#pragma once
#include "Dice.hpp"

class BonusDice : public RandomValueInterface {
public:
    BonusDice(RandomValueInterface&);
    int roll() override;
private:
    RandomValueInterface& dice;
};