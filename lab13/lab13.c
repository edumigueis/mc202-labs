#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int n;
    while (1) {
        // Ler o número de PDVs
        scanf("%d", &n);

        // Verificar se é o último bloco
        if (n == 0) {
            break;
        }

        // Processar cada linha do bloco
        for (int i = 0; i < n; i++) {
            int pdv, connected_pdv;
            
            // Ler o número do PDV
            scanf("%d", &pdv);

            // Ler os PDVs conectados
            for (int j = 0; j < n - 1; j++) {
                scanf("%d", &connected_pdv);
                // Processar a conexão (faça o que for necessário com as informações)
            }
        }

        // Ler a linha que contém apenas zero para indicar o fim do bloco
        int end_of_block;
        scanf("%d", &end_of_block);
        if (end_of_block != 0) {
            return 1;
        }
    }
    return 0;
}