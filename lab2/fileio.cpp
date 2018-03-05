/**
 * @file fileio.cpp
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2015
 * @copyright This code is in the public domain.
 *
 * @brief A brief example of file input (implementation).
 */

#include "fileio.hpp"
#include <iostream>
#include <fstream>
using namespace std;

/**
 * @brief Reads the integers in file and fills nums with these integers.
 *
 * @param file: File containing integers, one per line.
 * @param nums: Vector to fill with the integers in file.
 *
 * Notice that the vector is passed by reference, so you should fill the vector
 * and not return anything from this function.
 */
void readFile(char const *file, std::vector<int> &nums)
{
    // TODO Write a function which takes a filename and a vector of integers as
    // arguments and filles the vector with integers from the specified file.
	int num;
	string line;
	ifstream myfile(file);
	if (myfile.is_open()){
		while(getline(myfile, line)){
			num = atoi(line.c_str());
			nums.push_back(num);
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}
