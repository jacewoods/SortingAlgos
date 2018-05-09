#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

int ARRAY_LENGTH = 9999097; //max is 9999097

void recurseList(int arr[], int n, int timesToRecurse)
{
    //The base case; once timesToRecurse empties (reaches 0) the recursion stops
    if(timesToRecurse == 0)
        return;
    //Do this if timesToRecurse is still greater than 0
    else
    {
        int max = arr[0]; //Sets max to the first integer
        int largestIndex = 0;
        for(int i = 1; i < n; i++) //Loops through all elements of array
            //If the current 'max' is smaller than arr[i], make max = arr[i]
            if(arr[i] > max)
            {
                max = arr[i];
                largestIndex = i;
            }
        cout << arr[largestIndex] << endl; //Print out the largest number found in array
        arr[largestIndex] = 0; //Set largest number to 0
        recurseList(arr, n, --timesToRecurse); //Do it again, with the timesToRecurse element decrementing
    }
}

void insertionSort(vector<int> &vec, int n)
{
    for(int i = 1; i < n; i++)
    {
        int temp = vec[i];
        int j = i - 1;

        while(j >= 0 && vec[j] > temp)
        {
            vec[j+1] = vec[j];
            j = j - 1;
        }
        vec[j + 1] = temp;
    }
}

int getMax(int arr[], int n)
{
    int max = arr[0]; //Sets max to first number in array
    for (int i = 1; i < n; i++) //loop to set max to largest seen # until it reaches n
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void bucketSort(int arr[], int n) {
    //amount of seperate buckets, I.E. bins, for sorting
    int bucket = 100000;

    //This C++ compiler doesn't allow for variable length arrays, but this vector size will always be the same as 'Bucket'
    vector<int> B[100000];

    //find largest number in array
    int max = getMax(arr, n);

    //find number to set up divide in next group
    int divider = (max + 1) / bucket;

    //insert ints into bucket
    for(int i = 0; i < n; i++)
    {
        int j = arr[i] / divider; //Finds a bucket to place into B[j]
        B[j].push_back(arr[i]); //push_back is vector command for inserting an element to end of vector
    }

    //sort ints in the buckets
    for(int i = 0; i < bucket; i++)
        insertionSort(B[i], B[i].size()); //sorts the elements in current bucket using insertion sort


    //replaces current contents of array with the sorted contents from the 3D vector B
    int k = 0;
    for(int i = 0; i < bucket; i++)
    {
        for(int j = 0; j < B[i].size(); j++)
        {
            //First run of loop is B[0][j], with j incrementing through all numbers in bucket 0
            arr[k] = B[i][j];
            k++; //increments the array to place each sorted int
        }
    }
}



//Does counting sort based on current digit in arr[], based on k
void countSort(int arr[], int n, int k)
{
    int *C = (int *)malloc(sizeof(int)*n); //New empty array of size n
    int count[10] = {0}; //New array of 10 elements set at 0

    //Increments each digit 0-9 found at current level,
    //I.E. digits found in the 10s or 100s, etc. based on current stage of function
    for (int i = 0; i < n; i++)
        count[(arr[i]/k)%10]++;

    //Change count[i] to display actual position of this digit to properly place in C[] array
    for(int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    //Build the C[] array
    for(int i = n - 1; i >= 0; i--)
    {
        C[count[(arr[i]/k)%10] - 1] = arr[i]; //Sorts items based on current digit in function
        count[ (arr[i]/k) % 10]--; //Deincrements count to properly place integers in C[] array
    }

    //Copy C[] to arr[] so that arr[] contains sorted numbers based on current digit
    for(int i = 0; i < n; i++)
        arr[i] = C[i];
}


void radixSort(int arr[], int n)
{
    int m = getMax(arr, n); //Get max number to know largest number of digits in array

    //Do count sort for every digit
    //Loops until max / k results in 0, and k increments up a digit place every loop
    for(int k = 1; m/k > 0; k = k * 10)
        countSort(arr, n, k);
}

void merge(int arr[], int p, int q, int r)
{
    int *temp = new int[r-p+1]; //create temporary array
    int i = p, j = q + 1; //i is left-hand, j is right-hand
    int k = 0; //k is temp array

    while(i <= q && j <= r){
        if(arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    //copy data to temp arrays
    while(i <= q)
        temp[k++] = arr[i++];

    while(j <= r)
        temp[k++] = arr[j++];

    //put sorted temp elements into array
    for(k = 0, i = p; i <= r; ++i, ++k)
        arr[i] = temp[k];

    //clean up data
    delete [] temp;
}
void auxMergeSort(int arr[], int p, int r)
{
    int q;
    if(p < r){
        q = (p + r) / 2;
        auxMergeSort(arr, p, q);
        auxMergeSort(arr, q+1, r);
        merge(arr, p, q, r);
    }
}


int partition (int arr[], int p, int r)
{
    int x = arr[r]; //pivot
    int i = (p - 1); // index of smaller element

    for (int j = p; j <= r - 1; j++)
    {
        if (arr[j] <= x) //if current element is smaller than/equal to pivot
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[r];
    arr[r] = temp;

    return (i + 1);
}

void auxQuickSort(int arr[], int p, int r)
{
    if(p < r)
    {
        int q = partition(arr, p, r); //partitions and sorts segment of array

        //sort elements before and after partition
        auxQuickSort(arr, p, q - 1);
        auxQuickSort(arr, q + 1, r);
    }
}

bool recurseSort(int arr[], int i)
{
    if(i == 1 || i == 0)
        return true;
    if(arr[i-1] < arr[i-2])
        return false;
    return recurseSort(arr, i / 2);
    /*This method of dividing rather than iterating
     * i - 1 is required as recursion on large numbers
     * quickly overloads program*/
}

bool flgIsSorted(int arr[])
{
    bool check;
    int x = (ARRAY_LENGTH / 2) + 1; /* Sets up first recursive check
    *to compare the last element of first half to first element of second half*/

    check = recurseSort(arr, x);
    return check;
}

int main()
{
    ifstream in("lab3_data.txt");

    if(!in) //Checks to see if file exists
    {
        cout <<"Can't open file" << endl;
        return 1;
    }

    int *arrayBuild = (int *)malloc(sizeof(int)*ARRAY_LENGTH); //dynamic array based on ARRAY_LENGTH set globally

    for(int i = 0; i < ARRAY_LENGTH; i++) //builds array via numbers in text file
        in >> arrayBuild[i];
    //radixSort(arrayBuild, ARRAY_LENGTH);

    time_t start = clock();

    cout << "Largest 10 Numbers:" << endl;
    //Pass in the array and its length, and the number of times to perform the recursive function
    recurseList(arrayBuild, ARRAY_LENGTH, 10);

    double d = clock() - start;
    cout << "Time: " << d / CLOCKS_PER_SEC << " seconds" << endl << endl;

    //    long long totalAmount = 0; //"long long" to ensure large numbers accurately print out
    //    for(int i = 0; i < ARRAY_LENGTH; i++) //
    //    {
    //        totalAmount = totalAmount + arrayBuild[i];
    //    }

    //    cout << totalAmount << endl << endl;



    cout << "First 10 of array before sort:" << endl;
    for(int i = 0; i < 10; i++)
    {
        cout << arrayBuild[i] << endl;
    }


    cout << "Currently sorting " << ARRAY_LENGTH << " integers from the data list" << endl << endl;

    //auxQuickSort(arrayBuild, 0, ARRAY_LENGTH - 1);
    //bucketSort(arrayBuild, ARRAY_LENGTH);
    //radixSort(arrayBuild, ARRAY_LENGTH);

    cout << "First 10 of array after sort:" << endl;
    for(int i = 0; i < 10; i++)
    {
        cout << arrayBuild[i] << endl;
    }

    if(!flgIsSorted(arrayBuild))
        cout << "Not Sorted" << endl;
    else
        cout << "Sorted" << endl;

    return 0;
}
