#include <stdio.h>
#include <math.h>

int addUpArray(int S[], int R[], int i, int j) {
    return 0;
}

void updateArray(int S[], int R[], int i, int j) {

}

int main(void)
{
    int n, S[n], R[n];
    for (int i = 0; i < n; i++)
    {
        fscanf(stdin, "%d", &S[i]);
    }
    for (int i = 0; i < n; i+=sqrt(n))
    {
        for(int j = i; j < j + sqrt(n); j++){
            R[i] = S[j];
        }
    }
    char operation;
    int i, j;
    while (scanf("%c %d %d", &operation, &i, &j) == 3)
    {
        if (operation == 's')
        {
            printf("%d", addUpArray(S, R, i, j));
        }
        else
        {
            updateArray(S, R, i, j);
        }
    }
    return 0;
}