/*
    Question 3: Stack Using Dynamic Array
    Marks: 10

    Operations:
    1. Initialize stack at runtime
    2. Push an element
    3. Pop an element
    4. Peek the top element
    5. Display stack elements
    6. Find minimum and maximum elements
    7. Count even and odd elements

    Tricky point:
    tos (top of stack) stores the index of the current top element.
    Initially tos = -1, which means the stack is empty.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct STACKARR
{
    int size;
    int tos;
    int *stack;
} STACKARR;

int init_stack(STACKARR *s, int size)
{
    if (size <= 0)
    {
        printf("Stack size must be greater than zero.\n");
        return 0;
    }

    s->stack = (int *)malloc(size * sizeof(int));

    if (s->stack == NULL)
    {
        printf("Memory allocation failed.\n");
        return 0;
    }

    s->size = size;
    s->tos = -1;

    return 1;
}

int is_empty(STACKARR *s)
{
    return (s->tos == -1);
}

int is_full(STACKARR *s)
{
    return (s->tos == s->size - 1);
}

void push(STACKARR *s, int value)
{
    if (is_full(s))
    {
        printf("Stack overflow. Cannot push element.\n");
        return;
    }

    /*
       First increase tos, then store the new value at that index.
       This keeps tos pointing to the actual top element.
    */
    s->tos++;
    s->stack[s->tos] = value;

    printf("%d pushed into stack.\n", value);
}

void pop(STACKARR *s)
{
    int value;

    if (is_empty(s))
    {
        printf("Stack underflow. Stack is empty.\n");
        return;
    }

    value = s->stack[s->tos];

    /*
       Decreasing tos removes the top element logically.
       No shifting of remaining array elements is required.
    */
    s->tos--;

    printf("Popped element = %d\n", value);
}

void peek(STACKARR *s)
{
    if (is_empty(s))
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("Top element = %d\n", s->stack[s->tos]);
}

void display(STACKARR *s)
{
    int i;

    if (is_empty(s))
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack elements (top to bottom):\n");

    for (i = s->tos; i >= 0; i--)
    {
        printf("%d\n", s->stack[i]);
    }
}

void findMinMax(STACKARR *s)
{
    int i;
    int min;
    int max;

    if (is_empty(s))
    {
        printf("Stack is empty.\n");
        return;
    }

    min = s->stack[0];
    max = s->stack[0];

    /*
       Start from index 1 because index 0 is already used
       to initialize both min and max.
    */
    for (i = 1; i <= s->tos; i++)
    {
        if (s->stack[i] < min)
            min = s->stack[i];

        if (s->stack[i] > max)
            max = s->stack[i];
    }

    printf("Minimum element = %d\n", min);
    printf("Maximum element = %d\n", max);
}

void countEvenOdd(STACKARR *s)
{
    int i;
    int even = 0;
    int odd = 0;

    if (is_empty(s))
    {
        printf("Stack is empty.\n");
        return;
    }

    for (i = 0; i <= s->tos; i++)
    {
        if (s->stack[i] % 2 == 0)
            even++;
        else
            odd++;
    }

    printf("Even elements = %d\n", even);
    printf("Odd elements = %d\n", odd);
}

void free_stack(STACKARR *s)
{
    free(s->stack);
    s->stack = NULL;
    s->size = 0;
    s->tos = -1;
}

int main(void)
{
    STACKARR s;
    int choice;
    int size;
    int value;
    int initialized = 0;

    s.stack = NULL;
    s.size = 0;
    s.tos = -1;

    do
    {
        printf("\n----- STACK USING ARRAY -----\n");
        printf("1. Initialize Stack\n");
        printf("2. Push\n");
        printf("3. Pop\n");
        printf("4. Peek\n");
        printf("5. Display\n");
        printf("6. Find Minimum and Maximum\n");
        printf("7. Count Even and Odd Elements\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            if (initialized)
                free_stack(&s);
            return 1;
        }

        switch (choice)
        {
            case 1:
                if (initialized)
                {
                    printf("Stack is already initialized.\n");
                    break;
                }

                printf("Enter stack size: ");

                if (scanf("%d", &size) != 1)
                {
                    printf("Invalid input.\n");
                    return 1;
                }

                initialized = init_stack(&s, size);

                if (initialized)
                    printf("Stack initialized successfully.\n");

                break;

            case 2:
                if (!initialized)
                {
                    printf("Initialize stack first.\n");
                    break;
                }

                printf("Enter value: ");

                if (scanf("%d", &value) != 1)
                {
                    printf("Invalid input.\n");
                    free_stack(&s);
                    return 1;
                }

                push(&s, value);
                break;

            case 3:
                if (initialized)
                    pop(&s);
                else
                    printf("Initialize stack first.\n");
                break;

            case 4:
                if (initialized)
                    peek(&s);
                else
                    printf("Initialize stack first.\n");
                break;

            case 5:
                if (initialized)
                    display(&s);
                else
                    printf("Initialize stack first.\n");
                break;

            case 6:
                if (initialized)
                    findMinMax(&s);
                else
                    printf("Initialize stack first.\n");
                break;

            case 7:
                if (initialized)
                    countEvenOdd(&s);
                else
                    printf("Initialize stack first.\n");
                break;

            case 0:
                printf("Program terminated.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    if (initialized)
        free_stack(&s);

    return 0;
}
