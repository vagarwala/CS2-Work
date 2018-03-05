#include <iostream>
using namespace std;
 
int findUnique(int arr[], int n)
{
    // xor all the elements, because n xor n = 0, and n xor 0 = 0 xor n = n.
	// so as we keep xor-ing, the only thing that should remain at the end is the unique element
    int res = arr[0];
    for (int i=1; i < n; i++)
       res = res ^ arr[i];
 
    return res;
}

int main()
{
    int arr[] = {1, 5, 2, 3, 3, 4, 1, 5, 4};
    int n = sizeof(ar)/sizeof(ar[0]);
    cout << "Element occurring once is " << findUnique(arr, n) << ", should be 2." << endl;
    return 0;
}