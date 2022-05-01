#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 20 // array size

void mergesort(int start, int end, int *array);
void merge(int start, int mid, int end, int *array);
void printarray(int *array);
int main()
{
    srand(time(NULL)); // to randomise the numbers to be sorted
    int array[N];
    for (int i = 0; i < N; i++)
    {
        array[i] = rand()%1000;
    }
    printf("Unsorted Array:\n");
    printarray(array);
    mergesort(0, N - 1, array);
    printf("\nSorted Array:\n");
    printarray(array);
}
void printarray(int *array){
    for (int i = 0; i < N; i++)
    {
        printf("%d\n", array[i]);
    }
}
void mergesort(int start, int end, int *array)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        mergesort(start, mid, array);
        mergesort(mid + 1, end, array);
        merge(start, mid, end, array);
    }
}
void merge(int start, int mid, int end, int *array){
    int i1=start,i2=mid+1;          //starting index for arr1 and arr2
    int n1=mid-start+1, n2=end-mid; //length of arr1 and arr2
    int *arr1=calloc(n1,sizeof(int));//creation of subarrays
    int *arr2=calloc(n2,sizeof(int));
    for (int i = 0; i < n1; i++)    //fill each subarray
    {
        arr1[i]=array[i+i1];
    }
    for (int i = 0; i < n2; i++)
    {
        arr2[i]=array[i+i2];
    }
    int i=start;    //starting index for merged array
    i1=0;
    i2=0;
    while (i1<n1 && i2<n2)//merging arrays while sorting it
    {
        if (arr1[i1]<=arr2[i2])
        {
            array[i]=arr1[i1];
            i1++;
        }
        else
        {
            array[i]=arr2[i2];
            i2++;
        }
        i++;
    }
    while (i1<n1)
    {
        array[i]=arr1[i1];
        i++;
        i1++;
    }
    while (i2<n2)
    {
        array[i]=arr2[i2];
        i++;
        i2++;
    }
    free(arr1); //deallocate memory for subarrays
    free(arr2);
}