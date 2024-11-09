
#include <cassert>
#include "multi_grid.hpp"

int main() {
    MultiGrid<float, 3> const g3(1.0f, 2u, 3u, 4u);
    assert(3.0f == g3(1u, 1u, 1u));

    MultiGrid<float, 2> g2(3.0f, 2u, 5u);
    assert(3.0f == g3(1u, 1u, 1u));

    g2 = g3[1];

    assert(1.0f == g2(1u, 1u));
}
