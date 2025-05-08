#include <iostream>
#include <cstdlib>

#include "grid.hpp"

Grid::Grid(): Grid(false) {}

Grid::Grid(bool gen_grid) {
    if (gen_grid) {
        generate();
    } else {
        reset();
    }
}

void Grid::reset() {
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            _cells[x][y].fill(0);  // Zero means empty cell
        }
    }
}

void Grid::generate() {
    // Solve an empty puzzle then remove one random element at a time
    // until just before the puzzle becomes unsolvable or has
    // multiple solutions
    reset();
    solve();

    bool can_be_solved = true;
    int amount_removed = 0;
    while (can_be_solved) {
        // Take random cell
        int index = std::rand() % 81;
        int x = index / 9;
        int y = index % 9;
        while (_cells[x][y].get_value() == 0) {
            index = std::rand() % 81;
            x = index / 9;
            y = index % 9;
        }

        Cell cell_copy[9][9];
        for (int i = 0; i < 9; i++) {
            std::copy(std::begin(_cells[i]), std::end(_cells[i]), std::begin(cell_copy[i]));
        }

        _cells[x][y].fill(0);
        amount_removed += 1;
        bool solvable = solve();

        for (int i = 0; i < 9; i++) {
            std::copy(std::begin(cell_copy[i]), std::end(cell_copy[i]), std::begin(_cells[i]));
        }

        if (!solvable) {
            can_be_solved = false;
        } else {
            _cells[x][y].fill(0);
        }
    }
}

bool Grid::solve() {
    bool took_a_random_path = false;

    while (!solved()) {
        // Update cells weights
        for (int x = 0; x < 9; x++) {
            for (int y = 0; y < 9; y ++) {
                if (_cells[x][y].get_value() != 0.0) continue;

                Cell* neighbours[8];
                Cell* horizontal[8];
                Cell* vertical[8];

                int index = 0;
                for (int inner_x = (x / 3) * 3; inner_x < (x / 3) * 3 + 3; inner_x++) {
                    for(int inner_y = (y / 3) * 3; inner_y < (y / 3) * 3 + 3; inner_y++) {
                        if (inner_x != x || inner_y != y) {
                            neighbours[index] = &(_cells[inner_x][inner_y]);
                            index++;
                        }
                    }
                }

                for (int i = 0; i < 9; i ++) {
                    if (i != x) {
                        horizontal[i - static_cast<int>(i >= x)] = &(_cells[i][y]);
                    }
                    if (i != y) {
                        vertical[i - static_cast<int>(i >= y)] = &(_cells[x][i]);
                    }
                }

                _cells[x][y].update_weights(neighbours, horizontal, vertical);
            }
        }

        // Find the cell with the highest probability;
        float highest_probability = 0.0;

        // Take a random cell just in case
        int highest_probability_coord[2] = {std::rand() % 9, std::rand() % 9};
        for (int x = 0; x < 9; x++) {
            for (int y = 0; y < 9; y ++) {
                float cell_probability = _cells[x][y].highest_probability();
                if (cell_probability > highest_probability) {
                    highest_probability = cell_probability;
                    highest_probability_coord[0] = x;
                    highest_probability_coord[1] = y;
                }
            }
        }

        if (highest_probability <= 1.0 - 10e-6) {
            took_a_random_path = true;
        }

        // Collapse the cell
        _cells[highest_probability_coord[0]][highest_probability_coord[1]].collapse();
    }
    return !took_a_random_path;
}

bool Grid::solved() {
    for(int x = 0; x < 9; x++) {
        for(int y = 0; y < 9; y++) {
            if (_cells[x][y].get_value() == 0) {
                return false;
            }
        }
    }
    return true;
}

void Grid::display() {
    std::cout << " |";
    for (int x = 0; x < 9; x++) {
        std::cout << static_cast<char>(65 + x);
        if ((x + 1) % 3 == 0) {
            std::cout << "|";
        } else {
            std::cout << "_";
        }
    }
    std::cout << std::endl;

    for (int y = 0; y < 9; y ++) {
        std::cout << y + 1 << "|";
        for (int x = 0; x < 9; x ++) {
            uint8_t value = _cells[x][y].get_value();
            if (value == 0) {
                std::cout << " ";
            } else {
                std::cout << static_cast<int>(value);
            }

            if ((x + 1) % 3 == 0) {
                std::cout << "|";
            } else {
                if ((y + 1) % 3 == 0)
                {
                    std::cout << "_";
                } else {
                    std::cout << " ";
                }
            }
        }
        std::cout << std::endl;
    }
}
