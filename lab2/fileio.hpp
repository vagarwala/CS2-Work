/**
 * @file fileio.hpp
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2015
 * @copyright This code is in the public domain.
 *
 * @brief A brief example of file input (headers).
 *
 */

#ifndef __FILEIO_H__
#define __FILEIO_H__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

void readFile(char const *file, std::vector<int> &nums);

/**
 * @brief Prints the contents of a vector to stdout, delimited by newlines.
 *
 * @param v: vector to be printed
 */
inline void print_vector(std::vector<int> v)
{
    // TODO Write a function to print out a vector of integers.
    for(int i = 0; i < (int)v.size(); i++){
    	printf("%d\n", v[i]);
    }
}

#endif
