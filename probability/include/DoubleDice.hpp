
#pragma once

#include "BonusDice.hpp"
#include "PenaltyDice.hpp"

class DoubleDice : public RandomValueInterface
{
public:
    DoubleDice(BonusDice &, PenaltyDice &);
    int roll() override;

private:
    BonusDice &bonus_dice;
    PenaltyDice &penalty_dice;
};

class DoubleDiceWithInheritance : public BonusDice, public PenaltyDice {
public:
    DoubleDiceWithInheritance(unsigned, unsigned);
    int roll() override;
};