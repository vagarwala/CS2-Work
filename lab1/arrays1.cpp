/**
 * @file arrays1.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2014-2015
 * @copyright This code is in the public domain.
 *
 * @brief An array example.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

#define TEST_SIZE 60

using namespace std;

//
// TODO: put user functions here
//

/**
 * @brief Finds maximum value in an integer array
 * @param arr[] the array
 * @param n the length of the array
 * @return the maximum element of the array
 */

int findMax(int arr[], int n){
    int i;
    int max = arr[0];
    for (i = 0; i < n; i++){
        if (arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}

/**
 * @brief Finds arithmetic mean of elements of an integer array
 * @param arr[] the array
 * @param n the length of the array
 * @return the arithmetic mean of the array
 */

double findMean(int arr[], int n){
    int i;
    int sum = 0;
    for (i = 0; i < n; i++){
        sum += arr[i];
    }
    return sum/n;
}

/**
 * @brief fills the given array with an ascending sequence
 * overwrites any previous contents.
 * 
 * @param arr[] the array
 * @param n the length of the array
 * @return no return value
 */

void fillArrAscending(int arr[], int n){
    int i;
    for (i = 0; i < n; i++){
        arr[i] = i;
    }
}



/**
 * @brief Sets up and runs an array example.
 */
int main(int argc, char ** argv)
{

    /*-------- CHANGE NOTHING BELOW THIS LINE FOR PART 1 --------*/
    int test_values[TEST_SIZE];
    int real_size;

    // seed the PRNG
    srand(time(nullptr));

    // initialize the test array to garbage
    for (int i = 0; i < TEST_SIZE; i++)
    {
        test_values[i] = rand();
    }

    // determine a real size
    real_size = TEST_SIZE - (rand() % 20);

    // initialize the meaningful part of the test array to random numbers
    // all of which are less than one million
    for (int i = 0; i < real_size; i++)
    {
        test_values[i] = rand() % 1000000;
    }
    /*-------- CHANGE NOTHING ABOVE THIS LINE FOR PART 1 --------*/

    //
    // TODO: do your stuff here with the array `test_values`
    // of dynamic size `real_size`
    //

    for (int i = 0; i < real_size; i++){
        cout << test_values[i] << " ";
    }
    cout << endl;

    int max = findMax(test_values, real_size);
    cout << "Max: " << max << endl;
    int mean = findMean(test_values, real_size);
    cout << "Mean: " << mean << endl;
    fillArrAscending(test_values, real_size);
    for (int i = 0; i < real_size; i++){
        cout << test_values[i] << " ";
    }
    cout << endl;

}
