
#include "PenaltyDice.hpp"

PenaltyDice::PenaltyDice(RandomValueInterface& arg1) : dice(arg1) {}

int PenaltyDice::roll() {
    return std::min(dice.roll(), dice.roll());
}