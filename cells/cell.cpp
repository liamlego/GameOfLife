#include "cell.h"


Cell::Cell(CELL_STATE state) : state{state} {

}

CELL_STATE *Cell::getState() {
    return &state;
}

void Cell::setState(CELL_STATE state) {
    this->state = state;
}