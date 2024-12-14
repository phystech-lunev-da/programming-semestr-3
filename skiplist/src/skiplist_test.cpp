
#include "skiplist.hpp"
#include <iostream>

int main() {

    SkipList<int> skiplist(10);
    //SkipList<int> skiplist(10000000);

    std::cout << skiplist << std::endl;

    for (unsigned i = 20; i < 40; i++) {
        skiplist.insert(i, i);
        std::cout << skiplist << std::endl;
    }

    skiplist.remove(25);
    std::cout << skiplist << std::endl;

    skiplist.remove(27);
    std::cout << skiplist << std::endl;

    skiplist.clear();

    std::cout << skiplist << std::endl;

    return 0;
}