/*
    DAY 9 - Q2: HASHMAP USING KEY-VALUE PAIRS

    Implement a HashMap to store key-value pairs.
    Duplicate values are allowed, and multiple values can share
    the same hash code.

    Collision handling used in this program: Separate Chaining.
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct Node
{
    int key;
    int value;
    struct Node *next;
};

struct Node *hashTable[SIZE] = {NULL};

int HashCode(int key);
void Insert(int key, int value);
int Search(int key, int *value);
void display();
void freeHashTable();

int HashCode(int key)
{
    int index = key % SIZE;

    if (index < 0)
        index = index + SIZE;

    return index;
}

void Insert(int key, int value)
{
    int index;
    struct Node *temp;
    struct Node *newNode;

    index = HashCode(key);

    /* If the key already exists, update its value. */
    temp = hashTable[index];

    while (temp != NULL)
    {
        if (temp->key == key)
        {
            temp->value = value;
            printf("Value updated for key %d.\n", key);
            return;
        }

        temp = temp->next;
    }

    newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->key = key;
    newNode->value = value;

    /* Add the new node at the beginning of the bucket list. */
    newNode->next = hashTable[index];
    hashTable[index] = newNode;

    printf("Key-value pair (%d, %d) inserted.\n", key, value);
}

int Search(int key, int *value)
{
    int index;
    struct Node *temp;

    index = HashCode(key);
    temp = hashTable[index];

    while (temp != NULL)
    {
        if (temp->key == key)
        {
            *value = temp->value;
            return 1;
        }

        temp = temp->next;
    }

    return 0;
}

void display()
{
    int i;
    struct Node *temp;

    printf("\n----- HASHMAP -----\n");

    for (i = 0; i < SIZE; i++)
    {
        printf("Bucket %d: ", i);

        temp = hashTable[i];

        if (temp == NULL)
            printf("Empty");

        while (temp != NULL)
        {
            printf("[%d : %d]", temp->key, temp->value);

            if (temp->next != NULL)
                printf(" -> ");

            temp = temp->next;
        }

        printf("\n");
    }
}

void freeHashTable()
{
    int i;
    struct Node *temp;
    struct Node *nextNode;

    for (i = 0; i < SIZE; i++)
    {
        temp = hashTable[i];

        while (temp != NULL)
        {
            nextNode = temp->next;
            free(temp);
            temp = nextNode;
        }

        hashTable[i] = NULL;
    }
}

int main()
{
    int choice;
    int key;
    int value;

    do
    {
        printf("\n----- HASHMAP MENU -----\n");
        printf("1. Insert key-value pair\n");
        printf("2. Search by key\n");
        printf("3. Display HashMap\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            freeHashTable();
            return 0;
        }

        switch (choice)
        {
            case 1:
                printf("Enter key: ");
                if (scanf("%d", &key) != 1)
                {
                    printf("Invalid input.\n");
                    freeHashTable();
                    return 0;
                }

                printf("Enter value: ");
                if (scanf("%d", &value) != 1)
                {
                    printf("Invalid input.\n");
                    freeHashTable();
                    return 0;
                }

                Insert(key, value);
                break;

            case 2:
                printf("Enter key to search: ");
                if (scanf("%d", &key) != 1)
                {
                    printf("Invalid input.\n");
                    freeHashTable();
                    return 0;
                }

                if (Search(key, &value))
                    printf("Key %d found. Value = %d\n", key, value);
                else
                    printf("Key %d not found.\n", key);
                break;

            case 3:
                display();
                break;

            case 0:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    freeHashTable();

    return 0;
}
