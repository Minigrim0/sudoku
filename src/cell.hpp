#pragma once

class Cell {
    public:
        Cell();
        ~Cell();

        /**
         * Chooses a value at random (weighted) to collapse the cell
         */
        int collapse();

        /**
         * Returns the highest probability from all the possibilities.
         * Using the simplest probability setting algorithm will mean
         * all possbile numbers in the cell will have the same probability
         * but further analysis may change those probabilities.
         */
        float highest_probability();

        /**
         * Fills the cell with the given value, effectively collapsing
         * it
         */
        void fill(int value);

        /**
         Update weights for the current cell given its neighbours (within the same square, horizontal line and vertical line)
         */
        void update_weights(Cell* square[8], Cell* horizontal[8], Cell* vertical[8]);

        inline int get_value() const { return _value; }

    private:
        int _value;
        float _possibilities[9];  // Possibilities for each number
};
