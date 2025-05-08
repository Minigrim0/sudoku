#include <iostream>
#include <cstdlib>

#include "grid.hpp"

Grid::Grid(): Grid(false) {}

Grid::Grid(bool generate) {
    if (generate) {
        this->generate();
    } else {
        for (int x = 0; x < 9; x++) {
            for (int y = 0; y < 9; y++) {
                _cells[x][y].fill(0);  // Zero means empty cell
            }
        }
    }
}

bool Grid::generate() {
    std::cout << "Grid generation is not implemented yet" << std::endl;
    // Solve an empty puzzle then remove one random element at a time
    // until just before the puzzle becomes unsolvable or has
    // multiple solutions
    return false;
}

bool Grid::solve() {
    std::cout << "Starting solver" << std::endl;

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

        // Collapse the cell
        _cells[highest_probability_coord[0]][highest_probability_coord[1]].collapse();
    }
    return false;
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
    std::cout << "  ";
    for (int x = 0; x < 9; x++) std::cout << static_cast<char>(65 + x) << " ";
    std::cout << std::endl;

    for (int y = 0; y < 9; y ++) {
        std::cout << y + 1 << " ";
        for (int x = 0; x < 9; x ++) {
            uint8_t value = _cells[x][y].get_value();
            if (value == 0) {
                std::cout << "_ ";
            } else {
                std::cout << static_cast<int>(value) << " ";
            }
        }
        std::cout << std::endl;
    }
}
