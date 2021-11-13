#define CELLGRID_H
#ifdef CELLGRID_H 

#include "cells/cell.h"
#include <iostream>
#include <vector>

using namespace std;

/*
* Conoway's Game of Life Simulation
* Created by Liam Morrison 11/13/2021
* Uses SFML Graphics API
*/

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
    // Next generation that the cells will be on the next iteration
    vector<vector<CELL_STATE*>*> nextGeneration;

    // Rendering data
    int cellWidth, cellHeight;

};
#endif


