#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 3000


double read_timer()
{
    static bool initialized = false;
    static struct timeval start;
    struct timeval end;
    if (!initialized)
    {
        gettimeofday(&start, NULL);
        initialized = true;
    }
    gettimeofday(&end, NULL);
    return (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
}

double start_time, end_time; /* start and end times */


void quicksort(int number[25], int first, int last)
{

    int i, j, pivot, temp;

    if (first < last)
    {

        pivot = first;

        i = first;

        j = last;

        while (i < j)
        {

            while (number[i] <= number[pivot] && i < last)
                i++;

            while (number[j] > number[pivot])
                j--;

            if (i < j)
            {

                temp = number[i];

                number[i] = number[j];

                number[j] = temp;
            }
        }

        temp = number[pivot];

        number[pivot] = number[j];

        number[j] = temp;

        quicksort(number, first, j - 1);

        quicksort(number, j + 1, last);
    }
}

int main()
{

    int i, arr[N];

     // generate an array of random numbers 
    for (int i=0 ; i<N ; i++){
        arr[i] = rand()%999;
    }
    start_time = read_timer(); //read time before running the function

    quicksort(arr, 0, N - 1);

    end_time = read_timer();// read time after function ends

    printf("The Sorted Order is: ");

    for (i = 0; i < N; i++)
        printf(" %d", arr[i]);

    printf("\n");
    printf("The execution time was:  %lf secs\n", end_time - start_time);
    return 0;
}