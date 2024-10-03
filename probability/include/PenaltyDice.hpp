
#pragma once
#include "Dice.hpp"

class PenaltyDice : public RandomValueInterface {
public:
    PenaltyDice(RandomValueInterface&);
    int roll() override;
private:
    RandomValueInterface& dice;
};