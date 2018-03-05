/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The gift wrapping and Graham scan convex hull algorithms
 * (implementation).
 *
 */
#include "HullAlgorithms.hpp"

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to HullAlgorithms.hpp if you write a helper function!
 *
 * Our reference implementation has four helper functions and the function(s)
 * copied over from angleSort.cpp.
 */

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

/** as described in the assignment
 * @brief determines whether three points make a left turn
 * @params three points
 * @return 0 or 1 if they do not or do make a left turn
 */

int leftTurn(Tuple* pt1, Tuple* pt2, Tuple* pt3){
    int x_diff1 = pt2->x - pt1->x;
    int y_diff1 = pt2->y - pt1->y;
    int x_diff2 = pt3->x - pt1->x;
    int y_diff2 = pt3->y - pt1->y;

    //cross product of the following lines: pt1-----pt2, pt1-----pt3
    int cross = (x_diff1 * y_diff2 - y_diff1 * x_diff2);

    if (cross > 0){ // this means pt1-----pt3 is counter-clockwise from pt1-----pt2 which means its a left turn
        return 1;
    }else{
        return 0;
    }
}

/** as described in the assignment
 * @brief determines the leftmost point in the dataset
 * @params data set
 * @return leftmost point
 */

int leftMost(vector<Tuple*> points){
    int left = points[0]->x;
    int left_ind = 0;
    for(int i = 0; i < (int)points.size(); i++){
        if(points[i]->x < left){
            left = points[i]->x;
            left_ind = i;
        }
    }
    return left_ind;
}



/**
 * TODO: Implement this function.
 */

/**
 * Gift wrap works as follows:
 * Find the leftmost point.
 * From there find point w/ which it makes a line such that no points to its left
 * Set that point to the current point, keep going until you wrap around.
 *
 */

void DoGiftWrap(vector<Tuple*> points, ConvexHullApp *app)
{
    int current_index;
    int test;
    int left_index = leftMost(points);

    app->add_to_hull(points[left_index]);
    current_index = left_index;
    do{
        test = -1;
        for (int i = 1; i < (int)points.size(); i++){
            if (i != current_index){
                if (test == -1){
                    test = i;
                }
                int left = leftTurn(points[current_index], points[i], points[test]);
                if (!left){
                    test = i;
                }
            }
        }
        current_index = test;
        app->add_to_hull(points[current_index]);

    } while (current_index != left_index);
}

 /**
 * TODO: Implement this function.
 */

/**
 * Graham Scan Algorithm:
 * find the bottommost point, P.  We know it's in the convex hull.
 * sort the points w.r.t angle they make relative to P.
 * Then consider these points -- if they make a left turn, it is added to the hull
 * if not then we pop the last element and keep going until we find a left turn.
 *
 */
void DoGrahamScan(vector<Tuple*> points, ConvexHullApp *app)
{
    //find bottommost point
    int bottom = points[0]->y;
    int bottom_index = 0;
    double angle;
    vector<double> angles;
    vector<Tuple*> hull;
    for (int i = 1; i < (int)points.size(); i++){
        if (points[i]->y < bottom){
            bottom = points[i]->y;
            bottom_index = i;
        }
    }

    //temporarily take it out of the vector so we can sort the rest of them
    Tuple *bottom_point = points[bottom_index];
    points.erase(points.begin() + bottom_index);

    // make angles vector
    for (int i = 0; i < (int)points.size(); i++){
        angle = bottom_point->angle_wrt_pt(points[i]);
        angles.push_back(angle);
    }
    // sort angles and points
    sort(points, angles, 0, (int)points.size() - 1);

    //add the bottom point back
    points.insert(points.begin(), bottom_point);

    //we know these will be in the hull
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    hull.push_back(points[2]);

    //if the second to top, top, and i, make a right turn this doesn't work! pop!
    for (int i = 3; i < (int)points.size(); i++){
        while (!leftTurn(hull[hull.size() - 2], hull[hull.size() - 1], points[i])){
            hull.pop_back();
        }
        //this one makes a left turn; keep it
        hull.push_back(points[i]);
    }
    //add the hull to the app and we're done
    for (unsigned int i = 0; i < hull.size(); i++){
        app->add_to_hull(hull[i]);
    }
    app->add_to_hull(points[0]);

    delete bottom_point;
}
