#include <stdlib.h>
#include <stdio.h>

// Define the Cell structure for a matrix element
struct Cell
{
    int column;
    int value;
    struct Cell *next;
};

// Define the Line structure for a row in the matrix
typedef struct Cell Cell;

struct Line
{
    int row;
    Cell *first;
    struct Line *next;
};

typedef struct Line Line;

// Define the Matrix structure that contains the head of the lines
struct Matrix
{
    Line *head;
};

typedef struct Matrix Matrix;

// Function to free memory allocated for the matrix
void m_free(Matrix *m)
{
    Line *curr = m->head;
    Line *aux_line;
    Cell *curr_cell;
    Cell *aux_cell;

    while (curr)
    {
        curr_cell = curr->first;
        while (curr_cell)
        {
            aux_cell = curr_cell;
            curr_cell = curr_cell->next;
            free(aux_cell);
        }

        aux_line = curr;
        curr = curr->next;
        free(aux_line);
    }

    // Free the matrix itself
    free(m);
}

// Function to set a value in the matrix
void m_set(Matrix *m, int i, int j, int x)
{
    Line *p = m->head;
    Line *prev = NULL;

    // Find the appropriate row to keep order (Line)
    while (p && p->row < i)
    {
        prev = p;
        p = p->next;
    }

    if (!p || p->row != i)
    {
        // Create a new Line if it doesn't exist
        Line *nl = malloc(sizeof(Line));
        if (!nl)
            return; // Memory allocation failed
        nl->row = i;
        nl->first = NULL;
        nl->next = p;

        if (prev)
            prev->next = nl;
        else
            m->head = nl;
        p = nl;
    }

    Cell *c = p->first;
    Cell *prev_c = NULL;

    // Find the appropriate column to keep order(Cell)
    while (c && c->column < j)
    {
        prev_c = c;
        c = c->next;
    }

    if (c && c->column == j)
        if (x == 0) // value removal
        {
            if (prev_c) // there is a cell before
                prev_c->next = c->next;
            else // is the first cell in row or row is empty
            {
                p->first = c->next;
                if (!p->first) // if the row is empty we alter the rows
                {
                    if (prev)
                        prev->next = p->next;
                    else
                        m->head = p->next;
                    free(p);
                }
            }
            free(c);
            return;
        }
        else
            c->value = x; // cell alteration
    else if (x != 0)
    {
        // Create a new Cell if it doesn't exist and x is not 0(is an addition)
        Cell *nc = malloc(sizeof(Cell));
        if (!nc)
            return; // Memory allocation failed
        nc->column = j;
        nc->value = x;
        nc->next = c;

        if (prev_c)
            prev_c->next = nc;
        else
            p->first = nc;
    }
}

// Function to retrieve a value from the matrix
int m_retrieve(Matrix *m, int i, int j)
{
    if (!m || !m->head)
        return 0; // Indicate failure

    Line *p = m->head;
    while (p && p->row < i)
        p = p->next;

    if (!p || p->row != i)
        return 0; // Indicate failure

    Cell *c = p->first;

    while (c && c->column < j)
        c = c->next;

    if (!c || c->column != j)
        return 0; // Indicate failure

    return c->value;
}

// Function to print the matrix
int m_print(Matrix *m)
{
    if (!m || !m->head)
        return 0;
    printf("M: ");
    Line *curr = m->head;
    Cell *curr_cell = curr->first;
    while (curr) // iterate rows
    {
        curr_cell = curr->first;
        while (curr_cell) // iterate columns(cells in row)
        {
            printf("(%d,%d,%d) ", curr->row, curr_cell->column, curr_cell->value);
            curr_cell = curr_cell->next;
        }
        curr = curr->next;
    }
    return 1;
}

int main(void)
{
    char cmd;
    int i, j, x;
    Matrix *m = NULL;

    while (1)
    {
        scanf("%c ", &cmd);

        if (cmd == 'c')
        {
            if (m != NULL)
                m_free(m);
            m = malloc(sizeof(Matrix));
            if (m == NULL)
            {
                printf("Unable to create a matrix.\n");
                return 1;
            }
            m->head = NULL;
        }
        else if (cmd == 'a')
        {
            scanf("[%d,%d] %d ", &i, &j, &x);
            m_set(m, i, j, x);
        }
        else if (cmd == 'r')
        {
            scanf("[%d,%d] ", &i, &j);
            printf("M[%d][%d] == %d\n", i, j, m_retrieve(m, i, j));
        }
        else if (cmd == 'p')
        {
            if (m_print(m) == 0)
                printf("A matriz e' nula.\n");
            else
                printf("\n");
        }
        else if (cmd == 't')
        {
            m_free(m);
            return 0;
        }
        else
        {
            printf("Invalid command: %c.\n", cmd);
            m_free(m);
            return 1;
        }
    }
}