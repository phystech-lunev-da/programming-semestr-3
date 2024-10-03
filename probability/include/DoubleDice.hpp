
#pragma once

#include "BonusDice.hpp"
#include "PenaltyDice.hpp"

class DoubleDice : public BonusDice, public PenaltyDice {
    DoubleDice(Dice&);
};