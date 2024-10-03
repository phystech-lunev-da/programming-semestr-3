


#include "Dice.hpp"

Dice::Dice(unsigned max, unsigned seed) : max(max), dstr(1, max), reng(seed) {}

int Dice::roll() {
    return dstr(reng);
}

double expected_value(RandomValueInterface& value, unsigned number_of_rolls=1u) {
    auto accum = 0llu;
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt)
        accum += value.roll();
    return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}

double value_probability(unsigned value, RandomValueInterface& randomValue, unsigned number_of_rolls=1u) {
    auto count = 0llu;
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt) {
        int result = randomValue.roll();
        if (result == value) {
            count++;
        }
    }
    return static_cast<double>(count) / static_cast<double>(number_of_rolls);
}