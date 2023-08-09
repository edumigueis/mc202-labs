#include <stdio.h>

// Funcao para determinar a soma dos divisores proprios de um numero
int sumPrimeDividers(int num)
{
    int sum = 0;
    for (int i = 1; i <= num / 2; i++)
        if (num % i == 0)
            sum += i;

    return sum;
}

int main(void)
{
    int first = 0;
    int second = 0;
    scanf("%d %d", &first, &second);
    if (sumPrimeDividers(first) == second && sumPrimeDividers(second) == first)
        printf("%d e %d sao amigos\n", first, second);
    else
        printf("%d e %d nao sao amigos\n", first, second);
    return 0;
}