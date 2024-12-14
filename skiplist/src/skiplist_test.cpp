
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

    std::cout << "Finding 30" << std::endl;
    Node<int>* node = skiplist.find(30);
    std::cout << "Found: " << node->key << std::endl;

    std::cout << "Finding 25" << std::endl;
    node = skiplist.find(25);
    std::cout << "Found: " << node->key << std::endl;

    std::cout << "Copy" << std::endl;
    SkipList<int> copy(skiplist);   
    std::cout << copy << std::endl; 

    skiplist.clear();

    std::cout << skiplist << std::endl;

    return 0;
}