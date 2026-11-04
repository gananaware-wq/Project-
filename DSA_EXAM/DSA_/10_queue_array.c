/*
    DAY 5 - Q1: QUEUE USING ARRAY

    WAP to implement user defined Queue using Array. Accept the size of the
    queue from the user and allocate memory for the queue at runtime. Make
    use of structure to store queue size, memory, front and rear. Create a
    menu driven program providing options: initQueue(), enQueue(),
    deQueue(), display(). Implement other required functions isFull(),
    isEmpty().
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

    printf("Enter the size of queue: ");
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

    printf("Queue initialized successfully.\n");
}

int isFull(QUEUE q)
{
    if (q.queue == NULL)
        return 0;

    return q.rear == q.size - 1;
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
        printf("Queue is full.\n");
        return;
    }

    printf("Enter value: ");
    if (scanf("%d", &value) != 1)
    {
        printf("Invalid input.\n");
        return;
    }

    if (isEmpty(*q))
        q->front = 0;

    q->rear++;
    q->queue[q->rear] = value;

    printf("%d inserted into queue.\n", value);
}

void deQueue(QUEUE *q)
{
    int value;

    if (isEmpty(*q))
    {
        printf("Queue is empty.\n");
        return;
    }

    value = q->queue[q->front];
    printf("Deleted element: %d\n", value);

    q->front++;

    if (q->front > q->rear)
    {
        q->front = -1;
        q->rear = -1;
    }
}

void display(QUEUE q)
{
    int i;

    if (isEmpty(q))
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue elements: ");
    for (i = q.front; i <= q.rear; i++)
    {
        printf("%d ", q.queue[i]);
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
        printf("\n----- QUEUE MENU -----\n");
        printf("1. Initialize Queue\n");
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
