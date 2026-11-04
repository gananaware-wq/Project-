/*
    DAY 5 - Q2: CIRCULAR QUEUE USING ARRAY

    WAP to implement a circular queue using arrays.
    (Use structure, runtime memory, menu driven)
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct QUEUE
{
    int size;
    int front;
    int rear;
    int *queue;
} QUEUE;

void initQueue(QUEUE *q);
int isFull(QUEUE q);
int isEmpty(QUEUE q);
void enQueue(QUEUE *q);
void deQueue(QUEUE *q);
void display(QUEUE q);

void initQueue(QUEUE *q)
{
    int size;

    printf("Enter the size of circular queue: ");
    if (scanf("%d", &size) != 1 || size <= 0)
    {
        printf("Invalid queue size.\n");
        return;
    }

    int *temp = (int *)malloc(size * sizeof(int));

    if (temp == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    free(q->queue);

    q->size = size;
    q->front = -1;
    q->rear = -1;
    q->queue = temp;

    printf("Circular queue initialized successfully.\n");
}

int isFull(QUEUE q)
{
    if (q.queue == NULL)
        return 0;

    return (q.rear + 1) % q.size == q.front;
}

int isEmpty(QUEUE q)
{
    if (q.queue == NULL || q.front == -1)
        return 1;

    return 0;
}

void enQueue(QUEUE *q)
{
    int value;

    if (q->queue == NULL)
    {
        printf("Please initialize the queue first.\n");
        return;
    }

    if (isFull(*q))
    {
        printf("Circular queue is full.\n");
        return;
    }

    printf("Enter value: ");
    if (scanf("%d", &value) != 1)
    {
        printf("Invalid input.\n");
        return;
    }

    if (isEmpty(*q))
    {
        q->front = 0;
        q->rear = 0;
    }
    else
    {
        q->rear = (q->rear + 1) % q->size;
    }

    q->queue[q->rear] = value;

    printf("%d inserted into circular queue.\n", value);
}

void deQueue(QUEUE *q)
{
    int value;

    if (isEmpty(*q))
    {
        printf("Circular queue is empty.\n");
        return;
    }

    value = q->queue[q->front];
    printf("Deleted element: %d\n", value);

    if (q->front == q->rear)
    {
        q->front = -1;
        q->rear = -1;
    }
    else
    {
        q->front = (q->front + 1) % q->size;
    }
}

void display(QUEUE q)
{
    int i;

    if (isEmpty(q))
    {
        printf("Circular queue is empty.\n");
        return;
    }

    printf("Circular queue elements: ");

    i = q.front;
    while (1)
    {
        printf("%d ", q.queue[i]);

        if (i == q.rear)
            break;

        i = (i + 1) % q.size;
    }

    printf("\n");
}

int main()
{
    QUEUE q;

    q.size = 0;
    q.front = -1;
    q.rear = -1;
    q.queue = NULL;

    int choice;

    do
    {
        printf("\n----- CIRCULAR QUEUE MENU -----\n");
        printf("1. Initialize Circular Queue\n");
        printf("2. EnQueue\n");
        printf("3. DeQueue\n");
        printf("4. Display\n");
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
                initQueue(&q);
                break;

            case 2:
                enQueue(&q);
                break;

            case 3:
                deQueue(&q);
                break;

            case 4:
                display(q);
                break;

            case 0:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    free(q.queue);

    return 0;
}
