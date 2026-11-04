/*
DAY 2: Linked List

Q. Write a C/C++ program to implement a linked list with one integer as data item
and write following functions:

1. Display the list.
2. Insert a node at the beginning of the list.
3. Insert a node at the end of the list.
4. Remove the node at the beginning of the list.
5. Remove the node at the end of the list.
6. Find number of nodes in the list.
7. Search a data in the list.
8. Insert a node at given position in the list.
9. Delete a node at a given position in the list.
10. Insert a node after a node containing a given data item.
11. Delete a node after a node containing a given data item.
12. Display the linked list in reverse (recursive).

Note: Take care of cases like linked list empty and linked list containing
only one node.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node;

node* createNode(int data);
node* addAtStart(int data, node *head);
node* addAtEnd(int data, node *head);
node* deleteAtStart(node *head);
node* deleteAtEnd(node *head);
node* insertAtPosition(int data, int pos, node *head);
node* deleteAtPosition(int pos, node *head);
node* insertAfterData(int data, int key, node *head);
node* deleteAfterData(int key, node *head);
int countNodes(node *head);
void searchData(int key, node *head);
void display(node *head);
void displayReverse(node *head);

int main()
{
    node *head = NULL;
    node *temp;
    int data, key, pos;
    int choice;

    do
    {
        printf("\n-----------------Menu-----------------\n");
        printf("1. Display the list\n");
        printf("2. Insert a node at the beginning\n");
        printf("3. Insert a node at the end\n");
        printf("4. Delete a node at the beginning\n");
        printf("5. Delete a node at the end\n");
        printf("6. Count number of nodes\n");
        printf("7. Search a data in the list\n");
        printf("8. Insert a node at given position\n");
        printf("9. Delete a node at given position\n");
        printf("10. Insert a node after given data\n");
        printf("11. Delete a node after given data\n");
        printf("12. Display the list in reverse (recursive)\n");
        printf("13. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                display(head);
                break;

            case 2:
                printf("Enter data to add: ");
                scanf("%d", &data);
                head = addAtStart(data, head);
                break;

            case 3:
                printf("Enter data to add: ");
                scanf("%d", &data);
                head = addAtEnd(data, head);
                break;

            case 4:
                head = deleteAtStart(head);
                break;

            case 5:
                head = deleteAtEnd(head);
                break;

            case 6:
                printf("Number of nodes = %d\n", countNodes(head));
                break;

            case 7:
                printf("Enter data to search: ");
                scanf("%d", &key);
                searchData(key, head);
                break;

            case 8:
                printf("Enter position: ");
                scanf("%d", &pos);
                printf("Enter data to add: ");
                scanf("%d", &data);
                head = insertAtPosition(data, pos, head);
                break;

            case 9:
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                head = deleteAtPosition(pos, head);
                break;

            case 10:
                printf("Enter data after which to insert: ");
                scanf("%d", &key);
                printf("Enter data to add: ");
                scanf("%d", &data);
                head = insertAfterData(data, key, head);
                break;

            case 11:
                printf("Enter data after which to delete: ");
                scanf("%d", &key);
                head = deleteAfterData(key, head);
                break;

            case 12:
                if (head == NULL)
                    printf("There is no data\n");
                else
                {
                    printf("Reverse list: ");
                    displayReverse(head);
                    printf("\n");
                }
                break;

            case 13:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice\n");
        }

    } while (choice != 13);

    /* Free remaining nodes */
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

node* createNode(int data)
{
    node *newnode;

    newnode = (node *)malloc(sizeof(node));

    if (newnode == NULL)
    {
        printf("Memory allocation failed...\n");
        return NULL;
    }

    newnode->data = data;
    newnode->next = NULL;

    return newnode;
}

node* addAtStart(int data, node *head)
{
    node *newnode;

    newnode = createNode(data);
    if (newnode == NULL)
        return head;

    newnode->next = head;
    head = newnode;

    printf("Node inserted successfully...\n");
    return head;
}

node* addAtEnd(int data, node *head)
{
    node *temp, *newnode;

    newnode = createNode(data);
    if (newnode == NULL)
        return head;

    if (head == NULL)
        head = newnode;
    else
    {
        temp = head;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newnode;
    }

    printf("Node inserted successfully...\n");
    return head;
}

node* deleteAtStart(node *head)
{
    node *temp;

    if (head == NULL)
    {
        printf("There is no node..\n");
        return head;
    }

    temp = head;
    head = head->next;
    free(temp);

    printf("Node deleted successfully...\n");
    return head;
}

node* deleteAtEnd(node *head)
{
    node *temp, *prev;

    if (head == NULL)
    {
        printf("There is no node..\n");
        return head;
    }

    if (head->next == NULL)
    {
        free(head);
        head = NULL;
    }
    else
    {
        temp = head;
        while (temp->next != NULL)
        {
            prev = temp;
            temp = temp->next;
        }

        prev->next = NULL;
        free(temp);
    }

    printf("Node deleted successfully...\n");
    return head;
}

node* insertAtPosition(int data, int pos, node *head)
{
    node *temp, *newnode;
    int i;

    if (pos < 1)
    {
        printf("Invalid position\n");
        return head;
    }

    if (pos == 1)
        return addAtStart(data, head);

    temp = head;
    for (i = 1; i < pos - 1 && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL)
    {
        printf("Position not found\n");
        return head;
    }

    newnode = createNode(data);
    if (newnode == NULL)
        return head;

    newnode->next = temp->next;
    temp->next = newnode;

    printf("Node inserted successfully...\n");
    return head;
}

node* deleteAtPosition(int pos, node *head)
{
    node *temp, *prev;
    int i;

    if (head == NULL)
    {
        printf("There is no node..\n");
        return head;
    }

    if (pos < 1)
    {
        printf("Invalid position\n");
        return head;
    }

    if (pos == 1)
        return deleteAtStart(head);

    temp = head;
    for (i = 1; i < pos && temp != NULL; i++)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Position not found\n");
        return head;
    }

    prev->next = temp->next;
    free(temp);

    printf("Node deleted successfully...\n");
    return head;
}

node* insertAfterData(int data, int key, node *head)
{
    node *temp, *newnode;

    temp = head;
    while (temp != NULL && temp->data != key)
        temp = temp->next;

    if (temp == NULL)
    {
        printf("Data %d not found\n", key);
        return head;
    }

    newnode = createNode(data);
    if (newnode == NULL)
        return head;

    newnode->next = temp->next;
    temp->next = newnode;

    printf("Node inserted successfully...\n");
    return head;
}

node* deleteAfterData(int key, node *head)
{
    node *temp, *delnode;

    temp = head;
    while (temp != NULL && temp->data != key)
        temp = temp->next;

    if (temp == NULL)
    {
        printf("Data %d not found\n", key);
        return head;
    }

    if (temp->next == NULL)
    {
        printf("There is no node after %d\n", key);
        return head;
    }

    delnode = temp->next;
    temp->next = delnode->next;
    free(delnode);

    printf("Node deleted successfully...\n");
    return head;
}

int countNodes(node *head)
{
    int count = 0;
    node *temp;

    temp = head;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

void searchData(int key, node *head)
{
    node *temp;
    int pos = 1;

    temp = head;
    while (temp != NULL)
    {
        if (temp->data == key)
        {
            printf("Data %d found at position %d\n", key, pos);
            return;
        }

        temp = temp->next;
        pos++;
    }

    printf("Data %d not found\n", key);
}

void display(node *head)
{
    node *temp;

    if (head == NULL)
    {
        printf("There is no data\n");
        return;
    }

    temp = head;
    printf("HEAD -> ");
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void displayReverse(node *head)
{
    if (head == NULL)
        return;

    displayReverse(head->next);
    printf("%d ", head->data);
}
