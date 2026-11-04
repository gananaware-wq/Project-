/*
Q4. WAP to implement doubly linked list with following operations:
    createNode()
    addAtStart()
    addAtEnd()
    addAtMiddle() - add new value after node mentioned by user
    deleteAtStart()
    deleteAtEnd()
    deleteAtMiddle() - delete node mentioned by user
    display()
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
} node;

node* createNode(int data);
node* addAtStart(int data, node *head);
node* addAtEnd(int data, node *head);
node* addAtMiddle(int data, int after, node *head);
node* deleteAtStart(node *head);
node* deleteAtEnd(node *head);
node* deleteAtMiddle(int key, node *head);
void display(node *head);

int main()
{
    node *head = NULL;
    node *temp;
    int data, key, choice;

    do
    {
        printf("\n------------- MENU -------------\n");
        printf("1. Add a node at the start\n");
        printf("2. Add a node at the end\n");
        printf("3. Add a node after a given node\n");
        printf("4. Delete the node at the start\n");
        printf("5. Delete the node at the end\n");
        printf("6. Delete a given node\n");
        printf("7. Display the list\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter data to add: ");
                scanf("%d", &data);
                head = addAtStart(data, head);
                break;

            case 2:
                printf("Enter data to add: ");
                scanf("%d", &data);
                head = addAtEnd(data, head);
                break;

            case 3:
                printf("Enter data of the node after which to add: ");
                scanf("%d", &key);
                printf("Enter new data: ");
                scanf("%d", &data);
                head = addAtMiddle(data, key, head);
                break;

            case 4:
                head = deleteAtStart(head);
                break;

            case 5:
                head = deleteAtEnd(head);
                break;

            case 6:
                printf("Enter data of the node to delete: ");
                scanf("%d", &key);
                head = deleteAtMiddle(key, head);
                break;

            case 7:
                display(head);
                break;

            case 8:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
                break;
        }

    } while(choice != 8);

    /* Free all remaining nodes */
    while(head != NULL)
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

    if(newnode == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;

    return newnode;
}

node* addAtStart(int data, node *head)
{
    node *newnode;

    newnode = createNode(data);

    if(newnode == NULL)
    {
        return head;
    }

    if(head != NULL)
    {
        newnode->next = head;
        head->prev = newnode;
    }

    head = newnode;
    return head;
}

node* addAtEnd(int data, node *head)
{
    node *temp, *newnode;

    newnode = createNode(data);

    if(newnode == NULL)
    {
        return head;
    }

    if(head == NULL)
    {
        head = newnode;
    }
    else
    {
        temp = head;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newnode;
        newnode->prev = temp;
    }

    return head;
}

node* addAtMiddle(int data, int after, node *head)
{
    node *temp, *newnode;

    if(head == NULL)
    {
        printf("List is empty!\n");
        return head;
    }

    temp = head;

    while(temp != NULL && temp->data != after)
    {
        temp = temp->next;
    }

    if(temp == NULL)
    {
        printf("Node with data %d not found.\n", after);
        return head;
    }

    newnode = createNode(data);

    if(newnode == NULL)
    {
        return head;
    }

    newnode->next = temp->next;
    newnode->prev = temp;

    if(temp->next != NULL)
    {
        temp->next->prev = newnode;
    }

    temp->next = newnode;

    printf("Node inserted successfully.\n");
    return head;
}

node* deleteAtStart(node *head)
{
    node *temp;

    if(head == NULL)
    {
        printf("List is empty!\n");
        return head;
    }

    temp = head;
    head = head->next;

    if(head != NULL)
    {
        head->prev = NULL;
    }

    free(temp);

    printf("Node deleted successfully.\n");
    return head;
}

node* deleteAtEnd(node *head)
{
    node *temp;

    if(head == NULL)
    {
        printf("List is empty!\n");
        return head;
    }

    temp = head;

    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    if(temp->prev == NULL)
    {
        head = NULL;
    }
    else
    {
        temp->prev->next = NULL;
    }

    free(temp);

    printf("Node deleted successfully.\n");
    return head;
}

node* deleteAtMiddle(int key, node *head)
{
    node *temp;

    if(head == NULL)
    {
        printf("List is empty!\n");
        return head;
    }

    temp = head;

    while(temp != NULL && temp->data != key)
    {
        temp = temp->next;
    }

    if(temp == NULL)
    {
        printf("Node with data %d not found.\n", key);
        return head;
    }

    if(temp->prev == NULL)
    {
        head = temp->next;
    }
    else
    {
        temp->prev->next = temp->next;
    }

    if(temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }

    free(temp);

    printf("Node deleted successfully.\n");
    return head;
}

void display(node *head)
{
    node *temp;

    if(head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    temp = head;

    printf("NULL <-> ");

    while(temp != NULL)
    {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}
