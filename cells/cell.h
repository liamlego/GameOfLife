#define CELL_H
#ifdef CELL_H 

/*
* Conoway's Game of Life Simulation
* Created by Liam Morrison 11/13/2021
* Uses SFML Graphics API
*/

enum CELL_STATE {ALIVE, DEAD};

class Cell {

public:
    Cell(CELL_STATE state);
    CELL_STATE *getState();
    void setState(CELL_STATE state);

private:
    CELL_STATE state;

};


#endif