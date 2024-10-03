
#pragma once
#include <random>

struct RandomValueInterface {
    virtual int roll() = 0;
};

class Dice : public RandomValueInterface {
public:
    Dice(unsigned max, unsigned seed);
    int roll() override;
private:
    unsigned max;
    std::uniform_int_distribution<unsigned> dstr;
    std::default_random_engine reng;
};

double expected_value(RandomValueInterface& value, unsigned number_of_rolls);
double value_probability(unsigned, RandomValueInterface&, unsigned);