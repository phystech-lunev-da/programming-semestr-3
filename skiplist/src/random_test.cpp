
#include <random>
#include <iostream>
#include "skiplist.hpp"

int main() {
    unsigned max_level = 10;
    Coin coin(0.5f, 1000);
    for (unsigned i = 0; i < max_level; i++) {
        std::cout << coin.flip() << " ";
    }
    std::cout << std::endl;
    return 0;
}