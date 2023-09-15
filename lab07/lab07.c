#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10000                          // maximum group size
#define INIT_ARRAY_DR 1, -1, 0, 0, 1, -1, -1, 1 // row variation
#define INIT_ARRAY_DC 0, 0, 1, -1, 1, -1, 1, -1 // column variation

#define IS_VALID(x, y, rows, cols) ((x) >= 0 && (x) < (rows) && (y) >= 0 && (y) < (cols))
// verifies if positions are within matrix bounds

typedef struct
{
    short x;
    short y;
} Coord;

// basic method for allocating memory only
char **allocateMatrix(int m, int n)
{
    char **mat = (char **)malloc(m * sizeof(char *));
    if (mat == NULL)
    {
        perror("Memory allocation failed");
        exit(1);
    }

    for (int i = 0; i < m; i++)
    {
        mat[i] = (char *)malloc(n * sizeof(char));
        if (mat[i] == NULL)
        {
            perror("Memory allocation failed");
            exit(1);
        }
    }

    return mat;
}

// basic method for freeing memory only
void freeMatrix(char **mat, int m)
{
    for (int i = 0; i < m; i++)
    {
        free(mat[i]);
    }
    free(mat);
}

// starts from one position and removes that entire group from the matrix
void clearGroup(char **mat, Coord start, int rows, int cols)
{
    // stack for the main logic(max sized)
    Coord *inp_array = (Coord *)malloc(MAX_SIZE * sizeof(Coord));

    // arrays off possible adjacent positions
    int dr[] = {INIT_ARRAY_DR};
    int dc[] = {INIT_ARRAY_DC};

    int top = 0;

    inp_array[top].x = start.x;
    inp_array[top].y = start.y;

    // while stack is not exausted
    while (top >= 0)
    {
        int x = inp_array[top].x;
        int y = inp_array[top].y;
        mat[x][y] = '*'; // clear pos
        top--;           // removes from stack(logic only)

        for (int i = 0; i < 8; i++)
        {
            int newX = x + dr[i];
            int newY = y + dc[i];

            // if next pos is in group than add to stack processing in further iterations the same way
            if (IS_VALID(newX, newY, rows, cols) && mat[newX][newY] == '@')
            {
                top++;
                inp_array[top].x = newX;
                inp_array[top].y = newY;
            }
        }
    }
    free(inp_array);
}

// finds @s while constantly updating matrix(clearGroup) for every @ it finds
int findGroups(char **mat, int m, int n)
{
    int count = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] == '@') // group seed
            {
                clearGroup(mat, (Coord){i, j}, m, n);
                count++;
            }
        }
    }
    return count;
}

int main()
{
    int m, n;

    while (scanf("%d %d", &m, &n) == 2)
    {
        if (m == 0)
            break; // Terminate the loop when m becomes 0

        char **mat = allocateMatrix(m, n);

        for (int i = 0; i < m; i++)
        {
            char line[n + 1]; // +1 for the null terminator
            scanf("%s", line);
            for (int j = 0; j < n; j++)
            {
                mat[i][j] = line[j];
            }
        }

        int groups = findGroups(mat, m, n); // retreive count from main method
        printf("%d\n", groups);

        freeMatrix(mat, m);
    }

    return 0;
}