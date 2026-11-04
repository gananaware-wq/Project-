/*
Q5. WAP to implement singly circular linked list with following operations:
    createNode()
    addAtStart()
    addAtEnd()
    deleteAtStart()
    deleteAtEnd()
    display()
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
void display(node *head);

int main()
{
    node *head = NULL;
    node *temp;
    int data, choice;

    do
    {
        printf("\n------------- MENU -------------\n");
        printf("1. Add a node at the start\n");
        printf("2. Add a node at the end\n");
        printf("3. Delete the node at the start\n");
        printf("4. Delete the node at the end\n");
        printf("5. Display the list\n");
        printf("6. Exit\n");
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
                head = deleteAtStart(head);
                break;

            case 4:
                head = deleteAtEnd(head);
                break;

            case 5:
                display(head);
                break;

            case 6:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
                break;
        }

    } while(choice != 6);

    /* Free the remaining nodes */
    if(head != NULL)
    {
        temp = head;

        while(temp->next != head)
        {
            temp = temp->next;
        }

        temp->next = NULL;

        while(head != NULL)
        {
            temp = head;
            head = head->next;
            free(temp);
        }
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

    return newnode;
}

node* addAtStart(int data, node *head)
{
    node *temp, *newnode;

    newnode = createNode(data);

    if(newnode == NULL)
    {
        return head;
    }

    if(head == NULL)
    {
        newnode->next = newnode;
        head = newnode;
    }
    else
    {
        temp = head;

        while(temp->next != head)
        {
            temp = temp->next;
        }

        newnode->next = head;
        temp->next = newnode;
        head = newnode;
    }

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
        newnode->next = newnode;
        head = newnode;
    }
    else
    {
        temp = head;

        while(temp->next != head)
        {
            temp = temp->next;
        }

        temp->next = newnode;
        newnode->next = head;
    }

    return head;
}

node* deleteAtStart(node *head)
{
    node *temp, *last;

    if(head == NULL)
    {
        printf("List is empty!\n");
        return head;
    }

    temp = head;

    if(head->next == head)
    {
        head = NULL;
    }
    else
    {
        last = head;

        while(last->next != head)
        {
            last = last->next;
        }

        head = head->next;
        last->next = head;
    }

    free(temp);

    printf("Node deleted successfully.\n");
    return head;
}

node* deleteAtEnd(node *head)
{
    node *temp, *prev_temp;

    if(head == NULL)
    {
        printf("List is empty!\n");
        return head;
    }

    temp = head;

    if(head->next == head)
    {
        head = NULL;
    }
    else
    {
        while(temp->next != head)
        {
            prev_temp = temp;
            temp = temp->next;
        }

        prev_temp->next = head;
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

    do
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while(temp != head);

    printf("(back to head %d)\n", head->data);
}
