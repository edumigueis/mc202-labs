#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

struct Cell
{
    int column;
    int value;
    struct Cell *next;
};

typedef struct Cell Cell;

struct Line
{
    int row;
    Cell *first;
    struct Line *next;
};

typedef struct Line Line;

struct Matrix
{
    Line *head;
};

typedef struct Matrix Matrix;

void m_free(Matrix *m)
{
    Line *curr = m->head;
    while (curr)
    {
        Cell *curr_cell = curr->first;
        while (curr_cell)
        {
            Cell *aux = curr_cell;
            curr_cell = curr_cell->next;
            free(aux);
        }

        Line *aux = curr;
        curr = curr->next;
        free(aux);
    }

    // Free the matrix itself
    free(m);
}

void m_set(Matrix *m, int i, int j, int x)
{
    Line *p = m->head;
    Line *prev = NULL;

    while (p && p->row < i)
    {
        prev = p;
        p = p->next;
    }

    if (!p || p->row != i)
    {
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

    while (c && c->column < j)
    {
        prev_c = c;
        c = c->next;
    }

    if (c && c->column == j)
        c->value = x;
    else
    {
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

int m_remove(Matrix *m, int i, int j)
{
    if (!m || !m->head)
        return 0; // Indicate failure

    Line *p = m->head;
    while (p && p->row < i)
        p = p->next;

    if (!p || p->row != i)
        return 0; // Indicate failure

    Cell *curr = p->first;
    Cell *prev = NULL;

    while (curr && curr->column != j)
    {
        prev = curr;
        curr = curr->next;
    }

    if (!curr || curr->column != j)
        return 0; // Indicate failure

    int ret = curr->value;

    if (prev)
        prev->next = curr->next;
    else
        p->first = curr->next;

    free(curr);

    return ret;
}

int m_print(Matrix *m)
{
    if (!m)
        return 0;
    printf("M:");
    Line *curr = m->head;
    while (curr)
    {
        Cell *curr_cell = curr->first;
        while (curr_cell)
        {
            printf(" (%d,%d,%d)", curr->row, curr_cell->column, curr_cell->value);
            curr_cell = curr_cell->next;
        }
        curr = curr->next;
    }
    return 1;
}

int main(void)
{
    char cmd;
    int i, j;
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
                return errno ? errno : 1;
            }
            m->head = NULL;
        }
        else if (cmd == 'a')
        {
            int x;
            scanf("[%d,%d] %d ", &i, &j, &x);
            m_set(m, i, j, x);
        }

        else if (cmd == 'r')
        {
            scanf("[%d,%d] ", &i, &j);
            printf("M[%d][%d] == %d\n", i, j, m_remove(m, i, j));
        }

        else if (cmd == 'p')
        {
            int res = m_print(m);
            if (res == 0)
                printf("A matriz e' nula.");
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