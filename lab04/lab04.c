#include <stdio.h>
#include <math.h>

// Adds up the data sctructure and the array within the i-j range
int addUpArray(int S[], int R[], int i, int j, int sqroot)
{
    int ret = 0;
    int k = i; // counter for getting the positions to add up
    while (k <= j)
    {
        if (k % sqroot == 0 && k + sqroot <= j)
        {
            k += sqroot;
            ret += R[(k / sqroot) - 1]; // relative position in R to S
            continue;                   // adding 1 is not necessary
        }
        ret += S[k];
        k++;
    }

    return ret;
}

int main(void)
{
    // essential variables
    int n, x, inp1, inp2;
    scanf("%d", &n);
    int rsize = ceil(sqrt(n));
    int S[n], R[rsize];

    // starts up arrays with 0s
    for (int i = 0; i < n; i++)
        S[i] = 0;
    for (int i = 0; i < rsize; i++)
        R[i] = 0;

    // boots data sctructures(starter values)
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &x);
        int rPos = i / rsize;
        S[i] = x;
        R[rPos] += x;
    }

    // main loop
    char operation;
    // reads while input matches
    while (scanf(" %c %d %d", &operation, &inp1, &inp2) == 3)
    {
        if (operation == 's')
            printf("%d\n", addUpArray(S, R, inp1, inp2, rsize));
        else
        {
            int rPos = floor(inp1 / rsize);
            R[rPos] -= S[inp1]; // subtract previous value and add new from R
            S[inp1] = inp2;
            R[rPos] += inp2;
        }
    }
    return 0;
}