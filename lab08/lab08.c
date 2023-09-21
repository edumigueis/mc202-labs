#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_SIZE 250

typedef struct
{
    int key;
    int value;
} KeyValuePair;

typedef struct
{
    KeyValuePair dict[MAX_SIZE];
    int size;
} IntDict;

void initDict(IntDict *dict)
{
    dict->size = 0;
}

void insert(IntDict *dict, int key, int value)
{
    // Check if the key already exists in the dictionary
    for (int i = 0; i < dict->size; i++)
    {
        if (dict->dict[i].key == key)
        {
            // Key found, update the value
            dict->dict[i].value = value;
            return;
        }
    }

    // If the key doesn't exist, insert a new key-value pair
    if (dict->size < MAX_SIZE) // Dict must have space
    {
        dict->dict[dict->size].key = key;
        dict->dict[dict->size].value = value;
        dict->size++;
    }
}

int find(const IntDict *dict, int key)
{
    for (int i = 0; i < dict->size; i++)
    {
        if (dict->dict[i].key == key)
        {
            return dict->dict[i].value; // return value stored by key
        }
    }
    return -1; // Key not found
}

typedef struct
{
    int data[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack *stack)
{
    stack->top = -1;
}

int isEmpty(Stack *stack)
{
    return stack->top == -1;
}

void push(Stack *stack, int value)
{
    stack->data[++stack->top] = value;
}

int pop(Stack *stack)
{
    if (isEmpty(stack))
        return -1; // Return out of bounds value(can not pop)
    return stack->data[stack->top--];
}

int peek(Stack *stack)
{
    if (isEmpty(stack))
        return -1; // Return out of bounds value(can not peek)
    return stack->data[stack->top];
}

int isMatryoshka(const int *sequence, int n, Stack *stack, IntDict *sums)
{
    int isMatryoshka = 1;

    for (int i = 0; i < n; i++)
    {
        int num = sequence[i];
        int key = !isEmpty(stack) ? peek(stack) : 1;

        if (num < 0)
        {
            int valueFound = find(sums, key);
            // Update the sum for the current key
            if (key != 1)
                insert(sums, key, valueFound == -1 ? -num : valueFound - num);
            push(stack, num);
        }
        else
        {
            int popped = pop(stack);
            // Reset the sum for the popped key
            insert(sums, popped, 0);
            // Check if the popped value matches the current positive number(integrity of doll nesting)
            if (-num != popped)
                isMatryoshka = 0;
        }

        // Check if the current sum violates Matryoshka condition
        int numberFound = find(sums, key);
        if (numberFound != -1 && numberFound >= -key)
            isMatryoshka = 0;
    }

    return isMatryoshka && isEmpty(stack);
}

int main()
{
    int n;
    IntDict sums;
    Stack stack;
    while (scanf("%d", &n) == 1 && n != 0)
    {
        initialize(&stack);
        initDict(&sums);
        int sequence[n];

        for (int i = 0; i < n; i++)
            scanf("%d", &sequence[i]);

        int result = isMatryoshka(sequence, n, &stack, &sums);

        if (result)
            printf(":-) Matriosca!\n");
        else
            printf(":-( Tente novamente.\n");
    }
}
