#include <stdlib.h>
#include <stdio.h>

struct Node
{
    void *data;
    char type;
    struct Node *next;
};

typedef struct Node Node;

// Define the GenericList structure that contains the head of the list
struct GenericList
{
    Node *head;
};

typedef struct GenericList GenericList;

// Function to free memory allocated for the list
void l_free(GenericList *l)
{
    Node *curr = l->head;
    Node *aux;

    while (curr)
    {
        aux = curr;
        curr = curr->next;
        free(aux->data);
        free(aux);
    }

    // Free the list itself
    free(l);
}

void l_insert(GenericList *l, char t, void *x)
{
    if (x == NULL)
        return;

    Node *p = l->head;

    if (!p) // special case: empty list
    {
        l->head = malloc(sizeof(Node));
        l->head->data = x;
        l->head->type = t;
        l->head->next = NULL;
        return;
    }

    while (p->next) // iterato to insertion point
        p = p->next;

    Node *newNode = malloc(sizeof(Node));
    if (!newNode)
        return;
    newNode->data = x;
    newNode->type = t;
    newNode->next = NULL;

    p->next = newNode;
}

void l_reverse(GenericList *l, int i, int j)
{
    if (!l || !l->head || i >= j)
        return;

    Node *start = NULL;
    Node *end = NULL; // start and end nodes of reversal
    int c = 0;        // counter

    Node *curr = l->head; // current node
    Node *prev = NULL;    // previous node on iteration
    Node *before = NULL;  // node before the reversal interval
    Node *after = NULL;   // node after the reversal interval

    while (c <= j && curr != NULL) // reverse range or until list ends
    {
        Node *next = curr->next;
        if (c < i)
            before = curr;
        else if (c == i)
        {
            start = curr;
            end = curr;
        }
        else if (c == j)
        {
            end = curr;
            after = next;
        }
        if (c >= i)
            curr->next = prev;

        prev = curr;
        curr = next;
        c++;
    }

    if (before != NULL)
        before->next = end;
    else
        l->head = end;

    start->next = after;
}

void l_transpose(GenericList *l, int i, int j, int k)
{
    if (!l || !l->head || j < i || (k > i && k < j) || k == i - 1)
        // empty list or ivalid range or nothing to be done
        return;

    Node *p = l->head;
    Node *prevP = NULL;
    Node *q = l->head;

    for (int count = i; count > 0; count--) // point to start transposal
    {
        prevP = p;
        p = p->next;
    }

    for (; k > 0; k--) // point to insert
        q = q->next;

    Node *qAux = q;
    Node *pAux = p;

    if (k >= 0) // -1 is a especial case since there is nothing before root
    {
        qAux = q->next;
        q->next = p;
    }

    while (i++ < j) // from start to end of range
        p = p->next;

    if (!prevP)
        l->head = p->next;
    else
        prevP->next = p->next;

    p->next = qAux;
    if (k == -1)
        l->head = pAux;
}

// Function to print the list
void l_print(GenericList *l)
{
    if (!l || !l->head)
        return;
    Node *curr = l->head;
    while (curr) // iterate rows
    {
        switch (curr->type) // each type has a different scanf
        {
            case 's':
                printf("%s ", (char *)curr->data);
                break;
            case 'd':
                printf("%d ", *(int *)curr->data);
                break;
            case 'f':
                printf("%.4f ", *(float *)curr->data);
                break;
            case 'c':
                printf("%c ", *(int *)curr->data);
                break;
        }
        curr = curr->next;
    }
    printf("\n");
}

int main(void)
{
    char cmd, t;
    int i, j, k;
    void *x = NULL;
    GenericList *l = NULL;

    while (1)
    {
        scanf(" %c", &cmd);

        if (cmd == 'c')
        {
            if (l != NULL)
                l_free(l);
            l = malloc(sizeof(GenericList));
            if (l == NULL)
            {
                printf("Unable to create a generic list.\n");
                return 1;
            }
            l->head = NULL;
        }
        else if (cmd == 'i')
        {
            scanf(" %c", &t);

            switch (t)
            {
                case 's':
                    x = malloc(sizeof(char) * 127); // Allocate memory for string
                    scanf(" %s", (char *)x);
                    break;
                case 'd':
                    x = malloc(sizeof(int));
                    scanf(" %d", (int *)x);
                    break;
                case 'f':
                    x = malloc(sizeof(float));
                    scanf(" %f", (float *)x);
                    break;
                case 'c':
                    x = malloc(sizeof(char));
                    scanf(" %c", (char *)x);
                    break;
            }

            l_insert(l, t, x);
        }
        else if (cmd == 'r')
        {
            scanf("%d %d ", &i, &j);
            l_reverse(l, i, j);
        }
        else if (cmd == 't')
        {
            scanf("%d %d %d ", &i, &j, &k);
            l_transpose(l, i, j, k);
        }
        else if (cmd == 'p')
            l_print(l);
        else if (cmd == 'f')
        {
            l_free(l);
            return 0;
        }
        else
        {
            printf("Invalid command: %c.\n", cmd);
            l_free(l);
            return 1;
        }
    }
}