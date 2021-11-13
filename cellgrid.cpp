#include "cellgrid.h"

/*
* Conoway's Game of Life Simulation
* Created by Liam Morrison 11/13/2021
* Uses SFML Graphics API
*/

CellGrid::CellGrid(int width, int height, const vector<vector<Cell*>*> &startGrid) : width{width}, height{height} {

    // Shallow copy
    for (int i = 0; i < width; i++) {
        cellGrid.push_back(*startGrid[i]);
        nextGeneration.push_back(new vector<CELL_STATE*>);
        for (int j = 0; j < height; j++) {
            // Load the cell grid
            cellGrid[i].push_back(startGrid[i]->at(j));
            // Load first generation
            nextGeneration[i]->push_back(new CELL_STATE(*cellGrid[i][j]->getState()));
        }
    }

}

CellGrid::~CellGrid() {
    for (int x = 0; x < nextGeneration.size(); x++) {
        for (int y = 0; y < nextGeneration.size(); y++) {
            delete nextGeneration.at(x)->at(y);
        }
        delete [] nextGeneration.at(x);
    }    
}

/*

    1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
    2. Any live cell with two or three live neighbours lives on to the next generation.
    3. Any live cell with more than three live neighbours dies, as if by overpopulation.
    4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

*/

bool CellGrid::determineNextGeneration() {

    for (int i = 0; i < width; i++) {
        
        for (int j = 0; j < height; j++) {

                int numberOfLiveCells = 0;

                if ((i+1 < width && j+1 < height) && *cellGrid[i+1][j+1]->getState() == ALIVE) {
                    numberOfLiveCells++;
                }
                // i+1 && j
                if ((i+1 < width) && *cellGrid[i+1][j]->getState() == ALIVE) {
                    numberOfLiveCells++;
                }
                // i && j+1
                if ((j+1 < height) && *cellGrid[i][j+1]->getState() == ALIVE) {
                    numberOfLiveCells++;
                }
                // i+1 && j-1
                if ((i+1 < width && j-1 >= 0) && *cellGrid[i+1][j-1]->getState() == ALIVE) {
                    numberOfLiveCells++;
                }
                // i-1 && j+1
                if ((i-1 >= 0 && j+1 < height) && *cellGrid[i-1][j+1]->getState() == ALIVE) {
                    numberOfLiveCells++;
                }
                // i-1 && j-1
                if ((i-1 >= 0 && j-1 >= 0) && *cellGrid[i-1][j-1]->getState() == ALIVE) {
                    numberOfLiveCells++;
                }
                // i && j-1
                if ((j-1 >= 0) && *cellGrid[i][j-1]->getState() == ALIVE) {
                    numberOfLiveCells++;
                }
                // i-1 && j
                if ((i-1 >= 0) && *cellGrid[i-1][j]->getState() == ALIVE) {
                    numberOfLiveCells++;
                }

                if (*cellGrid[i][j]->getState() == ALIVE) {
                    if (numberOfLiveCells < 2 || numberOfLiveCells > 3) {
                        *nextGeneration[i]->at(j) = DEAD;
                    }
                } else if (*cellGrid[i][j]->getState() == DEAD) {
                    if (numberOfLiveCells == 3) {
                        *nextGeneration[i]->at(j) = ALIVE;
                    }
                }  
        }

    }


    return true;
}

bool CellGrid::birthNextGeneration() {

    for (int i = 0; i < width; i++) {

        for (int j = 0; j < height; j++) {
            if (*nextGeneration[i]->at(j) == ALIVE) {
                cellGrid[i][j]->setState(ALIVE);
            } else {
                cellGrid[i][j]->setState(DEAD);
            }
        }

    }

    return true;
}

vector<vector<Cell*>> &CellGrid::getCellGrid() {
    return cellGrid;
}

vector<vector<CELL_STATE*>*> &CellGrid::getNextGeneration() {
    return nextGeneration;
}