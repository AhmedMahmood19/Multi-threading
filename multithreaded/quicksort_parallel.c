#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define isPrinting 0

int *arr;
long N;
long THRESHOLD;

// a stucture to pass as parameter to the thread creation function
// because we need to send multiple parameters but thread_create function only takes 1 arg parameter for the function it's calling
typedef struct
{
    int *arr;
    long start;
    long end;
} ThreadArg;

void swap(int *a, int *b);
void printarray(int *array);
void *quickSortThreadFunc(void *arg);
void quickSort(int *arr, long start, long end);
long partition(int *arr, long start, long end);

int main(int argc, char **argv)
{
    // dynamic allocation of array
    N = strtol(argv[1], NULL, 10);
    srand(time(NULL));
    arr = calloc(N, sizeof(int));
    THRESHOLD = N / 12;
    // generate an array of random numbers
    for (long i = 0; i < N; i++)
    {
        arr[i] = rand();
    }
    if (isPrinting)
    {
        printf("\nQuick Sort in Parallel for N=%ld\n",N);
        printf("\nUnsorted Array\n");
        printarray(arr);
    }
    quickSort(arr, 0, N - 1);
    if (isPrinting)
    {
        printf("\nSorted Array\n");
        printarray(arr);
    }
    free(arr);
}

// function to convert our void arg which are standard for pthread into normal arguements that could be sent as parameter to our quicksort function
// called on thread creation
void *quickSortThreadFunc(void *arg)
{
    // typeCasting
    ThreadArg *qarg = (ThreadArg *)arg;
    // printf("\n~Thread created~\n");
    quickSort(qarg->arr, qarg->start, qarg->end);
    return NULL;
}
void quickSort(int *arr, long start, long end)
{
    if (start < end)
    {
        long pi = partition(arr, start, end);
        pthread_t id = 0;
        ThreadArg arg = {arr, start, pi - 1};
        // threshold is basically a level if end-start < threshold then creating threads isnt efficient and thus normal sequential call is better
        // threshold calculation can differ, it's hardcoded, threshold = maxlength / 12 ;
        if (arg.end - arg.start > THRESHOLD)
        {
            pthread_create(&id, NULL, quickSortThreadFunc, &arg); // new thread created for left partition only because we already have a thread so we need only 1 more
            // eg. 1 thread running the quicksort, now if we need another thread we'll make a thread for the left partition while right partition stays on the main thread
            //  thus we'll get 2 threads.
            // creating two threads for left and right would result in extra thread creation as we already have on main thread which could be utilised
        }
        else
        {
            quickSort(arr, start, pi - 1); // recursive call for left partition
        }
        quickSort(arr, pi + 1, end); // recursive call for right partition
        if (id != 0)
        {
            pthread_join(id, NULL);
        }
    }
}

long partition(int *arr, long start, long end)
{
    int pivot = arr[end];
    long i = start;
    for (long j = start; j < end; ++j)
    {
        // If current element is smaller than pivot
        if (arr[j] <= pivot)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[end]);
    return i;
}
void printarray(int *array)
{
    for (long i = 0; i < N; i++)
    {
        printf("%d\n", array[i]);
    }
}
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}