#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    int data;
    struct NODE *next;
} NODE;

typedef struct STACK
{
    NODE *top;
    int count;
} STACK;

typedef struct QUEUE
{
    NODE *front;
    NODE *rear;
    int count;
} QUEUE;

NODE *createNode(int value)
{
    NODE *newNode = (NODE *)malloc(sizeof(NODE));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\\n");
        return NULL;
    }

    newNode->data = value;
    newNode->next = NULL;

    return newNode;
}

/* -------------------- STACK OPERATIONS -------------------- */

void initStack(STACK *s)
{
    s->top = NULL;
    s->count = 0;
}

int isStackEmpty(STACK *s)
{
    return s->top == NULL;
}

void push(STACK *s, int value)
{
    NODE *newNode = createNode(value);

    if (newNode == NULL)
        return;

    newNode->next = s->top;
    s->top = newNode;
    s->count++;

    printf("%d pushed into stack.\\n", value);
}

int pop(STACK *s, int *deletedValue)
{
    NODE *temp;

    if (isStackEmpty(s))
    {
        printf("Stack underflow. Stack is empty.\\n");
        return 0;
    }

    temp = s->top;
    *deletedValue = temp->data;

    s->top = s->top->next;
    free(temp);
    s->count--;

    return 1;
}

void peekStack(STACK *s)
{
    if (isStackEmpty(s))
        printf("Stack is empty.\\n");
    else
        printf("Top element: %d\\n", s->top->data);
}

void displayStack(STACK *s)
{
    NODE *temp = s->top;

    if (temp == NULL)
    {
        printf("Stack is empty.\\n");
        return;
    }

    printf("Stack (TOP to BOTTOM): ");

    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\\nTotal stack elements: %d\\n", s->count);
}

void freeStack(STACK *s)
{
    NODE *temp;

    while (s->top != NULL)
    {
        temp = s->top;
        s->top = s->top->next;
        free(temp);
    }

    s->count = 0;
}

/* -------------------- QUEUE OPERATIONS -------------------- */

void initQueue(QUEUE *q)
{
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
}

int isQueueEmpty(QUEUE *q)
{
    return q->front == NULL;
}

void enQueue(QUEUE *q, int value)
{
    NODE *newNode = createNode(value);

    if (newNode == NULL)
        return;

    if (isQueueEmpty(q))
    {
        /* First node is both front and rear. */
        q->front = newNode;
        q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }

    q->count++;
    printf("%d inserted into queue.\\n", value);
}

int deQueue(QUEUE *q, int *deletedValue)
{
    NODE *temp;

    if (isQueueEmpty(q))
    {
        printf("Queue underflow. Queue is empty.\\n");
        return 0;
    }

    temp = q->front;
    *deletedValue = temp->data;

    q->front = q->front->next;
    free(temp);
    q->count--;

    /* If the last node is removed, rear must also become NULL. */
    if (q->front == NULL)
        q->rear = NULL;

    return 1;
}

void peekQueue(QUEUE *q)
{
    if (isQueueEmpty(q))
        printf("Queue is empty.\\n");
    else
        printf("Front element: %d\\n", q->front->data);
}

void displayQueue(QUEUE *q)
{
    NODE *temp = q->front;

    if (temp == NULL)
    {
        printf("Queue is empty.\\n");
        return;
    }

    printf("Queue (FRONT to REAR): ");

    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\\nTotal queue elements: %d\\n", q->count);
}

void freeQueue(QUEUE *q)
{
    NODE *temp;

    while (q->front != NULL)
    {
        temp = q->front;
        q->front = q->front->next;
        free(temp);
    }

    q->rear = NULL;
    q->count = 0;
}

/* -------------------- MAIN MENU -------------------- */

int main()
{
    STACK s;
    QUEUE q;
    int mainChoice, choice, value;

    initStack(&s);
    initQueue(&q);

    do
    {
        printf("\\n========== LINKED LIST STACK AND QUEUE ==========\\n");
        printf("1. Stack operations\\n");
        printf("2. Queue operations\\n");
        printf("3. Display stack and queue counts\\n");
        printf("0. Exit\\n");
        printf("Enter choice: ");

        if (scanf("%d", &mainChoice) != 1)
        {
            printf("Invalid input. Exiting.\\n");
            break;
        }

        switch (mainChoice)
        {
            case 1:
                do
                {
                    printf("\\n----- STACK MENU -----\\n");
                    printf("1. Push\\n");
                    printf("2. Pop\\n");
                    printf("3. Peek\\n");
                    printf("4. Display\\n");
                    printf("0. Back to main menu\\n");
                    printf("Enter choice: ");

                    if (scanf("%d", &choice) != 1)
                    {
                        printf("Invalid input.\\n");
                        choice = 0;
                        break;
                    }

                    switch (choice)
                    {
                        case 1:
                            printf("Enter value: ");
                            if (scanf("%d", &value) == 1)
                                push(&s, value);
                            else
                                printf("Invalid value.\\n");
                            break;

                        case 2:
                            if (pop(&s, &value))
                                printf("Popped element: %d\\n", value);
                            break;

                        case 3:
                            peekStack(&s);
                            break;

                        case 4:
                            displayStack(&s);
                            break;

                        case 0:
                            break;

                        default:
                            printf("Invalid choice.\\n");
                    }

                } while (choice != 0);
                break;

            case 2:
                do
                {
                    printf("\\n----- QUEUE MENU -----\\n");
                    printf("1. Enqueue\\n");
                    printf("2. Dequeue\\n");
                    printf("3. Peek front\\n");
                    printf("4. Display\\n");
                    printf("0. Back to main menu\\n");
                    printf("Enter choice: ");

                    if (scanf("%d", &choice) != 1)
                    {
                        printf("Invalid input.\\n");
                        choice = 0;
                        break;
                    }

                    switch (choice)
                    {
                        case 1:
                            printf("Enter value: ");
                            if (scanf("%d", &value) == 1)
                                enQueue(&q, value);
                            else
                                printf("Invalid value.\\n");
                            break;

                        case 2:
                            if (deQueue(&q, &value))
                                printf("Dequeued element: %d\\n", value);
                            break;

                        case 3:
                            peekQueue(&q);
                            break;

                        case 4:
                            displayQueue(&q);
                            break;

                        case 0:
                            break;

                        default:
                            printf("Invalid choice.\\n");
                    }

                } while (choice != 0);
                break;

            case 3:
                printf("Stack count: %d\\n", s.count);
                printf("Queue count: %d\\n", q.count);
                break;

            case 0:
                printf("Exiting program.\\n");
                break;

            default:
                printf("Invalid choice.\\n");
        }

    } while (mainChoice != 0);

    /* Release all dynamically allocated nodes before program termination. */
    freeStack(&s);
    freeQueue(&q);

    return 0;
}
