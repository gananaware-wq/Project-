/*
    Question 2: Circular Queue Using Dynamic Array
    Marks: 20

    Operations:
    1. Initialize queue at runtime
    2. Enqueue an element
    3. Dequeue an element
    4. Display queue elements
    5. Display front and rear elements
    6. Check whether queue is full or empty

    Tricky point:
    The queue uses circular movement. The modulo operator (%) brings
    front and rear back to index 0 after reaching the last array position.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct QUEUE
{
    int size;
    int front;
    int rear;
    int count;
    int *arr;
} QUEUE;

QUEUE *createQueue(int size)
{
    QUEUE *q;

    if (size <= 0)
    {
        printf("Queue size must be greater than zero.\n");
        return NULL;
    }

    q = (QUEUE *)malloc(sizeof(QUEUE));

    if (q == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    q->arr = (int *)malloc(size * sizeof(int));

    if (q->arr == NULL)
    {
        printf("Memory allocation failed.\n");
        free(q);
        return NULL;
    }

    q->size = size;
    q->front = 0;
    q->rear = -1;
    q->count = 0;

    return q;
}

int isEmpty(QUEUE *q)
{
    return (q == NULL || q->count == 0);
}

int isFull(QUEUE *q)
{
    return (q != NULL && q->count == q->size);
}

void enQueue(QUEUE *q, int value)
{
    if (q == NULL)
    {
        printf("Queue is not initialized.\n");
        return;
    }

    if (isFull(q))
    {
        printf("Queue is full. Cannot insert.\n");
        return;
    }

    /*
       Move rear circularly.
       Example: if rear is at the last index, (rear + 1) % size becomes 0.
    */
    q->rear = (q->rear + 1) % q->size;
    q->arr[q->rear] = value;
    q->count++;

    printf("%d inserted into queue.\n", value);
}

void deQueue(QUEUE *q)
{
    int value;

    if (q == NULL)
    {
        printf("Queue is not initialized.\n");
        return;
    }

    if (isEmpty(q))
    {
        printf("Queue is empty. Cannot delete.\n");
        return;
    }

    value = q->arr[q->front];

    /*
       Move front circularly to the next logical element.
       count is reduced so the removed position becomes available again.
    */
    q->front = (q->front + 1) % q->size;
    q->count--;

    /* Reset indexes when the queue becomes empty. */
    if (q->count == 0)
    {
        q->front = 0;
        q->rear = -1;
    }

    printf("Deleted element = %d\n", value);
}

void display(QUEUE *q)
{
    int i;
    int index;

    if (q == NULL)
    {
        printf("Queue is not initialized.\n");
        return;
    }

    if (isEmpty(q))
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue elements: ");

    /*
       Display in logical order, not physical array order.
       (front + i) % size handles the case where elements wrap around.
    */
    for (i = 0; i < q->count; i++)
    {
        index = (q->front + i) % q->size;
        printf("%d ", q->arr[index]);
    }

    printf("\n");
}

void displayFrontRear(QUEUE *q)
{
    if (q == NULL)
    {
        printf("Queue is not initialized.\n");
        return;
    }

    if (isEmpty(q))
    {
        printf("Queue is empty. Front and rear are not available.\n");
        return;
    }

    printf("Front element = %d\n", q->arr[q->front]);
    printf("Rear element = %d\n", q->arr[q->rear]);
}

void freeQueue(QUEUE *q)
{
    if (q != NULL)
    {
        free(q->arr);
        free(q);
    }
}

int main(void)
{
    QUEUE *q = NULL;
    int choice;
    int size;
    int value;

    do
    {
        printf("\n----- CIRCULAR QUEUE -----\n");
        printf("1. Initialize Queue\n");
        printf("2. Enqueue\n");
        printf("3. Dequeue\n");
        printf("4. Display Queue\n");
        printf("5. Display Front and Rear\n");
        printf("6. Check Full or Empty\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            freeQueue(q);
            return 1;
        }

        switch (choice)
        {
            case 1:
                if (q != NULL)
                {
                    printf("Queue is already initialized. Free it before creating another queue.\n");
                    break;
                }

                printf("Enter queue size: ");

                if (scanf("%d", &size) != 1)
                {
                    printf("Invalid input.\n");
                    freeQueue(q);
                    return 1;
                }

                q = createQueue(size);

                if (q != NULL)
                    printf("Queue initialized successfully.\n");

                break;

            case 2:
                if (q == NULL)
                {
                    printf("Initialize queue first.\n");
                    break;
                }

                printf("Enter value: ");

                if (scanf("%d", &value) != 1)
                {
                    printf("Invalid input.\n");
                    freeQueue(q);
                    return 1;
                }

                enQueue(q, value);
                break;

            case 3:
                deQueue(q);
                break;

            case 4:
                display(q);
                break;

            case 5:
                displayFrontRear(q);
                break;

            case 6:
                if (q == NULL)
                {
                    printf("Queue is not initialized.\n");
                }
                else
                {
                    printf("Queue is %s.\n", isFull(q) ? "FULL" : "NOT FULL");
                    printf("Queue is %s.\n", isEmpty(q) ? "EMPTY" : "NOT EMPTY");
                }
                break;

            case 0:
                printf("Program terminated.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    freeQueue(q);
    return 0;
}
