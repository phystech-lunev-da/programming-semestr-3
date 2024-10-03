
#include "BonusDice.hpp"

BonusDice::BonusDice(RandomValueInterface& arg1) : dice(arg1) {}

int BonusDice::roll() {
    return std::max(dice.roll(), dice.roll());
}