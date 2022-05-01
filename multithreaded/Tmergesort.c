#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

// No. of elements in the array
#define N 30

// No. of threads
#define N_THREAD 7

// array to be sorted
int array[N];

// parameters that will be needed for threads
struct threadparam
{
    int start;
    int end;
};

// Merges two subarrays
void merge(int start, int mid, int end)
{
    int i1 = start, i2 = mid + 1;
    int n1 = mid - start + 1;
    int n2 = end - mid;
    int *arr1 = calloc(n1, sizeof(int));
    int *arr2 = calloc(n2, sizeof(int));
    for (int i = 0; i < n1; i++)
    {
        arr1[i] = array[i + i1];
    }
    for (int i = 0; i < n2; i++)
    {
        arr2[i] = array[i + i2];
    }
    int i = start;
    i1 = 0;
    i2 = 0;
    while (i1 < n1 && i2 < n2)
    {
        if (arr1[i1] <= arr2[i2])
        {
            array[i] = arr1[i1];
            i1++;
        }
        else
        {
            array[i] = arr2[i2];
            i2++;
        }
        i++;
    }
    while (i1 < n1)
    {
        array[i] = arr1[i1];
        i++;
        i1++;
    }
    while (i2 < n2)
    {
        array[i] = arr2[i2];
        i++;
        i2++;
    }
    free(arr1);
    free(arr2);
}

// Divides the array into subarrays
void mergesort(int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        mergesort(start, mid);
        mergesort(mid + 1, end);
        merge(start, mid, end);
    }
}

// thread function for multi-threading
void *threadmerge(void *arg)
{
    struct threadparam *tsk = arg;
    int start = tsk->start;
    int end = tsk->end;

    if (start < end)
    {
        int mid = (start + end) / 2;
        mergesort(start, mid);
        mergesort(mid + 1, end);
        merge(start, mid, end);
    }
    return 0;
}
// print the array
void printarray()
{
    printf("\n");
    for (int i = 0; i < N; i++)
    {
        printf("%d\n", array[i]);
    }
    printf("\n");
}

int main()
{
    // Random numbers are filled into the array
    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        array[i] = rand() % 1000;
    }
    printf("Unsorted Array:");
    printarray();

    // array for thread id and thread parameters are declared
    pthread_t tid[N_THREAD];
    struct threadparam tsklist[N_THREAD];
    //total elements divided by total threads so array is divided amongst threads as equally as possible
    int subN = N / N_THREAD;
    //the start index of the first subarray will be 0 
    int start = 0;

    // thread parameters are set
    for (int i = 0; i < N_THREAD; i++)
    {
        if (i == (N_THREAD - 1))
        {
            //if last subarray:
            //end index will be one less than total length of whole array
            tsklist[i].end = N - 1;
        }
        else
        {
            //if its not the last subarray:
            //end index of a subarray will be one less than start index of next subarray
            tsklist[i].end = (start + subN) - 1;
        }
        tsklist[i].start = start;
        //start index is incremented by the No. of elements in sub array to get start index of next subarray
        start += subN;
    }

    // threads created
    for (int i = 0; i < N_THREAD; i++)
    {
        pthread_create(&tid[i], NULL, threadmerge, &tsklist[i]);
    }

    // threads joined
    for (int i = 0; i < N_THREAD; i++)
    {
        pthread_join(tid[i], NULL);
    }

    // The final merged subarray from each thread are all merged together
    for (int i = 1; i < N_THREAD; i++)
    {
        //the subarrays are merged one by one going from left to right(the left subarray cumulates)
        merge(tsklist[0].start, tsklist[i].start - 1, tsklist[i].end);
    }

    // Print sorted array
    printf("Sorted array:");
    printarray();
    return 0;
}