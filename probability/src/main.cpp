
#include "Dice.cpp"
#include "ThreeDicePool.hpp"
#include "BonusDice.hpp"
#include "PenaltyDice.hpp"

#include <iostream>
#include <fstream>
#include <ctime>

void calculate_expected_value() {
    Dice unique_dice(6, static_cast<unsigned>(time(nullptr)));

    std::cout << "Expected value of unique [1, 6) dice: " << expected_value(unique_dice, 100000u) << std::endl;

    Dice dices[3]{Dice(6, time(nullptr)), Dice(6, time(nullptr)), Dice(6, time(nullptr))};

    ThreeDicePool pool(dices[0], dices[1], dices[2]);

    std::cout << "Expected value of pool: " << expected_value(pool, 100000u) << std::endl;
}

double* get_value_distribution(int max, RandomValueInterface& value, unsigned number_of_rolls = 1u) {
    double* probabilities = new double[max];
    for (int i = 0; i < max; i++) {
        probabilities[i] = value_probability(i+1, value, 100000);
    }
    return probabilities;
}

void write_distribution_in_file(std::string file_name, double* probability, size_t length) {
    std::ofstream file;
    file.open(file_name);
    if (file.is_open()) {
        file << 1;
        for (int i = 1; i < length; i++) {
            file << " ; " << i+1;
        }
        file << "\n" << probability[0];
        for (int i = 1; i < length; i++) {
            file << " ; " << probability[i];
        }
    }
    file.close();
}

void calculate_distribution() {
    const int max = 100;

    Dice dice1(max, time(nullptr));

    BonusDice bonus(dice1);
    
    double* probability = get_value_distribution(max, bonus, 100000);
    write_distribution_in_file("bonusdice_data.csv", probability, max);
    delete[] probability;

    PenaltyDice penalty(dice1);

    probability = get_value_distribution(max, penalty, 100000);
    write_distribution_in_file("penaltydice_data.csv", probability, max);
    delete[] probability;

    const int three_max = 20;

    Dice d1(three_max, time(nullptr)), d2(three_max, time(nullptr) / 2), d3(three_max, time(nullptr) / 3);
    ThreeDicePool pool(d1, d2, d3);

    probability = get_value_distribution(3 * three_max, pool, 100000);
    write_distribution_in_file("threedicepool_data.csv", probability, 3 * three_max);
    delete[] probability;
}

int main() {
    calculate_expected_value();
    calculate_distribution();
}