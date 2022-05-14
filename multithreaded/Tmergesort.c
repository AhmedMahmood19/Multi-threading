#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

// No. of elements in the array
long N;

// No. of threads
#define N_THREAD 7

// array to be sorted
int *array;

// parameters that will be needed for threads
struct threadparam
{
    long start;
    long end;
};

void printarray();
void *threadmerge(void *arg);
void mergesort(long start, long end);
void merge(long start, long mid, long end);

int main(int argc, char **argv)
{
    N=strtol(argv[1],NULL,10);
    srand(time(NULL));
    array=calloc(N,sizeof(int));//allocate memory for array
    // Random numbers are filled into the array    
    for (long i = 0; i < N; i++)
    {
        array[i] = rand() % 1000;
    }
    printf("Unsorted Array:\n");
    // printarray();

    // array for thread ids and thread parameters are declared
    pthread_t tid[N_THREAD];
    struct threadparam tplist[N_THREAD];
    //total elements divided by total threads so array is divided amongst threads as equally as possible(subN is size of subarrays)
    long subN = N / N_THREAD;
    //the start index of the first subarray will be 0 
    long start = 0;

    // thread parameters are set
    for (int i = 0; i < N_THREAD; i++)
    {
        if (i == (N_THREAD - 1))
        {
            //if last subarray:
            //end index will be one less than total length of whole array
            tplist[i].end = N - 1;
        }
        else
        {
            //if it's not the last subarray:
            //end index of a subarray will be one less than start index of next subarray
            tplist[i].end = (start + subN) - 1;
        }
        tplist[i].start = start;
        //start index is incremented by the No. of elements in sub array to get start index of next subarray
        start += subN;
    }

    // threads created
    for (int i = 0; i < N_THREAD; i++)
    {
        pthread_create(&tid[i], NULL, threadmerge, &tplist[i]);
    }

    // threads joined
    for (int i = 0; i < N_THREAD; i++)
    {
        pthread_join(tid[i], NULL);
    }

    // The final merged subarray of each thread will be all merged together
    for (int i = 1; i < N_THREAD; i++)
    {
        //the subarrays are merged one by one going from left to right(the left subarray grows)
        merge(tplist[0].start, tplist[i].start - 1, tplist[i].end);
    }

    // Print sorted array
    printf("Sorted Array:\n");
    // printarray();
    free(array);
    return 0;
}
// Merges two subarrays
void merge(long start, long mid, long end)
{
    long i1 = start, i2 = mid + 1;
    long n1 = mid - start + 1;
    long n2 = end - mid;
    int *arr1 = calloc(n1, sizeof(int));
    int *arr2 = calloc(n2, sizeof(int));
    for (long i = 0; i < n1; i++)
    {
        arr1[i] = array[i + i1];
    }
    for (long i = 0; i < n2; i++)
    {
        arr2[i] = array[i + i2];
    }
    long i = start;
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
void mergesort(long start, long end)
{
    if (start < end)
    {
        long mid = (start + end) / 2;
        mergesort(start, mid);
        mergesort(mid + 1, end);
        merge(start, mid, end);
    }
}

// thread function for multi-threading
void *threadmerge(void *arg)
{
    struct threadparam *tp = arg;
    long start = tp->start;
    long end = tp->end;

    if (start < end)
    {
        long mid = (start + end) / 2;
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
    for (long i = 0; i < N; i++)
    {
        printf("%d\n", array[i]);
    }
    printf("\n");
}
