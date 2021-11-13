#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

#include "cellgrid.h"

using namespace std;

/*
* Conoway's Game of Life Simulation
* Created by Liam Morrison 11/13/2021
* Uses SFML Graphics API
*/



// Prototypes
void drawCellGrid(CellGrid &cellGrid, sf::RenderWindow &window);
void drawControl(sf::RenderWindow &window, sf::Color color);
vector<vector<Cell*>*> *allocateGrid();
void deallocateGrid(vector<vector<Cell*>*> *grid);

// Constants
// Maximum is 49, and 37 with this configuration
const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 608;
const float CELL_WIDTH = 16, CELL_HEIGHT = 16;
const int GRID_WIDTH = SCREEN_WIDTH/CELL_WIDTH, GRID_HEIGHT = SCREEN_HEIGHT/CELL_HEIGHT;

const int CONTROL_BUFFER = 200;

const vector<vector<int>> aliveStartingCells = {};//{1, 0}, {2, 0}, {1, 1}, {2, 1}, {0, 1}, {0, 2}, {1, 2}, {3, 1}, {3, 2}, {3, 3}, {4, 2}, {2, 3}};

int main()
{

    cout << "Starting a Game of Life..." << endl;


    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT+CONTROL_BUFFER), "Conoway's Game of Life");

    vector<vector<Cell*>*> *originCells = allocateGrid();

    CellGrid cellGrid(GRID_WIDTH, GRID_HEIGHT, *originCells);

    int mouseX = 0;
    int mouseY = 0;

    bool runSimulation = false;

    bool justClicked = false;

    sf::Color color = sf::Color::Green;

    cout << "Conway's Game of Life" << endl;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                mouseX = sf::Mouse::getPosition(window).x/CELL_WIDTH;
                mouseY = sf::Mouse::getPosition(window).y/CELL_HEIGHT;
                justClicked = true;
            }    

            if (event.type == sf::Event::KeyPressed) {
                runSimulation = !runSimulation;
            }
        }

        // Draw cells
        window.clear();   
        drawCellGrid(cellGrid, window);
        drawControl(window, color);
        window.display();

        if (justClicked) {
            if (mouseX < GRID_WIDTH && mouseX >= 0 && mouseY < GRID_HEIGHT && mouseY >= 0) {
                if (*cellGrid.getCellGrid()[mouseX][mouseY]->getState() == ALIVE) {
                    cellGrid.getCellGrid()[mouseX][mouseY]->setState(DEAD);
                    *cellGrid.getNextGeneration()[mouseX]->at(mouseY) = DEAD;
                } else {
                    cellGrid.getCellGrid()[mouseX][mouseY]->setState(ALIVE);
                    *cellGrid.getNextGeneration()[mouseX]->at(mouseY) = ALIVE;
                }
            } else {
                if (color == sf::Color::Red) {
                    color = sf::Color::Green;
                } else {
                    color = sf::Color::Red;
                }
                runSimulation = !runSimulation;
            }
            justClicked = false;
        }

        // Update cells
        if (runSimulation) {
            this_thread::sleep_for(50ms);
            cellGrid.determineNextGeneration();
            cellGrid.birthNextGeneration();
        }
        
    }

    deallocateGrid(originCells);
    delete originCells;
    return 0;
}

// Allocates memory for Cell Grid
vector<vector<Cell*>*> *allocateGrid() {

    vector<vector<Cell*>*> *originCells = new vector<vector<Cell*>*>();

    for (int x = 0; x < GRID_WIDTH; x++) {

        for (int y = 0; y < GRID_HEIGHT; y++) {
            originCells->push_back(new vector<Cell*>());
            originCells->at(x)->push_back(new Cell(DEAD));
            originCells->at(x)->at(y)->setState(DEAD);
            for (int i = 0; i < aliveStartingCells.size(); i++) {
                if (x == aliveStartingCells[i][0] && y == aliveStartingCells[i][1]) { 
                    originCells->at(x)->at(y)->setState(ALIVE);
                } 
            }

        }
    }
    return originCells;
}

// Deallocates grid to avoid memory leaks
void deallocateGrid(vector<vector<Cell*>*> *grid) {
    for (int x = 0; x < GRID_WIDTH; x++) {

        for (int y = 0; y < GRID_HEIGHT; y++) {
                delete grid->at(x)->at(y);
        }
        delete [] grid->at(x);
    }
}

// draws cellGrid using SFML
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

// Draws the control button for simulation
void drawControl(sf::RenderWindow &window, sf::Color color) {
            sf::RectangleShape control;
            
            sf::Vector2f controlV;
            controlV.x = SCREEN_WIDTH;
            controlV.y = CONTROL_BUFFER;

            control.setSize(controlV);

            sf::Vector2f controlPosition;
            controlPosition.x = 0;
            controlPosition.y = SCREEN_HEIGHT;

            control.setPosition(controlPosition);

            control.setFillColor(color);
            window.draw(control);
}