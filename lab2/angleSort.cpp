/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief An example of sorting (x, y) pairs by angle.
 *
 */
#include "structs.hpp"
#include <vector>
using namespace std;


// TODO Modify one of your sorting functions (bubble sort not permitted) and
// implement it here. Add extra arguments as needed

// essentially copied from sorter.cpp
// just takes in the point vector & angle vector and swaps the given indices in both
void swap(vector<Tuple*> &points, vector<double> &angles, int first, int second){
    double temp_ang = angles[first];
    angles[first] = angles[second];
    angles[second] = temp_ang;

    Tuple* temp_pt = points[first];
    points[first] = points[second];
    points[second] = temp_pt;
}

//copied over from sorter.cpp, simply swaps points along with angles
int partition(vector<Tuple*> &points, vector<double> &angles, int low, int high){
    double pivot = angles[high];
    int i = low - 1;
    for(int j = low; j < high; j++){
        if(angles[j] <= pivot){
            i++;
            swap(points, angles, i, j);
        }
    }
    swap(points, angles, i+1, high);
    return (i + 1);
}

// also more or less copied over from sorter.cpp
void sort(vector<Tuple*> &points, vector<double> &angles, int left, int right)
{
    if (left < right){
        int pivot = partition(points, angles, left, right);
        sort(points, angles, left, pivot - 1);
        sort(points, angles, pivot + 1, right);
    }
}

int main(int argc, char const *argv[])
{
    vector<double> angles {4.2, 2.8, 1.4, 5.0, 3.3};
    vector<Tuple*> points;
    // Print the initial points and angles
    for (unsigned int i = 0; i < angles.size(); ++i)
    {
        points.push_back(new Tuple(i, i));
    }
    for (vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    {
        (*i)->printTuple();
    }
    for (vector<double>::iterator i = angles.begin(); i != angles.end(); ++i)
    {
        cout << *i << endl;
    }

    // Now sort them with respect to angle (points[i] corresponds to angle[i])

    /** THIS IS THE ONLY LINE OF THE MAIN LOOP YOU NEED TO MODIFY. */
    sort(points, angles, 0, (int)angles.size() - 1);
    /** REPLACE THE LINE ABOVE WITH A CALL TO YOUR SORTING FUNCTION. */

    // and print out the new points and angles
    for (vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    {
        (*i)->printTuple();
    }
    for (vector<double>::iterator i = angles.begin(); i != angles.end(); ++i)
    {
        cout << *i << endl;
    }

    // Don't want to leak memory...
    // Either of the below implementations works
    // for (std::vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    // {
    //     delete (*i);
    // }
    for (unsigned int i = 0; i < points.size(); ++i)
    {
        delete points[i];
    }
    return 0;
}
