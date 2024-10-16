
#pragma once
#include "Dice.hpp"

class PenaltyDice : virtual public Dice {
public:
    PenaltyDice(unsigned max, unsigned seed);
    int roll() override;
};