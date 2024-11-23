
#include <grid.hpp>
#include <iostream>
#include <cassert>

int main() {
    Grid<float> g(3, 2, 0.0f);
    std::cout << "Checking size" << std::endl;

    assert(3 == g.get_x_size());
    assert(2 == g.get_y_size());

    using gsize_t = Grid<float>::size_type;

    std::cout << "Done!" << std::endl << std::endl;

    std::cout << "Checking value" << std::endl;
    for (gsize_t y_idx = 0; y_idx < g.get_y_size(); y_idx++) {
        for (gsize_t x_idx = 0; x_idx < g.get_x_size(); x_idx++) {
            assert(g(x_idx, y_idx) == 0.0f);
        }
    }
    std::cout << "Done!" << std::endl << std::endl;

    std::cout << "Assignment" << std::endl;
    for (gsize_t y_idx = 0; y_idx < g.get_y_size(); y_idx++) {
        for (gsize_t x_idx = 0; x_idx < g.get_x_size(); x_idx++) {
            g[y_idx][x_idx] = 1.0f;
        }
    }
    std::cout << "Done!" << std::endl << std::endl;

    std::cout << "Checking value" << std::endl;
    for (gsize_t y_idx = 0; y_idx < g.get_y_size(); y_idx++) {
        for (gsize_t x_idx = 0; x_idx < g.get_x_size(); x_idx++) {
            assert(g[y_idx][x_idx] == 1.0f);
        }
    }
    std::cout << "Done!" << std::endl << std::endl;

    return 0;
}