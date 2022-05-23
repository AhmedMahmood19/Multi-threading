#include <stdio.h>
#include <stdlib.h>

#define A 2 // first term in AP is used in HP
#define D 3 // common difference from AP used in HP
#define isPrinting 0

int main(int argc, char **argv)
{
    long N = strtol(argv[1], NULL, 10);
    double *arr = malloc(N * sizeof(double));
    long a = A;
    long d = D;
    for (long i = 0; i < N; i++)
    {
        arr[i] = (double)1 / (a + (i)*d);
    }
    if (isPrinting)
    {
        printf("\nHarmonic Progression a=%d d=%d n=%ld\n", A, D,N);
        for (long i = 0; i < N; i++)
        {
            printf("%lf\n", arr[i]);
        }
    }
    free(arr);
}