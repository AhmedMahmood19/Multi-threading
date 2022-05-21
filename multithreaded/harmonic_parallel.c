#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define A 2 //first term in AP is used in HP
#define D 3 //common difference from AP used in HP
#define N_THREAD 4  //Number of threads

long N; //No. of elements
double *arr;    //The array where the series is stored

//arguments sent to each thread function
struct threadparam
{
    long start; //starting index of subarray
    long end; //ending index of subarray
};

void *generate(void *ptr)
{      
    struct threadparam *x = ptr;
    for (long i = x->start; i <= x->end; i++)
    {
        arr[i]=(double)1/(A+(i*D)); //formula for Nth term but indexing of array starts at 0
    }
}

int main(int argc, char **argv)
{   
    N=strtol(argv[1],NULL,10);
    arr = malloc(N * sizeof(double)); //allocate memory for array
    
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
        pthread_create(&tid[i], NULL, generate, &tplist[i]);
    }
    //join all the threads
    for(long i=0;i<N_THREAD;i++)
    {
        pthread_join(tid[i], NULL);    
    }
    // //print the series
    // for(long i=0;i<N;i++)
    // {
    //     printf("%lf\n",arr[i]);
    // }
    free(arr);
}