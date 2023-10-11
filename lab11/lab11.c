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
        free(aux);
    }

    // Free the list itself
    free(l);
}

void l_insert(GenericList *l, char t, void *x)
{
    Node *p = l->head;

    if (!p)
    {
        l->head = malloc(sizeof(Node));
        l->head->data = x;
        l->head->type = t;
        l->head->next = NULL;
        return;
    }

    while (p->next)
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
    if (!l->head || i == j)
    {
        return;
    }

    Node *sRev = NULL; // start
    Node *bRev = NULL; // before
    Node *eRev = NULL; // end
    Node *aRev = NULL; // after
    int c = 1;

    Node *curr = l->head;
    Node *prev = NULL;

    while (c <= j && curr != NULL)
    {
        Node *next = curr->next;
        if (c < i)
            bRev = curr;
        else if (c == i)
        {
            sRev = curr;
            eRev = curr;
        }
        else if (c == j)
        {
            eRev = curr;
            aRev = next;
        }
        if (c >= i)
            curr->next = prev;

        prev = curr;
        curr = next;
        c++;
    }

    if (bRev != NULL)
        bRev->next = eRev;
    else
        l->head = eRev;

    sRev->next = aRev;
}

void l_transpose(GenericList *l, int i, int j, int k)
{
    if (!l || !l->head || j < i)
        return;

    Node *p = l->head;
    Node *prevP = NULL;
    Node *q = l->head;

    for (; i > 0; i--)
    {
        prevP = p;
        p = p->next;
    }

    for (; k > 0; k--)
        q = q->next;

    Node *qAux = q->next;
    Node *pAux = q->next;
    q->next = p;

    while (i++ < j)
        p = p->next;

    if (!prevP)
        l->head = p->next;
    else
        prevP->next = p->next;

    p->next = qAux;
}

// Function to print the list
void l_print(GenericList *l)
{
    if (!l || !l->head)
        return;
    Node *curr = l->head;
    while (curr) // iterate rows
    {
        switch (curr->type)
        {
        case 's':
            printf("%s ", (char *)curr->data);
            break;
        case 'd':
            printf("%d ", *(int *)curr->data);
            break;
        case 'f':
            printf("%f ", *(float *)curr->data);
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
    void *x;
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