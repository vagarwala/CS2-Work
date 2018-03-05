/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The bubble sort, quick sort, merge sort, and in-place quicksort
 * algorithms (implementation).
 *
 */
#include "sorter.hpp"
#include <cstdio>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
    // Set up buffers and data input
    std::vector<int> nums;
    std::string line;
    char *filename;
    int sort_type;

    // Ensure that at most one type of sort and at least a filename are specified.
    if (argc > 3 || argc < 2)
    {
        usage();
    }

    // default sort is bubble sort
    sort_type = BUBBLE_SORT;

    // Figure out which sort to use
    for (int i = 1; i < argc; ++i)
    {
        char *arg = argv[i];
        if (strcmp(arg, "-b") == 0) { sort_type = BUBBLE_SORT; }
        else if (strcmp(arg, "-q") == 0) { sort_type = QUICK_SORT; }
        else if (strcmp(arg, "-m") == 0) { sort_type = MERGE_SORT; }
        else if (strcmp(arg, "-qi") == 0) { sort_type = QUICK_SORT_INPLACE; }
        else { filename = argv[i]; }
    }

    // Read the file and fill our vector of integers
    // THIS FUNCTION IS STUDENT IMPLEMENTED
    readFile(filename, nums);

    switch (sort_type)
    {
        case BUBBLE_SORT:
        print_vector(bubbleSort(nums));
        break;

        case QUICK_SORT:
        print_vector(quickSort(nums));
        break;

        case MERGE_SORT:
        print_vector(mergeSort(nums));
        break;

        case QUICK_SORT_INPLACE:
        quicksort_inplace(nums, 0, nums.size() - 1);
        print_vector(nums);
        break;

        default:
        usage();
        break;
    }
    return 0;
}

/**
 * Usage    Prints out a usage statement and exits.
 */
void usage()
{
    std::cerr << usage_string << std::endl;
    exit(1);
}

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to sorter.hpp if you write a helper function!
 */

/**
 * TODO: Implement this function.
 */

/**
 * @brief swap is a helper function
 * often useful to swap two elements of a list when sorting
 * @params list, first index, second index
 * @return nothing; swaps elements at first and second indices in place
 */

void swap(std::vector<int> &list, int first, int second){
    int temp = list[first];
    list[first] = list[second];
    list[second] = temp;
}

/**
 * @brief bubbleSort sorts by "bubbling" up the larger elements
 * @params pointer to list to be sorted
 * @return nothing; sorts in place
 * bubble sort works as follows:
 * assume we have sorted the last i elements
 * steps through the list over and over (i increments each time)
 * step through the remaining elements (j counter)
 * if a pair of elements is in the wrong order, they get swapped
 * keeps going until it must be fully sorted
 *
 * IF list.size() <= 1
 *      return list
 * ENDIF
 * FOR int i = 0; i < list.size(); i++
 *      FOR int j = 0; j < list.size() - i - 1; j++
 *          IF list[j] . list[j + 1]
 *              swap(list[j], list[j + 1])
 *          ENDIF
 */

std::vector<int> bubbleSort(std::vector<int> &list)
{
    if((int)list.size() <= 1){
        return list;
    }
    int i, j;
    for(i = 0; i < (int)list.size(); i++){
        for(j = 0; j < (int)list.size() - i - 1; j++){
            if (list[j] > list[j + 1]){
                swap(list, j, j + 1);
            }
        }
    }

    return list;
}

/**
 * TODO: Implement this function.
 */
/** @brief quicksort!
 * @params pointer to list to be sorted
 * @return sorted list
 * outline is as follows:
 * think of sorting subarray array[a...b] (initially array[1...n-1])
 * divide by choosing an element in the subarray - the pivot - in this case, second element
 * rearrange so that all elements less than pivot are to its left 
 * & bigger elements are to the right.
 * recursively sort sub-subarrays array[a...c-1] and array[c+1...b] where c is the pivot
 * and we're done!
 *
 * IF list.size() <= 1
 *      return list
 * ENDIF
 * pivot = list[1]
 * for i = 0; i < list.size(); i++
 *      IF list[i] < pivot
 *          smaller.push_back(list[i])
 *      ELSE
 *          larger.push_back(list[i])
 *      ENDIF
 * smaller_sorted = quicksort(smaller)
 * larger_sorted = quicksort(larger)
 * return smaller_sorted + larger_sorted
 * 
 */
std::vector<int> quickSort(std::vector<int> &list)
{

    if(list.size() <= 1){
        return list;
    }
    vector<int> res;
    int pivot = list[0];
    vector<int> smaller;
    vector<int> larger;
    for(int i = 1; i < (int)list.size(); i++){
        if(list[i] <= pivot){
            smaller.push_back(list[i]);
        }else{
            larger.push_back(list[i]);
        }
    }
    smaller = quickSort(smaller);
    larger = quickSort(larger);
    for(int i = 0; i < (int)smaller.size(); i++){
        res.push_back(smaller[i]);
    }
    res.push_back(pivot);
    for(int i = 0; i < (int)larger.size(); i++){
        res.push_back(larger[i]);
    }
    return res;
}

/**
 * TODO: Implement this function.
 */
/** @brief mergesort helper!
 * @params pointer to list to be sorted, low index, high index
 * @return sorted list
 * outline as follows:
 * think of sorting a subarray array[a...b]; initially array[0....n-1]
 * split the subarray in half
 * recursively sort the two halves (when it is a one-element array, it is sorted)
 * combine the halves back together by merging them
 * 
 * IF low < high
 *      mid = (low + high)/2
 *      mergesort(low, mid)
 *      mergesort(mid + 1, high)
 *      merge(low, mid, high);
 * ENDIF
 *
 */

std::vector<int> mergeSortHelp(std::vector<int> &list, int low, int high){
    
    vector<int> left, right, left_sorted, right_sorted;
    if((int)list.size() <= 1){
        return list;
    }
    int mid = (low + high)/2;
    for(int i = 0; i < mid; i++){
        left.push_back(list[i]);
    }
    for(int i = mid; i < high; i++){
        right.push_back(list[i]);
    }
    left_sorted = mergeSortHelp(left, 0, (int)left.size());
    right_sorted = mergeSortHelp(right, 0, (int)right.size());
    return merge(left_sorted, right_sorted);
    
}

std::vector<int> mergeSort(std::vector<int> &list)
{
    if ((int)list.size() <= 1){
        return list;
    }
    return mergeSortHelp(list, 0, (int) list.size());
    
}



/**
 * TODO: Implement this function.
 */

/**
 * @brief merge - merges the two subarrays for mergesort
 * @params - pointers to two lists to merge
 * @return one (merged) list
 */

std::vector<int> merge(std::vector<int> &left, std::vector<int> &right)
{
    int i = 0;
    int j = 0;
    int len1 = left.size();
    int len2 = right.size();
    vector<int> res;
    while(i < len1 && j < len2){
        if(left[i] <= right[j]){
            res.push_back(left[i]);
            i++;
        } else{
            res.push_back(right[j]);
            j++;
        }
    }
    while(i < len1){
        res.push_back(left[i]);
        i++;
    }
    while(j < len2){
        res.push_back(right[j]);
        j++;
    }
    return res;
}

/**
 * @brief partition - used for quicksort, partitions elements of lists
 * as described in quicksort description, partitions in place
 * @params pointer to list being partitioned, portion we are paritioning
 * takes last element as pivot, places pivot at the proper position
 * smaller elements go to the left
 * larger elements go to the right
 * @return new index of puvot
 */

int partition(std::vector<int> &list, int low, int high){
    int pivot = list[high];
    int i = low - 1;
    for(int j = low; j < high; j++){
        if(list[j] <= pivot){
            i++;
            swap(list, i, j);
        }
    }
    swap(list, i+1, high);
    return (i + 1);
}

/*
 * quicksort_inplace:  In-place version of the quicksort algorithm. Requires
 *              O(1) instead of O(N) space, same time complexity. Each call of
 *              the method partitions the list around the pivot (an item taken
 *              from the middle of the array) with items left of the pivot
 *              smaller than it and items to its right larger than it. Then the
 *              method recursively sorts the left and right portions of the list
 *              until it reaches its base case: a list of length 1 is already
 *              sorted.
 *
 * @param list: pointer to integer array to be sorted
 * @returns:    Nothing, the array is sorted IN-PLACE.
 *
 * TODO: Implement this function.
 *
 * IF arr.size() <= 1
 *      return;
 * ENDIF
 * pick a pivot
 * partition arr into 2 halves
 * this time, instead of creating two new arrays, left and right, just swap elements into place
 * sort left[]
 * sort right[]
 * return left + right;
 */
void quicksort_inplace(std::vector<int> &list, int left, int right)
{
    if (left < right){
        int pivot = partition(list, left, right);
        quicksort_inplace(list, left, pivot - 1);
        quicksort_inplace(list, pivot + 1, right);
    }
}

