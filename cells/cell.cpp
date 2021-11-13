#include "cell.h"

/*
* Conoway's Game of Life Simulation
* Created by Liam Morrison 11/13/2021
* Uses SFML Graphics API
*/

Cell::Cell(CELL_STATE state) : state{state} {

}

CELL_STATE *Cell::getState() {
    return &state;
}

void Cell::setState(CELL_STATE state) {
    this->state = state;
}