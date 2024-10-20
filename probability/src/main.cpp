
#include "Dice.cpp"
#include "ThreeDicePool.hpp"
#include "BonusDice.hpp"
#include "PenaltyDice.hpp"
#include "DoubleDice.hpp"

#include <iostream>
#include <fstream>
#include <ctime>

#include <vector>

void calculate_expected_value() {
    Dice unique_dice(6, static_cast<unsigned>(time(nullptr)));

    std::cout << "Expected value of unique [1, 6) dice: " << expected_value(unique_dice, 100000u) << std::endl;

    Dice dices[3]{Dice(6, time(nullptr)), Dice(6, time(nullptr)), Dice(6, time(nullptr))};

    ThreeDicePool pool(dices[0], dices[1], dices[2]);

    std::cout << "Expected value of pool: " << expected_value(pool, 100000u) << std::endl;
}

std::vector<double> get_value_distribution(int max, RandomValueInterface& value, unsigned number_of_rolls = 1u) {
    std::vector<double> probabilities(max);
    for (int i = 0; i < max; i++) {
        probabilities[i] = value_probability(i+1, value, number_of_rolls);
    }
    return probabilities;
}

std::vector<double> get_value_distribution(int max, DoubleDiceWithInheritance& value, unsigned number_of_rolls = 1u) {
    std::vector<double> probabilities(max);
    for (int i = 0; i < max; i++) {
        probabilities[i] = value_probability(i+1, value, number_of_rolls);
    }
    return probabilities;
}

void write_distribution_in_file(std::string file_name, std::vector<double>& probability, size_t length) {
    std::ofstream file;
    file.open(file_name);
    if (file.is_open()) {
        for (int i = 1; i < length; i++) {
            file << i+1 << "; " << probability[i] << std::endl;
        }
    }
    file.close();
}

void calculate_distribution() {
    const int max = 100;
    const int iterations = 100000;

    Dice dice1(max, time(nullptr));

    BonusDice bonus(max, time(nullptr));
    
    std::vector<double> probability = get_value_distribution(max, bonus, iterations);
    write_distribution_in_file("bonusdice_data.csv", probability, max);

    PenaltyDice penalty(max, time(nullptr));

    probability = get_value_distribution(max, penalty, iterations);
    write_distribution_in_file("penaltydice_data.csv", probability, max);

    DoubleDice double_dice(bonus, penalty);

    probability = get_value_distribution(2 * max, double_dice, iterations);
    write_distribution_in_file("doubledice_data.csv", probability, 2 * max);

    DoubleDiceWithInheritance double_dice_with_inheritance(max, time(nullptr));

    probability = get_value_distribution(2 * max, double_dice_with_inheritance, iterations);
    write_distribution_in_file("doubledice_data_with_inheritance.csv", probability, 2 * max);

    const int three_max = 20;

    Dice d1(three_max, time(nullptr)), d2(three_max, time(nullptr) / 2), d3(three_max, time(nullptr) / 3);
    ThreeDicePool pool(d1, d2, d3);

    probability = get_value_distribution(3 * three_max, pool, iterations);
    write_distribution_in_file("threedicepool_data.csv", probability, 3 * three_max);
}

int main() {
    std::cout << "Calcutating the expected value of Dice and Three Dice: " << std::endl << std::endl;
    calculate_expected_value();
    std::cout << std::endl << std::endl;
    std::cout << "Calculating the distributions: " << std::endl;
    calculate_distribution();
    std::cout << "End of the calculation" << std::endl << std::endl;
}