#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char cmd;
    int n, key, cost;
    Graph graph;

    while (1)
    {
        scanf(" %c", &cmd);
        getchar();
        if (cmd == 'c')
        {
            scanf(" %d", &n);
            if (ht != NULL)
                free_hashtable(ht);
            ht = (HashTable *)malloc(sizeof(HashTable));
            int worked = init(ht, size);
            if (!worked || ht == NULL)
            {
                printf("Unable to create a hash table.\n");
                return 1;
            }
        }
        else if (cmd == 'i')
        {
            scanf("%d %d ", &key, &cost);
            insert_key(ht, str, timestamp) + 1;
        }
        else if (cmd == 'm')
        {
            remove_min(ht, str);
        }
        else if (cmd == 'd')
        {
            scanf("%d %d ", &key, &cost);
            lower_cost(ht, str);
        }
        else if (cmd == 't')
        {
            free_all(ht);
            return 0;
        }
        else
        {
            printf("Invalid command: %c.\n", cmd);
            free_all(ht);
            return 1;
        }
    }
}