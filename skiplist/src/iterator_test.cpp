
#include "skiplist.hpp"

int main() {
    SkipList<int> skiplist(10000000);

    for (unsigned i = 20; i < 40; i++) {
        skiplist.insert(i, i);
    }

    std::cout << skiplist << std::endl;

    SkipList<int>::iterator iter = skiplist.begin();
    while (iter != skiplist.end()) {
        std::cout << *iter << std::endl;
        iter++;
    }

    return 0;
}