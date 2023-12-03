#include <stdlib.h>
#include <stdio.h>

struct Node
{
    int dest;
    struct Node *next;
};

typedef struct Node Node;

typedef struct
{
    Node *head;
} List;

typedef struct
{
    int n;
    List *vertices;
} Graph;

// Add an oriented edge
void addEdge(Graph *graph, int start, int end)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->dest = end;
    newNode->next = graph->vertices[start].head;
    graph->vertices[start].head = newNode;
}

// Function to create a graph
Graph *createGraph(int nVertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->n = nVertices;

    graph->vertices = (List *)malloc(nVertices * sizeof(List));

    for (int i = 0; i < nVertices; ++i)
        graph->vertices[i].head = NULL;

    return graph;
}

// A recursive function to check if there is a path between 'v1' and 'v2'
short pathExistsUtil(Graph *graph, int v1, int v2, short visited[], int path[], int index)
{
    // Mark the current node as visited and store it in path[]
    visited[v1] = 1;
    path[index] = v1;
    ++index;

    // If the current vertex is the same as v2, a path is found
    if (v1 == v2)
    {
        return 1;
    }
    else
    {
        // If the current vertex is not v2, recur for all vertices adjacent to this vertex
        Node *p = graph->vertices[v1].head;
        while (p)
        {
            if (!visited[p->dest])
            {
                // Recursively check for a path
                if (pathExistsUtil(graph, p->dest, v2, visited, path, index))
                    return 1; // Return 1 if a path is found
            }
            p = p->next;
        }
    }

    // Remove the current vertex from path[] and mark it as unvisited
    --index;
    visited[v1] = 0;

    // No path found through this vertex, return 0
    return 0;
}

// Wrapper function to check if there is a path between 'v1' and 'v2'
short pathExists(Graph *graph, int v1, int v2)
{
    if (v1 == v2)
        return 0;
    // Initialize an array to keep track of visited vertices
    short *visited = (short *)malloc(graph->n * sizeof(short));
    for (int i = 0; i < graph->n; i++)
        visited[i] = 0;

    // Initialize an array to store the current path
    int *path = (int *)malloc(graph->n * sizeof(int));
    int index = 0;

    // Call the utility function
    short result = pathExistsUtil(graph, v1, v2, visited, path, index);

    // Free the allocated memory
    free(visited);
    free(path);

    return result;
}
// Function to free the memory allocated for the graph
void freeGraph(Graph *graph)
{
    for (int i = 0; i < graph->n; ++i)
    {
        Node *p = graph->vertices[i].head;
        while (p)
        {
            Node *aux = p;
            p = p->next;
            free(aux);
        }
    }
    free(graph->vertices);
    free(graph);
}

void printAdjacencyList(Graph *graph)
{
    for (int i = 0; i < graph->n; ++i)
    {
        printf("Adjacency list for vertex %d: ", i);

        Node *current = graph->vertices[i].head;
        while (current != NULL)
        {
            printf("%d", current->dest);
            if (current->next != NULL)
            {
                printf(" -> ");
            }
            current = current->next;
        }

        printf("\n");
    }
}

int main(void)
{
    int taskCount, taskSequences, n, m;

    // Read the number of tasks
    scanf("tarefas: %d ", &taskCount);
    scanf("precedencias: %d ", &taskSequences);

    Graph *graph = createGraph(taskCount);

    // Read the task sequences
    for (int i = 0; i < taskSequences; i++)
    {
        scanf("%d %d", &n, &m);
        addEdge(graph, n, m);
    }

    printAdjacencyList(graph);

    for (int j = 0; j < graph->n; j++)
    {
        short printed = 0;
        for (int k = graph->n - 1; k >= j; k--)
        {
            if (!pathExists(graph, j, k))
            {
                if (k == j && !printed)
                    printf("%d\n", j);
                else if (k != j)
                {
                    printed = 1;
                    printf("%d %d\n", j, k);
                }
            }
        }
    }
    freeGraph(graph);

    return 0;
}