#pragma once
#include "cell.hpp"

class Grid {
    public:
        Grid();
        Grid(bool generate);

        /**
         * Generates a grid
         */
        bool generate();

        /**
         * Solves the grid using WFC
         */
        bool solve();

        /**
         * Displays the grid in the terminal
         */
        void display();

    private:
        bool solved();
        Cell _cells[9][9];
};
