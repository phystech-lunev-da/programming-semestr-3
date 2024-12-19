
#include <cassert>
#include "multi_grid.hpp"
#include <iostream>

int main() {

    std::cout << "Create dim 3" << std::endl;
    MultiGrid<float, 3> g3(3.0f, 2u, 3u, 4u);
    std::cout << "Done!" << std::endl;

    std::cout << "Check Values" << std::endl << "(0, 0, 0)";
    assert(3.0f == g3(0u, 0u, 0u));
    std::cout << std::endl << "(1, 1, 1)";
    assert(3.0f == g3(1u, 1u, 1u));
    std::cout << std::endl << "Done!" << std::endl;

    std::cout << "Create dim 3" << std::endl;
    MultiGrid<float, 2> g2(3.0f, 2u, 5u);
    std::cout << "Done!" << std::endl;
    
    std::cout << "Check Values" << std::endl << "(1, 1)";
    assert(3.0f == g2(1u, 1u));
    std::cout << "Done!" << std::endl;

    std::cout << "Assignment" << std::endl;
    g2 = g3[1];
    std::cout << "Done!" << std::endl;

    assert(1.0f == g2(1u, 1u));
}
