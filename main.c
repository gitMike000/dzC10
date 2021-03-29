#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // for use boolean type

//Task 1
//==Stack
#define T char

typedef struct Node
{
    T dat;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    int size;
} Stack;

void init(Stack *stack)
{
    stack->head = NULL;
    stack->size = 0;
}

bool push(Stack *stack, T value)
{
    Node *tmp = (Node *)malloc(sizeof(Node));
    if (tmp == NULL)
    {
        printf("Stack overflow\n");
        return false;
    }
    tmp->dat = value;
    tmp->next = stack->head;

    stack->head = tmp;
    stack->size++;
    return true;
}

T pop(Stack *stack)
{
    if (stack->size == 0)
    {
        printf("Stack is empty\n");
        return -1;
    }
    Node *tmp = stack->head;
    T data = stack->head->dat;
    stack->head = stack->head->next;
    stack->size--;
    free(tmp);
    return data;
}

void printNode(Node *n)
{
    if (n == NULL)
    {
        printf("[]");
        return;
    }
    printf("[%c] ", n->dat);
}

void printStack(Stack *stack)
{
    Node *current = stack->head;
    if (current == NULL)
        printNode(current);
    else
    {
        do
        {
            printNode(current);
            current = current->next;
        } while (current != NULL);
    }
    printf(" Size: %d\n", stack->size);
}

//===cycle

typedef struct OneLinkNode
{
    char Sopen;
    char Sclose;
    struct OneLinkNode *next;
} OneLinkNode;

typedef struct
{
    OneLinkNode *head;
    int size;
} OneLinkList;

void initOneLinkList(OneLinkList *lst)
{
    lst->head = NULL;
    lst->size = 0;
}

void insertCyclic(OneLinkList *lst, char SymOpen, char SymClose)
{
    OneLinkNode *new = (OneLinkNode *)malloc(sizeof(OneLinkNode));
    new->Sopen=SymOpen;
    new->Sclose=SymClose;
    new->next = lst->head;

    OneLinkNode *current = lst->head;
    if (current == NULL)
    {
        lst->head = new;
        new->next = lst->head;
        lst->size++;
        return;
    }
    else
    {
        while (current->next != lst->head)
            current = current->next;
        current->next = new;
        lst->size++;
    }
}

OneLinkNode *removeCyclic(OneLinkList *lst, char SymOpen)
{
    OneLinkNode *current = lst->head;
    OneLinkNode *parent = NULL;
    if (current == NULL)
        return NULL;

    while (current->next != lst->head && current->Sopen != SymOpen)
    {
        parent = current;
        current = current->next;
    }
    if (current->Sopen != SymOpen)
        return NULL;
    if (current == lst->head)
    {
        if (current->next == lst->head)
        {
            lst->head = NULL;
            lst->size--;
            return current;
        }
        else
        {
            OneLinkNode *tmp = current;
            while (current->next != lst->head)
                current = current->next;
            lst->head = tmp->next;
            current->next = lst->head;
            lst->size--;
            return tmp;
        }
    }
    parent->next = current->next;
    lst->size--;
    return current;
}

OneLinkNode *readNext(OneLinkList *lst)
{
    OneLinkNode *current = lst->head;
    if (current == NULL)
        return NULL;
    lst->head=current->next;
    return current;
}

void printOneLinkNode(OneLinkNode *n)
{
    if (n == NULL)
    {
        printf("[]");
        return;
    }
    printf("[%c%c] ", n->Sopen,n->Sclose);
}

void printOneLinkList(OneLinkList *lst)
{
    OneLinkNode *current = lst->head;
    if (current == NULL)
        printOneLinkNode(current);
    else
    {
        do
        {
            printOneLinkNode(current);
            current = current->next;
        } while (current != lst->head);
    }
    printf(" Size: %d\n", lst->size);
}

bool ExpressionTrue(char *ex) {
    OneLinkList *SymExp = (OneLinkList *)malloc(sizeof(OneLinkList));
    initOneLinkList(SymExp);
    insertCyclic(SymExp, '(',')');
    insertCyclic(SymExp, '[',']');
    insertCyclic(SymExp, '{','}');

    Stack *st = (Stack *)malloc(sizeof(Stack));
    init(st);

    //printOneLinkList(SymExp);
    //printOneLinkNode(readNext(SymExp));
    //printOneLinkNode(removeCyclic(SymExp, '(')); printf("<- node\n");
    bool exit=true;
    while(*ex!='\n') {
        for (int i=0;i<SymExp->size;i++) {
            OneLinkNode *Cur = readNext(SymExp);
            if (*ex==Cur->Sopen) {
               push(st, Cur->Sclose);
               break;
            }
            if (*ex==Cur->Sclose) {
              if (pop(st)==*ex) {
               break;
              }
              else {
               exit=false;
               break;
              }
            }
        }
        if (exit==false) break;
        *ex++;
    }
    if (st->size>0) exit=false;
    free(st);
    free(SymExp);
    return exit;
}

//Task 2

typedef struct listNode
{
    int dat;
    struct listNode *next;
} listNode;

typedef struct
{
    listNode *head;
    int size;
} List;

void initList(List *lst)
{
    lst->head = NULL;
    lst->size = 0;
}

void insList(List *lst, int data)
{
    listNode *new = (listNode *)malloc(sizeof(listNode));
    new->dat = data;
    new->next = NULL;

    listNode *current = lst->head;
    if (current == NULL)
    {
        lst->head = new;
        lst->size++;
        return;
    }
    else
    {
        while (current->next != NULL)
            current = current->next;
        current->next = new;
        lst->size++;
    }
}

listNode *listrm(List *lst, int data)
{
    listNode *current = lst->head;
    listNode *parent = NULL;
    if (current == NULL)
        return NULL;

    while (current->next != NULL && current->dat != data)
    {
        parent = current;
        current = current->next;
    }
    if (current->dat != data)
        return NULL;
    if (current == lst->head)
    {
        lst->head = current->next;
        lst->size--;
        return current;
    }
    parent->next = current->next;
    lst->size--;
    return current;
}

void listcp(List *fromlst,List *tolst) {
    listNode *current = fromlst->head;
    if (current==NULL) return;
    int len=fromlst->size;
    for (int i=0;i<len;i++)
    {
        insList(tolst,current->dat);
        current=current->next;
    }
}

void printListNode(listNode *n)
{
    if (n == NULL)
    {
        printf("[]");
        return;
    }
    printf("[%d] ", n->dat);
}

void printList(List *lst)
{
    listNode *current = lst->head;
    if (current == NULL)
        printListNode(current);
    else
    {
        do
        {
            printListNode(current);
            current = current->next;
        } while (current != NULL);
    }
    printf(" Size: %d\n", lst->size);
}

//Task 3

bool verif(int a, int b) {
    return (a > b ? true : false);
}

bool isSort(List *lst) {
    bool rez=false;
    listNode *current = lst->head;
    if (current == NULL || current->next == NULL)
        return rez;
    for (int i=0;i<lst->size-1;i++) {
        rez=verif(current->dat , current->next->dat);
        if (!rez) break;
        current=current->next;
    }
    if (rez) return rez;
    current = lst->head;
    for (int i=0;i<lst->size-1;i++) {
        rez=verif(current->next->dat, current->dat);
        if (!rez) break;
        current=current->next;
    }
    return rez;
}

int main(const int arc, const char **argv)
{
    //Task 1
    printf("Task 1\n");
    printf("\n");

    char *ex1="(2+(2*2))\n";
    printf(ex1);
    printf( (ExpressionTrue(ex1)==true ? " is true" : " is false"));
    printf("\n\n");
    char *ex2="{2/{5*(4+7)]\n";
    printf(ex2);
    printf( ExpressionTrue(ex2)==true ? " is true" : " is false");
    printf("\n\n");

    //Task 2
    printf("Task 2\n");

    List *lst1 = (List *)malloc(sizeof(List));
    initList(lst1);
    insList(lst1, 1);
    insList(lst1, 5);
    insList(lst1, 10);
    printf("List lst1:");
    printList(lst1);
    printf("\n");
    //printListNode(listrm(lst1, 1)); printf("<- removed node\n");
    List *lst2 = (List *)malloc(sizeof(List));
    initList(lst2);
    insList(lst2, 20);
    insList(lst2, 30);
    insList(lst2, 40);
    printf("List lst2:");
    printList(lst2);
    printf("\n");
    listcp(lst1,lst2);
    printf("Copy lst1 to lst2:");
    printList(lst2);
    printf("\n");
    listcp(lst2,lst2);
    printf("Copy lst2 to lst2:");
    printList(lst2);
    printf("\n");
    free(lst1);
//    free(lst2);
    printf("\n");

    //Task 3
    printf("Task 3\n");

    printf("List:");
    printList(lst2);
    printf( isSort(lst2) ? "is sorted\n" : "is not sorted\n");
    free(lst2);
    List *lst3 = (List *)malloc(sizeof(List));
    initList(lst3);
    insList(lst3, 90);
    insList(lst3, 80);
    insList(lst3, 70);
    insList(lst3, 60);
    insList(lst3, 50);
    printList(lst3);
    printf( isSort(lst3) ? "is sorted\n" : "is not sorted\n");
    insList(lst3, 90);
    printList(lst3);
    printf( isSort(lst3) ? "is sorted\n" : "is not sorted\n");
    free(lst3);

    return 0;
}
