#include <cstdlib>
#include <ctime>

#include "src/grid.hpp"

int main(int argc, char* argv[]) {
    std::srand(std::time({}));

    Grid grid;

    grid = Grid(true);
    grid.display();
    grid.solve();
    grid.display();

    return 0;
}
