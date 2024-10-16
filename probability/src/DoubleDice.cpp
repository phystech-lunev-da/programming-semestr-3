
#include "DoubleDice.hpp"

DoubleDice::DoubleDice(BonusDice& bonus, PenaltyDice& penalty) : bonus_dice(bonus), penalty_dice(penalty) {}

int DoubleDice::roll() {
    return bonus_dice.roll() + penalty_dice.roll();
}

DoubleDiceWithInheritance::DoubleDiceWithInheritance(unsigned max, unsigned seed) : BonusDice(max, seed), PenaltyDice(max, seed), Dice(max, seed) {}

int DoubleDiceWithInheritance::roll() {
    return BonusDice::roll() + PenaltyDice::roll(); 
}