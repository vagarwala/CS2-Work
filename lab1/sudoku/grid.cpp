#include <cstdio>
#include <string>
#include <cmath>
#include <fstream>
#include "grid.hpp"

using namespace std;

const int DEFAULT_SIZE = 9;

/**
 * @brief: constructor, initializes board to 0
 */

Grid::Grid(){
	grid = new int*[DEFAULT_SIZE];
	for(int i = 0; i < size; i++){
		grid[i] = new int[size];
	}
	size = DEFAULT_SIZE;
	for (int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			grid[i][j] = 0;
		}
	}
}


/**
 * @brief: constructor, but for if we want the board to be a different size.
 * @param: s is the sidelength of the board we want.
 */

Grid::Grid(int s){
	grid = new int*[s];
	for(int i = 0; i < s; i++){
		grid[i] = new int[s];
	}
	size = s;
	for (int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			grid[i][j] = 0;
		}
	}
}

/**
 * @brief: destructor
 */

Grid::~Grid(){
    for (int i = 0; i < size; i++){
        delete[] grid[i];
    }
    delete[] grid;
}

/**
 * @brief: loadBoard, reads a file containing a sudoku board
 * and inputs that into the grid.
 */

void Grid::loadBoard(string filename){
	ifstream file(filename);
	if (file.is_open()){
		for (int i = 0; i < size; i++){
			for (int j = 0; i < size; j++){
				file >> grid[i][j];
			}
		}
	}
}

/**
 * @brief: checks if the board is completely full
 * very simple; just checks that every entry is filled
 * if it all managed to fill it must be valid
 */

int Grid::isComplete(){
	for (int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(grid[i][j] == 0){
				return 0;
			}
		}
	}
	return 1;
}

/**
 * @brief: checkValid: checks if a move is valid.
 * has to check the value you're trying to add doesn't match:
 * a) anything in the same row
 * b) anything in the same column
 * c) anything in the same box (usually 3x3 box but could be different for different sizes)
 */

int Grid::checkValid(int x, int y, char val){
	// row and column constraint
	for (int i = 0; i < size; i++){
		if((int)val == grid[x][i]){
			return 0;
		}
		if ((int)val == grid[i][y]){
			return 0;
		}
		int blockSize = (int)sqrt(size);
		int blockRowMult = x/blockSize;
		int blockColMult = y/blockSize;
		int blockRow = blockRowMult * blockSize;
		int blockCol = blockColMult * blockSize;
		for (int i = 0; i < blockSize; i++){
			for (int j = 0; j < blockSize; j++){
				if ((int)val == grid[blockRow + i][blockCol + j]){
					return 0;
				}
			}
		}
	}
	return 1;
}

/**
 * @brief: writeNum: if the move is valid, do it
 */

void Grid::writeNum(int x, int y, char val){
	if(checkValid(x, y, val)){
		grid[x][y] = val;
	}
}

/**
 * @brief: undoNum: remove the value at a given spot.
 */

void Grid::undoNum(int x, int y){
	grid[x][y] = 0;
}
