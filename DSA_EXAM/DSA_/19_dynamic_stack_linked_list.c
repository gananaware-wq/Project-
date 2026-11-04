/*
    DAY 8 - Q1: DYNAMIC STACK USING LINKED LIST

    Implement a dynamic stack using linked list.

    Required functions:
    Push(value, &top)
    Pop(&top)
    Pick(top)
    Display(top)
    isEmpty(top)
    createNode()
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} NODE;

NODE *createNode(int value);
int isEmpty(NODE *top);
void Push(int value, NODE **top);
void Pop(NODE **top);
void Pick(NODE *top);
void Display(NODE *top);

NODE *createNode(int value)
{
    NODE *newNode = (NODE *)malloc(sizeof(NODE));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    newNode->data = value;
    newNode->next = NULL;

    return newNode;
}

int isEmpty(NODE *top)
{
    return top == NULL;
}

void Push(int value, NODE **top)
{
    NODE *newNode = createNode(value);

    if (newNode == NULL)
        return;

    newNode->next = *top;
    *top = newNode;

    printf("%d pushed into stack.\n", value);
}

void Pop(NODE **top)
{
    NODE *temp;

    if (isEmpty(*top))
    {
        printf("Stack is empty.\n");
        return;
    }

    temp = *top;

    printf("Popped element: %d\n", temp->data);

    *top = (*top)->next;
    free(temp);
}

void Pick(NODE *top)
{
    if (isEmpty(top))
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("Top element: %d\n", top->data);
}

void Display(NODE *top)
{
    NODE *temp;

    if (isEmpty(top))
    {
        printf("Stack is empty.\n");
        return;
    }

    temp = top;

    printf("Stack elements (Top to Bottom): ");
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

int main()
{
    NODE *top = NULL;
    int choice, value;

    do
    {
        printf("\n----- DYNAMIC STACK MENU -----\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Pick (View Top)\n");
        printf("4. Display\n");
        printf("5. Check Empty\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            break;
        }

        switch (choice)
        {
            case 1:
                printf("Enter value: ");
                if (scanf("%d", &value) != 1)
                {
                    printf("Invalid input.\n");
                    break;
                }
                Push(value, &top);
                break;

            case 2:
                Pop(&top);
                break;

            case 3:
                Pick(top);
                break;

            case 4:
                Display(top);
                break;

            case 5:
                if (isEmpty(top))
                    printf("Stack is empty.\n");
                else
                    printf("Stack is not empty.\n");
                break;

            case 0:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    /* Free all remaining stack nodes */
    while (!isEmpty(top))
    {
        Pop(&top);
    }

    return 0;
}
