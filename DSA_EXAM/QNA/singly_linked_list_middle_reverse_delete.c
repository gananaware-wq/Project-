/*
    Question 1: Singly Linked List Operations
    Marks: 20

    Operations:
    1. Insert at beginning
    2. Insert at end
    3. Delete first occurrence of a value
    4. Count nodes
    5. Find middle node (second middle when node count is even)
    6. Reverse the linked list
    7. Display the linked list
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} NODE;

NODE *head = NULL;

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

void addAtStart(int value)
{
    NODE *newNode = createNode(value);

    if (newNode == NULL)
        return;

    newNode->next = head;
    head = newNode;
}

void addAtEnd(int value)
{
    NODE *newNode = createNode(value);
    NODE *temp;

    if (newNode == NULL)
        return;

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
}

void deleteByValue(int value)
{
    NODE *temp = head;
    NODE *prev = NULL;

    if (head == NULL)
    {
        printf("Linked list is empty.\n");
        return;
    }

    /* Stop at the first matching node, so only its first occurrence is deleted. */
    while (temp != NULL && temp->data != value)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Element not found.\n");
        return;
    }

    if (prev == NULL)
    {
        /* The first node itself contains the value. */
        head = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }

    free(temp);
    printf("Element deleted successfully.\n");
}

int countNodes(void)
{
    NODE *temp = head;
    int count = 0;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

void displayMiddle(void)
{
    NODE *slow = head;
    NODE *fast = head;

    if (head == NULL)
    {
        printf("Linked list is empty.\n");
        return;
    }

    /*
       slow moves one node and fast moves two nodes.
       For an even number of nodes, slow stops at the second middle node.
    */
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    printf("Middle element = %d\n", slow->data);
}

void reverseList(void)
{
    NODE *prev = NULL;
    NODE *current = head;
    NODE *nextNode = NULL;

    /*
       Save the next node before reversing the current link.
       Otherwise, the remaining list would become unreachable.
    */
    while (current != NULL)
    {
        nextNode = current->next;
        current->next = prev;

        prev = current;
        current = nextNode;
    }

    head = prev;
    printf("Linked list reversed successfully.\n");
}

void display(void)
{
    NODE *temp = head;

    if (head == NULL)
    {
        printf("Linked list is empty.\n");
        return;
    }

    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

void freeList(void)
{
    NODE *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void)
{
    int choice;
    int value;

    do
    {
        printf("\n----- SINGLY LINKED LIST -----\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Delete by Value\n");
        printf("4. Count Nodes\n");
        printf("5. Find Middle Element\n");
        printf("6. Reverse Linked List\n");
        printf("7. Display Linked List\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            freeList();
            return 1;
        }

        switch (choice)
        {
            case 1:
                printf("Enter value: ");
                if (scanf("%d", &value) != 1)
                {
                    printf("Invalid input.\n");
                    freeList();
                    return 1;
                }
                addAtStart(value);
                break;

            case 2:
                printf("Enter value: ");
                if (scanf("%d", &value) != 1)
                {
                    printf("Invalid input.\n");
                    freeList();
                    return 1;
                }
                addAtEnd(value);
                break;

            case 3:
                printf("Enter value to delete: ");
                if (scanf("%d", &value) != 1)
                {
                    printf("Invalid input.\n");
                    freeList();
                    return 1;
                }
                deleteByValue(value);
                break;

            case 4:
                printf("Total number of nodes = %d\n", countNodes());
                break;

            case 5:
                displayMiddle();
                break;

            case 6:
                reverseList();
                break;

            case 7:
                display();
                break;

            case 0:
                printf("Program terminated.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    freeList();
    return 0;
}
