#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long N; // to make command line args global

void swap(int *a, int *b);
void quicksort(int *array, long start, long end);
long partition(int *array, long start, long end);
void printarray(int *array);

int main(int argc, char **argv)
{
  N = strtol(argv[1], NULL, 10);
  srand(time(NULL));                   // to randomise the numbers to be sorted
  int *array = calloc(N, sizeof(int)); // allocate memory for array
  for (long i = 0; i < N; i++)
  {
    array[i] = rand();
  }
  // printf("Unsorted Array:\n");
  // printarray(array);
  quicksort(array, 0, N - 1);
  // printf("\nSorted Array:\n");
  // printarray(array);
  free(array);
  return 0;
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
long partition(int *array, long start, long end)
{
  int pivot = array[end]; // last element is the pivot
  long i = start;         // i set at start of subarray
  for (long j = start; j < end; j++)
  {
    // iterates through whole array and if current element is smaller than the pivot then
    if (array[j] <= pivot)
    {
      // swap current element with the element at i, and increment i to point to the next element
      swap(&array[i], &array[j]);
      i++;
    }
  }
  // Finally pivot swapped with element at i, thus pivot has smaller elements to the left and larger to the right
  swap(&array[i], &array[end]);
  // return the partition index to p
  return i;
}
void quicksort(int *array, long start, long end)
{
  if (start < end)
  {
    // smaller elements left of index p and larger elements right of index p
    long p = partition(array, start, end);
    // partition into smaller subarrays using p
    quicksort(array, start, p - 1);
    quicksort(array, p + 1, end);
  }
}