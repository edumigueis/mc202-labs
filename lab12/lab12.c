#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_STR_SIZE 250
#define SCANF_FORMAT "%249[^\n]"
#define REMOVED_KEY_MARKER "###REMOVED###"

typedef struct KeyPair
{
    char *key;
    int value;
} KeyPair;

typedef struct HashTable
{
    // Contains an array of pointers to items.
    KeyPair **items;
    int size;
    int count;
} HashTable;

// Free memory allocated for the hash table
void free_hashtable(HashTable *ht)
{
    for (int i = 0; i < ht->size; i++)
    {
        free(ht->items[i]->key);
        free(ht->items[i]);
    }
    free(ht->items);
    free(ht);
}

// Initialize a hash table with a specified size
int init(HashTable *ht, int size)
{
    ht->size = size * 2;
    ht->count = 0;
    ht->items = (KeyPair **)calloc(ht->size, sizeof(KeyPair *));
    if (ht->items == NULL)
        return 0;
    for (int i = 0; i < ht->size; i++)
    {
        ht->items[i] = (KeyPair *)malloc(sizeof(KeyPair));
        if (ht->items[i] == NULL)
        {
            free_hashtable(ht);
            return 0;
        }
        ht->items[i]->key = NULL; // Initialize key to NULL
    }
    return 1;
}

unsigned long djb2_hash(char *str) // DJB2 hash function
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) ^ c; // hash * 33 XOR c

    return hash;
}

unsigned long xor_hash(char *key) // XOR hash function
{
    unsigned long hash_value = 0;
    int c;

    while ((c = *key++))
    {
        hash_value = ((hash_value << 4) + hash_value) ^ c;
    }

    return hash_value;
}

unsigned long double_hashing(char *key, int i, int size) // Double hashing function
{
    unsigned long first_hash = djb2_hash(key);
    unsigned long second_hash = xor_hash(key);
    return (first_hash + i * second_hash) % size;
}

char *my_strdup(const char *str) // Custom strdup function
{
    if (str == NULL)
        return NULL;

    size_t length = strlen(str);
    char *new_str = (char *)malloc(length + 1);

    if (new_str == NULL)
        return NULL;

    strcpy(new_str, str);

    return new_str;
}

// Insert a key-value pair into the hash table
void insert_key(HashTable *ht, char *item, int timestamp)
{
    if (ht->count == ht->size)
        return;

    int i = 0;

    do
    {
        int index = double_hashing(item, i, ht->size);

        if (ht->items[index]->key == NULL || strcmp(ht->items[index]->key, REMOVED_KEY_MARKER) == 0)
        {
            ht->items[index]->key = my_strdup(item);
            ht->items[index]->value = timestamp;
            return;
        }
        i++;
    } while (i < ht->size);

    ht->count++;
}

// Remove a key from the hash table
void remove_key(HashTable *ht, char *key)
{
    int i = 0;
    int index;

    do
    {
        index = double_hashing(key, i, ht->size);

        if (ht->items[index]->key == NULL)
            return;

        if (strcmp(ht->items[index]->key, key) == 0)
        {
            free(ht->items[index]->key);
            ht->items[index]->key = my_strdup(REMOVED_KEY_MARKER);
            return;
        }

        // Collision occurred, so we try the next position
        i++;
    } while (i < ht->size);
}

// Get the timestamp associated with a key in the hash table
int get_timestamp(HashTable *ht, char *key)
{
    int i = 0;
    int index;

    do
    {
        index = double_hashing(key, i, ht->size);

        if (ht->items[index]->key == NULL)
            return -1;

        if (strcmp(ht->items[index]->key, key) == 0)
            return ht->items[index]->value;

        // Collision occurred, so we try the next position
        i++;
    } while (i < ht->size);

    return -1;
}

int main(void)
{
    char cmd;
    int timestamp = 0;
    int size;
    char *str = (char *)malloc(MAX_STR_SIZE);
    HashTable *ht = NULL;

    while (1)
    {
        scanf(" %c", &cmd);
        getchar();
        if (cmd == 'c')
        {
            scanf(" %d", &size);
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
            scanf(SCANF_FORMAT, str);
            if (get_timestamp(ht, str) == -1)
            {
                insert_key(ht, str, timestamp);
                timestamp++;
            }
        }
        else if (cmd == 'r')
        {
            scanf(SCANF_FORMAT, str);
            remove_key(ht, str);
        }
        else if (cmd == 'b')
        {
            scanf(SCANF_FORMAT, str);
            int t = get_timestamp(ht, str);
            if (t == -1)
                printf("[%s] nao esta na tabela\n", str);
            else
                printf("[%s] esta na tabela, timestamp %d\n", str, t);
        }
        else if (cmd == 'f')
        {
            free_hashtable(ht);
            free(str);
            return 0;
        }
        else
        {
            printf("Invalid command: %c.\n", cmd);
            free_hashtable(ht);
            free(str);
            return 1;
        }
    }
}