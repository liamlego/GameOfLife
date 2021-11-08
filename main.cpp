#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

#include "cellgrid.h"

using namespace std;

// Prototypes
void drawCellGrid(CellGrid &cellGrid, sf::RenderWindow &window);
vector<vector<Cell*>*> *allocateGrid();
void deallocateGrid(vector<vector<Cell*>*> *grid);

// Constants
// Maximum is 49, and 37 with this configuration
const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 608;
const float CELL_WIDTH = 16, CELL_HEIGHT = 16;
const int GRID_WIDTH = SCREEN_WIDTH/CELL_WIDTH, GRID_HEIGHT = SCREEN_HEIGHT/CELL_HEIGHT;

const vector<vector<int>> aliveStartingCells = {{16, 17}, {15, 17}, {16, 16}, {15, 16}, {17, 18}, {17, 19}, {18, 18}, {18, 19}};

int main()
{

    cout << "Starting..." << endl;


    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Conoway's Game of Life");

    vector<vector<Cell*>*> *originCells = allocateGrid();

    CellGrid cellGrid(GRID_WIDTH, GRID_HEIGHT, *originCells);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Draw cells
        window.clear();   
        drawCellGrid(cellGrid, window);
        window.display();

        this_thread::sleep_for(250ms);
        // Update cells
        cellGrid.determineNextGeneration();
        cellGrid.birthNextGeneration();

        
    }

    deallocateGrid(originCells);
    delete originCells;
    return 0;
}

vector<vector<Cell*>*> *allocateGrid() {

    vector<vector<Cell*>*> *originCells = new vector<vector<Cell*>*>();

    for (int x = 0; x < GRID_WIDTH; x++) {

        for (int y = 0; y < GRID_HEIGHT; y++) {
            originCells->push_back(new vector<Cell*>());
            for (int i = 0; i < aliveStartingCells.size(); i++) {
                originCells->at(x)->push_back(new Cell(DEAD));
                if (x == aliveStartingCells[i][0] && y == aliveStartingCells[i][1]) { 
                    originCells->at(x)->at(y)->setState(ALIVE);
                } 
            }

        }
    }
    return originCells;
}

void deallocateGrid(vector<vector<Cell*>*> *grid) {
    for (int x = 0; x < GRID_WIDTH; x++) {

        for (int y = 0; y < GRID_HEIGHT; y++) {
                delete grid->at(x)->at(y);
        }
        delete [] grid->at(x);
    }
}

void drawCellGrid(CellGrid &cellGrid, sf::RenderWindow &window) {

    float drawLocationX = 0;
    float drawLocationY = 0;

    for (int x = 0; x < GRID_WIDTH; x++) {

        for (int y = 0; y < GRID_HEIGHT; y++) {
            sf::RectangleShape drawableCell;
            
            sf::Vector2f drawableCellSize;
            drawableCellSize.x = CELL_WIDTH;
            drawableCellSize.y = CELL_HEIGHT;

            drawableCell.setSize(drawableCellSize);

            sf::Vector2f drawableCellPosition;
            drawableCellPosition.x = drawLocationX;
            drawableCellPosition.y = drawLocationY;

            drawableCell.setPosition(drawableCellPosition);

            if (*cellGrid.getCellGrid()[x][y]->getState() == ALIVE) {
                drawableCell.setFillColor(sf::Color::White);
            } else {
                drawableCell.setFillColor(sf::Color::Black);
            }

            window.draw(drawableCell);
            drawLocationY += CELL_HEIGHT;  
        }
        drawLocationX += CELL_WIDTH;
        drawLocationY = 0;
        
    }

}