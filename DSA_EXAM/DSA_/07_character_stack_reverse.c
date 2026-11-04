/*
Q3. WAP to create a stack of characters in order to store alphabets A-Z.
And print them in reverse order.
*/

#include <stdio.h>

#define SIZE 26

typedef struct STACK
{
    int tos;
    char stack[SIZE];
} STACK;

void initStack(STACK *s);
int isFull(STACK *s);
int isEmpty(STACK *s);
void Push(STACK *s, char value);
char Pop(STACK *s);

int main()
{
    int i;
    STACK s;

    initStack(&s);

    for(i = 0; i < SIZE; i++)
    {
        Push(&s, 'A' + i);
    }

    printf("\nAlphabets in reverse order:\n");

    while(!isEmpty(&s))
    {
        printf("%c ", Pop(&s));
    }

    printf("\n");

    return 0;
}

void initStack(STACK *s)
{
    s->tos = -1;
}

int isFull(STACK *s)
{
    if(s->tos == SIZE - 1)
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

void Push(STACK *s, char value)
{
    if(isFull(s))
    {
        printf("Stack is Full!\n");
    }
    else
    {
        s->tos++;
        s->stack[s->tos] = value;
    }
}

char Pop(STACK *s)
{
    char value;

    if(isEmpty(s))
    {
        printf("Stack is Empty!\n");
        return '\0';
    }
    else
    {
        value = s->stack[s->tos];
        s->tos--;
        return value;
    }
}
