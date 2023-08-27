#include <stdio.h>
#include <math.h>

int addUpArray(int S[], int R[], int i, int j, int sqroot)
{
    int ret = 0;
    int k = i;
    while (k < j)
    {
        if (k % sqroot == 0)
        {
            k += sqroot;
            ret += R[k / sqroot];
            continue;
        }
        ret += S[k];
        k++;
    }

    return 0;
}

void updateArray(int S[], int R[], int i, int x, int sqrt)
{
    int rPos = i / sqrt;
    R[rPos] = R[rPos] - S[i];
    S[i] = x;
}

int main(void)
{
    int n, sqroot, x, i, j;
    scanf("%d", &n);
    sqroot = (int)sqrt(n);
    int S[n], R[sqroot];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &x);
        // int rPos = i / sqroot;
        // R[rPos] = R[rPos] - S[i];
        S[i] = x;
    }
    char operation;
    while (scanf("%c %d %d", &operation, &i, &j) == 3)
    {
        if (operation == 's')
        {
            printf("%d", addUpArray(S, R, i, j, sqroot));
        }
        else
        {
            updateArray(S, R, i, j, sqroot);
        }
    }
    return 0;
}