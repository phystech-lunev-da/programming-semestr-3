
#include "PenaltyDice.hpp"

PenaltyDice::PenaltyDice(unsigned max, unsigned seed) : Dice(max, seed) {}

int PenaltyDice::roll() {
    return std::min(Dice::roll(), Dice::roll());
}