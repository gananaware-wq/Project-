/*
    DAY 9 - Q1: HASHING USING ARRAY

    Use an array of size 10 to store user-defined integer values
    using hashing.

    Required functions:
    HashCode()
    Insert(value)
    Search(value)

    Collision handling used in this program: Linear Probing.
*/

#include <stdio.h>

#define SIZE 10

int hashTable[SIZE];
int occupied[SIZE] = {0};

int HashCode(int value);
void Insert(int value);
int Search(int value);
void display();

int HashCode(int value)
{
    int index = value % SIZE;

    if (index < 0)
        index = index + SIZE;

    return index;
}

void Insert(int value)
{
    int index;
    int i;

    index = HashCode(value);

    for (i = 0; i < SIZE; i++)
    {
        if (occupied[index] == 0)
        {
            hashTable[index] = value;
            occupied[index] = 1;

            printf("%d inserted at index %d.\n", value, index);
            return;
        }

        if (hashTable[index] == value)
        {
            printf("Value already exists in hash table.\n");
            return;
        }

        /* Linear probing: check the next index */
        index = (index + 1) % SIZE;
    }

    printf("Hash table is full. Cannot insert %d.\n", value);
}

int Search(int value)
{
    int index;
    int i;

    index = HashCode(value);

    for (i = 0; i < SIZE; i++)
    {
        if (occupied[index] == 0)
            return -1;

        if (hashTable[index] == value)
            return index;

        /* Continue searching at the next index */
        index = (index + 1) % SIZE;
    }

    return -1;
}

void display()
{
    int i;

    printf("\n----- HASH TABLE -----\n");

    for (i = 0; i < SIZE; i++)
    {
        if (occupied[i] == 1)
            printf("Index %d : %d\n", i, hashTable[i]);
        else
            printf("Index %d : Empty\n", i);
    }
}

int main()
{
    int choice;
    int value;
    int index;

    do
    {
        printf("\n----- HASHING MENU -----\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Display Hash Table\n");
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
                printf("Enter value to insert: ");
                if (scanf("%d", &value) != 1)
                {
                    printf("Invalid input.\n");
                    break;
                }
                Insert(value);
                break;

            case 2:
                printf("Enter value to search: ");
                if (scanf("%d", &value) != 1)
                {
                    printf("Invalid input.\n");
                    break;
                }

                index = Search(value);

                if (index != -1)
                    printf("%d found at index %d.\n", value, index);
                else
                    printf("%d not found in hash table.\n", value);
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

    return 0;
}
