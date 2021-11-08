#define CELLGRID_H
#ifdef CELLGRID_H 

#include "cells/cell.h"
#include <iostream>
#include <vector>

using namespace std;

class CellGrid {

public:
    CellGrid(int width, int height, const vector<vector<Cell*>*> &startGrid);
    ~CellGrid();
    bool determineNextGeneration();
    bool birthNextGeneration();

    vector<vector<Cell*>> &getCellGrid();
    vector<vector<CELL_STATE*>*> &getNextGeneration();

private:
    int width, height;
    vector<vector<Cell*>> cellGrid;
    vector<vector<CELL_STATE*>*> nextGeneration;

    // Rendering data
    int cellWidth, cellHeight;

};
#endif


