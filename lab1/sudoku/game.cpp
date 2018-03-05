#include <iostream>
#include <cstring>
#include <cmath>
#include "game.hpp"

using namespace std;

/**
 * @brief constructor 
 */

Game::Game(){
	moves = 0;
	grid = Grid();
}

/**
 * @brief destructor 
 */

Game::~Game(){
	delete &moves;
	delete &grid;
}

/**
 * @brief getMove: takes user input of the move the user wants to make.
 * puts this info into a char array
 * returns the array
 * if i had finished this, another function (probably Run()) would take this output
 * and then use the coordinates (res[1], res[2]) to do the move. 
 * also, clearly I didn't finish this or write the solver (oops) 
 * especially since I can't really write the solver without finishing this
 * but if I were to write the solver I think I'd probably use a simple DFS algorithm?
 */

char[] Game::getMove(){
	string str;
	cout << "Enter your move." << endl;
	getline(cin, str);
	char* input = str.c_str();
	char* res = new char[4];
	if(*input == 'd'){
		res = {*input, *(input + 2), *(input + 4), *(input + 6)};
	} else{
		res = {*(input), *(input + 2), *(input + 4), 0};
	}
	return res;

}