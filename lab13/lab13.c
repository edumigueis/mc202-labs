#include <stdlib.h>
#include <stdio.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct
{
    int **matrix;
    int vertices;
} AdjacencyMatrix;

// Function to create a graph with the given number of vertices
AdjacencyMatrix *create_graph(AdjacencyMatrix *adjMatrix, int vertices)
{
    adjMatrix = (AdjacencyMatrix *)malloc(sizeof(AdjacencyMatrix));
    adjMatrix->vertices = vertices;

    adjMatrix->matrix = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++)
    {
        adjMatrix->matrix[i] = (int *)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++)
        {
            adjMatrix->matrix[i][j] = 0; // Initialize to 0 (no edge)
        }
    }

    return adjMatrix;
}

// Function to free the memory
void free_graph(AdjacencyMatrix *adjMatrix)
{
    for (int i = 0; i < adjMatrix->vertices; i++)
        free(adjMatrix->matrix[i]);
    free(adjMatrix->matrix);
    free(adjMatrix);
}

// Depth-First Search (DFS) function for finding critical nodes
void dfs(int u, int discovery_time[],
         int low[], int is_critical[], int time,
         const AdjacencyMatrix *adjMatrix, int parent)
{
    discovery_time[u] = low[u] = ++time;
    int children = 0;

    for (int v = 0; v < adjMatrix->vertices; v++)
    {
        if (adjMatrix->matrix[u][v])
        {
            if (!discovery_time[v])
            {
                children++;
                dfs(v, discovery_time, low, is_critical, time, adjMatrix, u);
                low[u] = MIN(low[u], low[v]);

                if (low[v] >= discovery_time[u] && parent != -1)
                    is_critical[u] = 1;
            }
            else if (v != parent)
                low[u] = MIN(low[u], discovery_time[v]);
        }
    }

    if (parent == -1 && children > 1)
        is_critical[u] = 1;
}

// Function to count the number of critical nodes in the graph
int count_crits(const AdjacencyMatrix *adjMatrix)
{
    int *discovery_time = (int *)calloc(adjMatrix->vertices, sizeof(int));
    int *low = (int *)calloc(adjMatrix->vertices, sizeof(int));
    int *is_critical = (int *)calloc(adjMatrix->vertices, sizeof(int));

    int time = 0;

    for (int i = 0; i < adjMatrix->vertices; i++)
        if (!discovery_time[i])
            dfs(i, discovery_time, low, is_critical, time, adjMatrix, -1);

    int count = 0;
    for (int i = 0; i < adjMatrix->vertices; i++)
        if (is_critical[i])
            count++;

    free(discovery_time);
    free(low);
    free(is_critical);

    return count;
}

int main(void)
{
    AdjacencyMatrix *graph = NULL;
    int n, read;
    while (1)
    {
        // Ler o número de PDVs
        scanf("%d ", &n);
        if (n == 0)
            break;
        if (graph != NULL)
            free_graph(graph);
        graph = create_graph(graph, n);

    readline:
        scanf("%d", &read);
        int origin = read - 1;
        while (read != 0)
        {
            if (scanf("%d", &read) != 1)
                return 1;
            graph->matrix[origin][read - 1] = 1;
            graph->matrix[read - 1][origin] = 1;
            if (getchar() == '\n')
                goto readline;
        }
        count_crits(graph);
        printf("%d\n", count_crits(graph));
    }
    free_graph(graph);
    return 0;
}