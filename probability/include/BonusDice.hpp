
#pragma once
#include "Dice.hpp"


class BonusDice : virtual public Dice {
public:
    BonusDice(unsigned max, unsigned seed);
    int roll() override;
};