
#include "BonusDice.hpp"

BonusDice::BonusDice(unsigned max, unsigned seed) : Dice(max, seed) {}

int BonusDice::roll() {
    return std::max(Dice::roll(), Dice::roll());
}