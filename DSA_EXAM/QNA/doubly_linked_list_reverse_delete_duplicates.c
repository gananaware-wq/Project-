/*
  Question 7: Advanced Doubly Linked List
  File: doubly_linked_list_reverse_delete_duplicates.c

  Required operations from the practical list:
    createNode(), addAtStart(), addAtEnd(), addAtMiddle()
    deleteAtStart(), deleteAtEnd(), deleteAtMiddle(), display()

  Additional challenge operations:
    Insert at a given position
    Delete at a given position
    Delete all occurrences of a value
    Search and count nodes
    Display in reverse
    Reverse the links of the complete list

  Positions are 1-based. addAtMiddle() inserts after the first matching value.
  deleteAtMiddle() deletes the first matching value.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
} node;

node *createNode(int data);
node *addAtStart(int data, node *head);
node *addAtEnd(int data, node *head);
node *addAtMiddle(int data, int after, node *head);
node *deleteAtStart(node *head);
node *deleteAtEnd(node *head);
node *deleteAtMiddle(int key, node *head);
node *insertAtPosition(int data, int position, node *head);
node *deleteAtPosition(int position, node *head);
node *deleteAllOccurrences(int key, node *head);
node *reverseList(node *head);
void display(node *head);
void displayReverse(node *head);
int countNodes(node *head);
int searchNode(int key, node *head);
void freeList(node *head);

int main()
{
    node *head = NULL;
    int choice, data, key, position;

    do
    {
        printf("\n--------------- DOUBLY LINKED LIST ---------------\n");
        printf("1. Add node at start\n");
        printf("2. Add node at end\n");
        printf("3. Add node after a given value\n");
        printf("4. Delete node at start\n");
        printf("5. Delete node at end\n");
        printf("6. Delete first node with given value\n");
        printf("7. Insert node at a position\n");
        printf("8. Delete node at a position\n");
        printf("9. Delete all occurrences of a value\n");
        printf("10. Display forward\n");
        printf("11. Display reverse\n");
        printf("12. Search a value\n");
        printf("13. Count nodes\n");
        printf("14. Reverse the complete list\n");
        printf("0. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            break;
        }

        switch (choice)
        {
            case 1:
                printf("Enter data: ");
                if (scanf("%d", &data) != 1) goto input_error;
                head = addAtStart(data, head);
                break;

            case 2:
                printf("Enter data: ");
                if (scanf("%d", &data) != 1) goto input_error;
                head = addAtEnd(data, head);
                break;

            case 3:
                printf("Enter value after which to insert: ");
                if (scanf("%d", &key) != 1) goto input_error;
                printf("Enter new data: ");
                if (scanf("%d", &data) != 1) goto input_error;
                head = addAtMiddle(data, key, head);
                break;

            case 4:
                head = deleteAtStart(head);
                break;

            case 5:
                head = deleteAtEnd(head);
                break;

            case 6:
                printf("Enter value to delete: ");
                if (scanf("%d", &key) != 1) goto input_error;
                head = deleteAtMiddle(key, head);
                break;

            case 7:
                printf("Enter position (1-based): ");
                if (scanf("%d", &position) != 1) goto input_error;
                printf("Enter data: ");
                if (scanf("%d", &data) != 1) goto input_error;
                head = insertAtPosition(data, position, head);
                break;

            case 8:
                printf("Enter position to delete (1-based): ");
                if (scanf("%d", &position) != 1) goto input_error;
                head = deleteAtPosition(position, head);
                break;

            case 9:
                printf("Enter value to delete completely: ");
                if (scanf("%d", &key) != 1) goto input_error;
                head = deleteAllOccurrences(key, head);
                break;

            case 10:
                display(head);
                break;

            case 11:
                displayReverse(head);
                break;

            case 12:
                printf("Enter value to search: ");
                if (scanf("%d", &key) != 1) goto input_error;
                position = searchNode(key, head);
                if (position == -1)
                    printf("Value not found.\n");
                else
                    printf("First occurrence found at position %d.\n", position);
                break;

            case 13:
                printf("Total nodes = %d\n", countNodes(head));
                break;

            case 14:
                head = reverseList(head);
                printf("List links reversed.\n");
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    freeList(head);
    return 0;

input_error:
    printf("Invalid input. Releasing allocated memory.\n");
    freeList(head);
    return 1;
}

node *createNode(int data)
{
    node *newnode;

    newnode = (node *)malloc(sizeof(node));
    if (newnode == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;

    return newnode;
}

node *addAtStart(int data, node *head)
{
    node *newnode;

    newnode = createNode(data);
    if (newnode == NULL)
        return head;

    if (head != NULL)
    {
        newnode->next = head;
        head->prev = newnode;
    }

    head = newnode;
    return head;
}

node *addAtEnd(int data, node *head)
{
    node *temp, *newnode;

    newnode = createNode(data);
    if (newnode == NULL)
        return head;

    if (head == NULL)
        return newnode;

    temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newnode;
    newnode->prev = temp;

    return head;
}

node *addAtMiddle(int data, int after, node *head)
{
    node *temp, *newnode;

    temp = head;
    while (temp != NULL && temp->data != after)
        temp = temp->next;

    if (temp == NULL)
    {
        printf("Value %d not found.\n", after);
        return head;
    }

    newnode = createNode(data);
    if (newnode == NULL)
        return head;

    /* Update both forward and backward links around the new node. */
    newnode->next = temp->next;
    newnode->prev = temp;

    if (temp->next != NULL)
        temp->next->prev = newnode;

    temp->next = newnode;

    return head;
}

node *deleteAtStart(node *head)
{
    node *temp;

    if (head == NULL)
    {
        printf("List is empty.\n");
        return head;
    }

    temp = head;
    head = head->next;

    if (head != NULL)
        head->prev = NULL;

    free(temp);
    return head;
}

node *deleteAtEnd(node *head)
{
    node *temp;

    if (head == NULL)
    {
        printf("List is empty.\n");
        return head;
    }

    temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    if (temp->prev == NULL)
        head = NULL;              /* The list contained only one node. */
    else
        temp->prev->next = NULL;

    free(temp);
    return head;
}

node *deleteAtMiddle(int key, node *head)
{
    node *temp;

    temp = head;
    while (temp != NULL && temp->data != key)
        temp = temp->next;

    if (temp == NULL)
    {
        printf("Value %d not found.\n", key);
        return head;
    }

    if (temp->prev == NULL)
        head = temp->next;
    else
        temp->prev->next = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    free(temp);
    return head;
}

node *insertAtPosition(int data, int position, node *head)
{
    node *temp, *newnode;
    int i;

    if (position <= 0)
    {
        printf("Invalid position.\n");
        return head;
    }

    if (position == 1)
        return addAtStart(data, head);

    temp = head;
    for (i = 1; temp != NULL && i < position - 1; i++)
        temp = temp->next;

    if (temp == NULL)
    {
        printf("Position is out of range.\n");
        return head;
    }

    newnode = createNode(data);
    if (newnode == NULL)
        return head;

    newnode->next = temp->next;
    newnode->prev = temp;

    if (temp->next != NULL)
        temp->next->prev = newnode;

    temp->next = newnode;
    return head;
}

node *deleteAtPosition(int position, node *head)
{
    node *temp;
    int i;

    if (position <= 0 || head == NULL)
    {
        printf("Invalid position or empty list.\n");
        return head;
    }

    temp = head;
    for (i = 1; temp != NULL && i < position; i++)
        temp = temp->next;

    if (temp == NULL)
    {
        printf("Position is out of range.\n");
        return head;
    }

    if (temp->prev == NULL)
        head = temp->next;
    else
        temp->prev->next = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    free(temp);
    return head;
}

node *deleteAllOccurrences(int key, node *head)
{
    node *temp, *nextNode;
    int deleted = 0;

    temp = head;

    while (temp != NULL)
    {
        nextNode = temp->next;  /* Save next before freeing current node. */

        if (temp->data == key)
        {
            if (temp->prev == NULL)
                head = temp->next;
            else
                temp->prev->next = temp->next;

            if (temp->next != NULL)
                temp->next->prev = temp->prev;

            free(temp);
            deleted++;
        }

        temp = nextNode;
    }

    printf("%d occurrence(s) deleted.\n", deleted);
    return head;
}

void display(node *head)
{
    node *temp;

    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    temp = head;
    printf("NULL <-> ");

    while (temp != NULL)
    {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

void displayReverse(node *head)
{
    node *temp;

    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    printf("NULL <-> ");
    while (temp != NULL)
    {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }

    printf("NULL\n");
}

int countNodes(node *head)
{
    int count = 0;

    while (head != NULL)
    {
        count++;
        head = head->next;
    }

    return count;
}

int searchNode(int key, node *head)
{
    int position = 1;

    while (head != NULL)
    {
        if (head->data == key)
            return position;

        head = head->next;
        position++;
    }

    return -1;
}

node *reverseList(node *head)
{
    node *current, *temp = NULL;

    current = head;

    while (current != NULL)
    {
        /*
           Swap next and prev for each node.
           After the swap, current->prev points to the next node
           in the original forward direction.
        */
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;

        current = current->prev;
    }

    /* The old last node becomes the new head. */
    if (temp != NULL)
        head = temp->prev;

    return head;
}

void freeList(node *head)
{
    node *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}
