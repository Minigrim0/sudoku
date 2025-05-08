#include <cstdlib>
#include <cstring>

#include "cell.hpp"

Cell::Cell() {
    _value = 0;
    for (int i = 0; i < 9; i++) _possibilities[i] = 0.0;
}

Cell::~Cell() {

}

int Cell::collapse() {
    // Weighted random selection
    float weight_sum = 0.0;
    for (int i=0; i< 9; i++) weight_sum += _possibilities[i];

    float random_value = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / weight_sum));
    for (int i = 0; i < 9; i++) {
        random_value -= _possibilities[i];
        if (random_value <= 0.0) {
            _value = i + 1;  // +1 to omit 0
            break;
        }
    }

    for (int i = 0; i < 9; i++) _possibilities[i] = 0.0;
    return _value;
}


void Cell::fill(int value) {
    _value = value;
}

void Cell::update_weights(Cell* square[8], Cell* horizontal[8], Cell* vertical[8]) {
    bool possible[9];
    memset(&possible, 1, 9);

    for (int idx = 0; idx < 8; idx ++) {
        int in_square_value = static_cast<int>(square[idx]->get_value());
        if (in_square_value > 0) {
            possible[in_square_value - 1] = false;
        }
        int horizontal_value = static_cast<int>(horizontal[idx]->get_value());
        if (horizontal_value > 0) {
            possible[horizontal_value - 1] = false;
        }
        int vertical_value = static_cast<int>(vertical[idx]->get_value());
        if (vertical_value > 0) {
            possible[vertical_value - 1] = false;
        }
    }

    int leftovers = 0;
    for (int idx = 0; idx < 9; idx++) if (possible[idx]) leftovers++;

    float probabilities = 1.0 / static_cast<float>(leftovers);
    for (int idx = 0; idx < 9; idx++) {
        if (possible[idx]) {
            _possibilities[idx] = probabilities;
        } else {
            _possibilities[idx] = 0.0;
        };
    }
}

float Cell::highest_probability() {
    if (_value != 0) return -1.0;
    float max = 0.0;
    for (int i = 0; i < 9; i++) {
        if (_possibilities[i] > max) {
            max = _possibilities[i];
        }
    }

    return max;
}
