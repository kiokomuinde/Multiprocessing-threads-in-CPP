// CPP Program to implement a parallel algorithm of a merge sort
#include <iostream>
#include <time.h>

// Defining maximum number of the items of the array
#define MAX 2000000

// number of threads
#define THREAD_MAX 4

using namespace std;

// Declaring an array of size max
int a[MAX];

//Declaring the parts of our multithreading
int part = 0;

// merge function for merging two parts
void merge(int low, int mid, int high)
{
    int* left = new int[mid - low + 1];
    int* right = new int[high - mid];

    // leftSize is size of left part and rightSize is size
    // of right part
    int leftSize = mid - low + 1, rightSize = high - mid, i, j;

    // storing values in left part
    for (i = 0; i < leftSize; i++)
        left[i] = a[i + low];

    // storing values in right part
    for (i = 0; i < rightSize; i++)
        right[i] = a[i + mid + 1];

    int k = low;
    i = j = 0;

    // merge left and right in ascending order
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }

    // insert remaining values from left
    while (i < leftSize) {
        a[k++] = left[i++];
    }

    // insert remaining values from right
    while (j < rightSize) {
        a[k++] = right[j++];
    }
}

// merge sort function
void merge_sort(int low, int high)
{
    // calculating mid point of array
    int mid = low + (high - low) / 2;
    if (low < high) {

        // calling first half
        merge_sort(low, mid);

        // calling second half
        merge_sort(mid + 1, high);

        // merging the two halves
        merge(low, mid, high);
    }
}

// Driver Code
int main()
{
    // Feeding our array of size max with values ranging from 0 to ten million
    for (int i = 0; i < MAX; i++)
        a[i] = rand() % 10000000;

    // t1 and t2 for calculating time taken by the merge sort
    clock_t t1, t2;

    t1 = clock();
    
    merge_sort(0, MAX);

    t2 = clock();

    // displaying sorted array
    cout << "Sorted array: ";
    for (int i = 0; i < MAX; i++)
        cout << a[i] << endl;

    // time taken by merge sort in seconds
    cout << "Time taken in seconds: " << (t2 - t1) /
            (double)CLOCKS_PER_SEC << endl;

    return 0;
}
