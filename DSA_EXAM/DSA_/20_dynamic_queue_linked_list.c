/*
    DAY 8 - Q2: DYNAMIC QUEUE USING LINKED LIST

    Implement a dynamic queue using linked list.

    Required functions:
    EnQueue(value, &front, &rear)
    DeQueue(&front, &rear)
    Front(front)
    Rear(rear)
    Display(front)
    isEmpty(front, rear)
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
int isEmpty(NODE *front, NODE *rear);
void EnQueue(int value, NODE **front, NODE **rear);
void DeQueue(NODE **front, NODE **rear);
void Front(NODE *front);
void Rear(NODE *rear);
void Display(NODE *front);

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

int isEmpty(NODE *front, NODE *rear)
{
    return front == NULL && rear == NULL;
}

void EnQueue(int value, NODE **front, NODE **rear)
{
    NODE *newNode = createNode(value);

    if (newNode == NULL)
        return;

    if (isEmpty(*front, *rear))
    {
        *front = newNode;
        *rear = newNode;
    }
    else
    {
        (*rear)->next = newNode;
        *rear = newNode;
    }

    printf("%d inserted into queue.\n", value);
}

void DeQueue(NODE **front, NODE **rear)
{
    NODE *temp;

    if (isEmpty(*front, *rear))
    {
        printf("Queue is empty.\n");
        return;
    }

    temp = *front;

    printf("Deleted element: %d\n", temp->data);

    *front = (*front)->next;

    if (*front == NULL)
    {
        *rear = NULL;
    }

    free(temp);
}

void Front(NODE *front)
{
    if (front == NULL)
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Front element: %d\n", front->data);
}

void Rear(NODE *rear)
{
    if (rear == NULL)
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Rear element: %d\n", rear->data);
}

void Display(NODE *front)
{
    NODE *temp;

    if (front == NULL)
    {
        printf("Queue is empty.\n");
        return;
    }

    temp = front;

    printf("Queue elements: ");
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

int main()
{
    NODE *front = NULL;
    NODE *rear = NULL;
    int choice, value;

    do
    {
        printf("\n----- DYNAMIC QUEUE MENU -----\n");
        printf("1. EnQueue\n");
        printf("2. DeQueue\n");
        printf("3. Display Front\n");
        printf("4. Display Rear\n");
        printf("5. Display Queue\n");
        printf("6. Check Empty\n");
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
                EnQueue(value, &front, &rear);
                break;

            case 2:
                DeQueue(&front, &rear);
                break;

            case 3:
                Front(front);
                break;

            case 4:
                Rear(rear);
                break;

            case 5:
                Display(front);
                break;

            case 6:
                if (isEmpty(front, rear))
                    printf("Queue is empty.\n");
                else
                    printf("Queue is not empty.\n");
                break;

            case 0:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    /* Free all remaining queue nodes */
    while (!isEmpty(front, rear))
    {
        DeQueue(&front, &rear);
    }

    return 0;
}
