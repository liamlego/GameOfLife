#define CELL_H
#ifdef CELL_H 

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