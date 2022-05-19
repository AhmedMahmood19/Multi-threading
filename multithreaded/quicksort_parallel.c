#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>

int *arr;
long N;
long THRESHOLD;

#define swap(x, y) \
    int _t = x;    \
    x = y;         \
    y = _t;


void printArray(int const *arr, int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }
    puts("");
}

// a stucture to pass as parameter to the thread creation function
// because we need to send multiple parameters but thread_create function only takes 1 arg parameter for the function it's calling
typedef struct
{
    int *arr;
    int lo;
    int hi;
} ThreadArg;

int partition(int *arr, long lo,  long hi)
{
    int pivot = arr[hi];
    int i = lo - 1;
    for (long j = lo; j < hi; ++j)
    {
        // If current element is smaller than pivot
        if (arr[j] < pivot)
        {
            ++i;
            swap(arr[i], arr[j]);
            // i++; // increment index of smaller element
        }
    }
    swap(arr[i + 1], arr[hi]);
    return i + 1;
}

void *quickSortThreadFunc(void *arg);

void quickSortHelper(int *arr,   long lo, long hi)
{
    if (lo < hi)
    {
        int pi = partition(arr, lo, hi);
        pthread_t id = 0;
        ThreadArg arg = {arr, lo, pi - 1};
        // threshold is basically a level if hi-lo < threshold then creating threads isnt efficient and thus normal sequential call is better
        // threshold calculation can differ, it's hardcoded, threshold = maxlength / 12 ;
        if (arg.hi - arg.lo > THRESHOLD)
        {
            pthread_create(&id, NULL, quickSortThreadFunc, &arg); //new thread created for left partition only because we already have a thread so we need only 1 more
            //eg. 1 thread running the quicksort, now if we need another thread we'll make a thread for the left partition while right partition stays on the main thread
            // thus we'll get 2 threads.
            //creating two threads for left and right would result in extra thread creation as we already have on main thread which could be utilised
        }
        else
        {
            quickSortHelper(arr, lo, pi - 1); //recursive call for left partition
        }
        quickSortHelper(arr, pi + 1, hi); //recursive call for right partition
        if (id != 0)
        {
            pthread_join(id, NULL);
        }
    }
}

// function to convert our void arg which are standard for pthread into normal arguements that could be sent as parameter to our quicksort function
// called on thread creation
void *quickSortThreadFunc(void *arg)
{
    // typeCasting
    ThreadArg *qarg = (ThreadArg *)arg;
    printf("\n~Thread created~\n");
    quickSortHelper(qarg->arr, qarg->lo, qarg->hi);
    return NULL;
}

void quickSort(int *arr, int size)
{
    // actual quick sort function
    quickSortHelper(arr, 0, size - 1);
}

int main()
{
    // dynamic allocation of array
    N=10000000;
    THRESHOLD=N/12;
    arr = malloc(N * sizeof(long));

    // generate an array of random numbers
    for (long i = 0; i < N; i++)
    {
        arr[i] = rand() % 999;
    }

    printf("Unsorted\n");
    for (long i = 0; i < N; i++)
    {
        printf(" %d ", arr[i]);
    }

    quickSort(arr, N);

    printf("Sorted\n");
    for (long i = 0; i < N; i++)
    {
        printf(" %d ", arr[i]);
    }
    
    free(arr);
}