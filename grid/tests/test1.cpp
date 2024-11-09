
#include "grid.hpp"
#include <cassert>

int main() {

    Grid<float> g(3, 2, 0.0f);

    assert(3 == g.get_x_size());
    assert(2 == g.get_y_size());

    return 0;
}