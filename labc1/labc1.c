#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int key;
    int cost;
} Item;

typedef struct
{
    Item *heap;
    int *indexes;
    int max;
    int size;
} InMinHeap;

InMinHeap *create_indexed_heap(int size)
{
    InMinHeap *minHeap = (InMinHeap *)malloc(sizeof(InMinHeap));
    minHeap->heap = (Item *)malloc(sizeof(Item) * size);
    minHeap->indexes = (int *)malloc(sizeof(int) * size);
    if (minHeap->indexes == NULL || minHeap->heap == NULL)
        return NULL;
    minHeap->max = size;
    minHeap->size = 0;

    for (int i = 0; i < size; ++i)
        minHeap->indexes[i] = -1; // start indexes with empty cost(-1)

    return minHeap;
}

// frees items from memory
void free_heap(InMinHeap *heap)
{
    free(heap->indexes);
    free(heap->heap);
    free(heap);
}

// exchange two items in the heap
void exchange(Item *a, Item *b)
{
    Item aux = *a;
    *a = *b;
    *b = aux;
}

// update heap bottom-up
void heapify_up(InMinHeap *minHeap, int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (minHeap->heap[parent].cost > minHeap->heap[index].cost)
        {
            // Swap the element with its parent if necessary
            exchange(&minHeap->heap[parent], &minHeap->heap[index]);
            minHeap->indexes[minHeap->heap[parent].key] = parent;
            minHeap->indexes[minHeap->heap[index].key] = index;
            index = parent;
        }
        else
            break;
    }
}

// update heap top-down
void heapify_down(InMinHeap *minHeap, int index)
{
    while (1)
    {
        int smallest = index;
        int leftIndex = 2 * index + 1;
        int rightIndex = 2 * index + 2;

        if (leftIndex < minHeap->size &&
            minHeap->heap[leftIndex].cost < minHeap->heap[smallest].cost)
            smallest = leftIndex;

        if (rightIndex < minHeap->size &&
            minHeap->heap[rightIndex].cost < minHeap->heap[smallest].cost)
            smallest = rightIndex;

        if (smallest != index)
        {
            // Swap the element with the smallest child if necessary
            exchange(&minHeap->heap[index], &minHeap->heap[smallest]);
            minHeap->indexes[minHeap->heap[index].key] = index;
            minHeap->indexes[minHeap->heap[smallest].key] = smallest;
            index = smallest;
        }
        else
            break;
    }
}

void insert_key(InMinHeap *minHeap, int key, int cost)
{
    // Heap is full or key already exists
    if (minHeap->size == minHeap->max || minHeap->indexes[key] != -1)
        return;

    // Add the element to the end of the heap
    int index = minHeap->size;
    minHeap->heap[index].key = key;
    minHeap->heap[index].cost = cost;

    minHeap->indexes[key] = index;
    minHeap->size++;

    heapify_up(minHeap, index);
}

Item *remove_min(InMinHeap *minHeap)
{
    // Allocate memory for the minimum element
    Item *minItem = (Item *)malloc(sizeof(Item));

    if (minHeap->size == 0 || minItem == NULL) // nothing to remove or failed allocation
        return NULL;

    *minItem = minHeap->heap[0];

    // Swap the root with the last element and heapify down
    int last = minHeap->size - 1;
    exchange(&minHeap->heap[0], &minHeap->heap[last]);
    minHeap->indexes[minHeap->heap[0].key] = 0;
    minHeap->indexes[minHeap->heap[last].key] = -1;
    minHeap->size--;

    heapify_down(minHeap, 0);

    return minItem;
}

void update_cost(InMinHeap *minHeap, int key, int new)
{
    int index = minHeap->indexes[key];
    if (index == -1)
        return;

    // Update the cost associated with the key
    int old = minHeap->heap[index].cost;
    minHeap->heap[index].cost = new;

    // Updating the heap based on the new value compared to the prior value
    if (new >= old)
        heapify_down(minHeap, index);
    else
        heapify_up(minHeap, index);
}

int main(void)
{
    char cmd;
    int n, key, cost;
    InMinHeap *heap = NULL;

    while (1)
    {
        scanf(" %c", &cmd);
        getchar();
        if (cmd == 'c')
        {
            scanf(" %d", &n);
            if (heap != NULL)
                free_heap(heap);
            heap = create_indexed_heap(n);
            if (heap == NULL)
            {
                printf("Unable to create a heap.\n");
                return 1;
            }
        }
        else if (cmd == 'i')
        {
            scanf("%d %d ", &key, &cost);
            insert_key(heap, key, cost);
        }
        else if (cmd == 'm')
        {
            Item *item = remove_min(heap);
            if (item != NULL)
                printf("minimo {%d,%d}\n", item->key, item->cost);
            else
                printf("heap vazio\n");
            free(item);
        }
        else if (cmd == 'd')
        {
            scanf("%d %d ", &key, &cost);
            update_cost(heap, key, cost);
        }
        else if (cmd == 't')
        {
            free_heap(heap);
            return 0;
        }
        else
        {
            printf("Invalid command: %c.\n", cmd);
            free_heap(heap);
            return 1;
        }
    }
}