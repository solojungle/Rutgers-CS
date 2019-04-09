#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _node
{
    char *string;
    struct _node *next;
} Node;

/*
*   Forward Declarations.
**/
void inputTokenizer(Node **node, char *array);
void push(Node **, char *);
void printlist(Node *);
char *createString(int, int, char *);
Node *addToFront(Node *, char *);
void mergeSort(Node **);
void split(Node *, Node **, Node **);
Node *merge(Node *, Node *);
int stringcompare(const char *, const char *);

int main(int argc, char **argv)
{
    /*
    *   Checks to see if correct number of arguments are supplied to the program.
    *   @returns:
    *       True: when argc is equal to 1.
    *       False: when for-all argc: less than or equal to 0, greater than or equal to 2.
    **/
    if (argc == 1)
    {
        fprintf(stderr, "ERROR: You must enter an string.\n");
        return 1;
    }
    else if (argc > 2)
    {
        fprintf(stderr, "ERROR: You may only enter ONE string.\n");
        return 1;
    }

    Node *head = NULL;
    inputTokenizer(&head, argv[1]);
    mergeSort(&head);
    printlist(head);
    // Is pointing to a malloc'd place in memory, must free
    free(head);
    return 0;
}

/*
*   @params: 
*       Node ** head: beginning of linked-list (This convention allows reassigning NULL pointer).
*       char * source: from argv[1].
*   @returns: Void: creates and populates data-structure with tokens.
**/
void inputTokenizer(Node **head, char *source)
{
    int i = 0;
    int length = 0;
    int lastDelim = 0;
    char *test;
    while (source[i])
    {
        if (isalpha(source[i]))
        {
            length += 1;
        }
        else
        {
            if (length > 0)
            {
                push(head, createString(length, lastDelim, source));
            }
            else if (source[i] == '\\')
            {
                i += 2;
            }
            length = 0;
            lastDelim = i;
        }
        i += 1;
    }
    if (length > 0)
    {
        push(head, createString(length, lastDelim, source));
    }
    return;
}

/*
*   @params: 
*       int length: length of the word.
*       int lastDelim: last instance of a delimiter (N+1 is where word begins).
*       char * source: the input string pointer.
*   @returns: String: memcpys characters from input into malloc'd memory.
**/
char *createString(int length, int lastDelim, char *source)
{
    char *string = (char *)malloc(length * sizeof(char *) + 1);
    if (string == NULL)
    {
        fprintf(stderr, "ERROR: CreateString has failed memory allocation.\n");
        exit(1);
    }
    if (isalpha(source[lastDelim]))
    {
        memcpy(string, source + lastDelim, length);
    }
    else
    {
        memcpy(string, source + lastDelim + 1, length);
    }
    string[length] = '\0';
    return string;
}

/*
*   @params: 
*       Node ** previous: prev. node to point too with new node (Extends convention to change NULL pointer).
*       char * str: the input string pointer.
*   @returns: Void: pushes new string node to beginning of list (new -> old).
**/
void push(Node **previous, char *str)
{
    Node *new = (Node *)malloc(sizeof(Node));
    if (new == NULL)
    {
        fprintf(stderr, "ERROR: Push has failed memory allocation.\n");
        exit(1);
    }
    new->string = str;
    new->next = *previous;
    *previous = new;
    return;
}

/*
*   @params: 
*       Node * head: beginning of linked list.
*   @returns: Void: prints out all the strings from the linked list.
**/
void printlist(Node *head)
{
    if (head == NULL)
    {
        fprintf(stderr, "WARNING: Empty string returned.\n");
    }
    Node *node = head;
    while (node)
    {
        printf("%s\n", node->string);
        node = node->next;
    }
}

/*
*   @params: 
*       Node * front: pointer to first node.
*       Node * back: pointer to middle node.
*   @returns: Void: merges two split linked list sections into one.
*   @comments: This recursive function merges two nodes/lists into one.
**/
Node *merge(Node *front, Node *back)
{
    if (front == NULL)
    {
        return back;
    }
    else if (back == NULL)
    {
        return front;
    }

    Node *result = NULL;
    // Sorting occurs here: pick either front or back, and recursively call
    if (stringcompare(front->string, back->string) == 1)
    {
        result = front;
        result->next = merge(front->next, back);
    }
    else
    {
        result = back;
        result->next = merge(front, back->next);
    }
    return result;
}

/*
*   @params: 
*       Node * source: beginning of linked list.
*       Node ** front: pointer to first half of linked list.
*       Node ** back: pointer to second half of linked list.
*   @returns: Void: splits linked list into two sections.
*   @comments: This function works by having a slow moving pointer and a fast
*           moving pointer, the fast moving pointer increments by two, while the slow
*           increments by one. When the fast pointer reaches the end of the linked-list
*           it can be assumed that the slow pointer is right before the middle of list
*           so we reset the fast pointer to the beginning of the list, increment the slow,
*           pointer and then partition the list into a front and back.
**/
void split(Node *source, Node **front, Node **back)
{
    // If zero nodes or only one node exists
    if (source == NULL || source->next == NULL)
    {
        *front = source;
        *back = NULL;
        return;
    }
    Node *slow = source;
    Node *fast = source->next;
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

/*
*   @params: 
*       Node * head: beginning of linked list.
*   @returns: Void: applies mergesort to a linked-list.
**/
void mergeSort(Node **head)
{
    // If zero nodes or only one node exists
    if (*head == NULL || (*head)->next == NULL)
    {
        return;
    }
    Node *front;
    Node *back;
    split(*head, &front, &back);
    mergeSort(&front);
    mergeSort(&back);
    *head = merge(front, back);
}

/*
*   Modified strcmp(), reverse lexicographic order, with uppercase ASCII being the opposite as well.
*   Iterative version
**/
int stringcompare(const char *s1, const char *s2)
{
    int i = 0;
    while (s1[i] && s2[i])
    {
        if (isupper(s1[i]) && isupper(s2[i]))
        {
        }
        // s1 < s2
        else if (isupper(s2[i]))
        {
            return -1;
        }
        // s1 > s2
        else if (isupper(s1[i]))
        {
            return 1;
        }

        // ASCII characters are weighted in reverse numerically
        if (s1[i] < s2[i])
        {
            return -1;
        }
        else if (s1[i] > s2[i])
        {
            return 1;
        }
        i += 1;
    }
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    return (l1 == l2) ? 0 : (l1 > l2) ? 1 : -1;
}