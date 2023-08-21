#include <math.h>
#include <stdio.h>

//Calcula a distancia entre dois pontos
float calcDistance(float x1, float y1, float x2, float y2)
{
    float deltaX = x1 - x2;
    float deltaY = y1 - y2;
    return sqrt((deltaX * deltaX) + (deltaY * deltaY));
}

int main(void)
{
    int holeCount = 0;
    float bunnyX, bunnyY, foxX, foxY = 0;
    scanf("%d %f %f %f %f", &holeCount, &bunnyX, &bunnyY, &foxX, &foxY);
    for (int i = 0; i < holeCount; i++)
    {
        float holeX, holeY = 0;
        scanf("%f %f", &holeX, &holeY);
        // Comparar as distancias e suficiente para deterinar quem vai chegar primeiro
        if (calcDistance(holeX, holeY, bunnyX, bunnyY) <= calcDistance(holeX, holeY, foxX, foxY) / 2)
        {
            printf("O coelho pode escapar pelo buraco (%.3f,%.3f).\n", holeX, holeY);
            return 0;
        }
    }
    printf("O coelho nao pode escapar.\n");
    return 0;
}