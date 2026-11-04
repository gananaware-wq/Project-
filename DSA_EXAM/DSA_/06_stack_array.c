/*
Q2. WAP to implement user defined Stack using Array to store integer values.
Create menu driven program providing options to:
    Push()
    Pop()
    Peek()
    Display()
Implement other required functions initStack(), isFull(), isEmpty().
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct STACKARR
{
    int size;
    int tos;
    int *stack;
} STACK;

STACK initStack();
int isFull(STACK *s);
int isEmpty(STACK *s);
void Push(STACK *s, int value);
void Pop(STACK *s);
void Peek(STACK *s);
void Display(STACK *s);

int main()
{
    int choice, value;
    STACK s;

    s = initStack();

    if(s.stack == NULL)
    {
        return 1;
    }

    do
    {
        printf("\n----------- STACK MENU -----------\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                Push(&s, value);
                break;

            case 2:
                Pop(&s);
                break;

            case 3:
                Peek(&s);
                break;

            case 4:
                Display(&s);
                break;

            case 5:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
                break;
        }

    } while(choice != 5);

    free(s.stack);
    return 0;
}

STACK initStack()
{
    STACK s;

    s.size = 0;
    s.tos = -1;
    s.stack = NULL;

    printf("Enter size of stack: ");
    scanf("%d", &s.size);

    while(s.size <= 0)
    {
        printf("Invalid size. Enter size again: ");
        scanf("%d", &s.size);
    }

    s.stack = (int *)calloc(s.size, sizeof(int));

    if(s.stack == NULL)
    {
        printf("Memory allocation failed!\n");
    }
    else
    {
        printf("Stack initialized successfully.\n");
    }

    return s;
}

int isFull(STACK *s)
{
    if(s->tos == s->size - 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isEmpty(STACK *s)
{
    if(s->tos == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Push(STACK *s, int value)
{
    if(isFull(s))
    {
        printf("Stack is Full!\n");
    }
    else
    {
        s->tos++;
        s->stack[s->tos] = value;
        printf("%d pushed into stack.\n", value);
    }
}

void Pop(STACK *s)
{
    int value;

    if(isEmpty(s))
    {
        printf("Stack is Empty!\n");
    }
    else
    {
        value = s->stack[s->tos];
        s->tos--;
        printf("Popped element: %d\n", value);
    }
}

void Peek(STACK *s)
{
    if(isEmpty(s))
    {
        printf("Stack is Empty!\n");
    }
    else
    {
        printf("Top element: %d\n", s->stack[s->tos]);
    }
}

void Display(STACK *s)
{
    int i;

    if(isEmpty(s))
    {
        printf("Stack is Empty!\n");
    }
    else
    {
        printf("Stack elements (Top to Bottom):\n");

        for(i = s->tos; i >= 0; i--)
        {
            printf("%d\n", s->stack[i]);
        }
    }
}
