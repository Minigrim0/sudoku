#pragma once
#include "cell.hpp"

class Grid {
    public:
        Grid();
        Grid(bool generate);

        /**
         * Generates a grid
         */
        void generate();

        /**
         * Solves the grid using WFC
         */
        bool solve();

        /**
         * Displays the grid in the terminal
         */
        void display();

        void reset();

    private:
        bool solved();
        Cell _cells[9][9];
};
