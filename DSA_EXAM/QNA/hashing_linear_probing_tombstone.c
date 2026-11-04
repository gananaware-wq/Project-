#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define OCCUPIED 1
#define DELETED 2

typedef struct HASH
{
    int size;
    int *key;
    int *state;
    int totalCollisions;
} HASH;

HASH *createHashTable(int size)
{
    HASH *h = (HASH *)malloc(sizeof(HASH));

    if (h == NULL)
        return NULL;

    h->key = (int *)malloc(size * sizeof(int));
    h->state = (int *)calloc(size, sizeof(int));

    if (h->key == NULL || h->state == NULL)
    {
        free(h->key);
        free(h->state);
        free(h);
        return NULL;
    }

    h->size = size;
    h->totalCollisions = 0;

    return h;
}

/* Handles negative keys and always returns an index from 0 to size - 1. */
int hashFunction(int key, int size)
{
    int index = key % size;

    if (index < 0)
        index += size;

    return index;
}

/* Linear probing checks the next slot and wraps around at the table end. */
int insertKey(HASH *h, int key)
{
    int index = hashFunction(key, h->size);
    int firstDeleted = -1;
    int i;

    for (i = 0; i < h->size; i++)
    {
        int current = (index + i) % h->size;

        if (h->state[current] == OCCUPIED)
        {
            if (h->key[current] == key)
            {
                printf("Duplicate key. Not inserted.\\n");
                return 0;
            }

            h->totalCollisions++;
        }
        else if (h->state[current] == DELETED)
        {
            if (firstDeleted == -1)
                firstDeleted = current;
        }
        else
        {
            if (firstDeleted != -1)
                current = firstDeleted;

            h->key[current] = key;
            h->state[current] = OCCUPIED;
            printf("Key inserted at index %d.\\n", current);
            return 1;
        }
    }

    /* Reuse a deleted slot even when no EMPTY slot remains. */
    if (firstDeleted != -1)
    {
        h->key[firstDeleted] = key;
        h->state[firstDeleted] = OCCUPIED;
        printf("Key inserted at index %d.\\n", firstDeleted);
        return 1;
    }

    printf("Hash table is full. Cannot insert.\\n");
    return 0;
}

int searchKey(HASH *h, int key)
{
    int index = hashFunction(key, h->size);
    int i;

    for (i = 0; i < h->size; i++)
    {
        int current = (index + i) % h->size;

        /* EMPTY means the key cannot occur later in this probe sequence. */
        if (h->state[current] == EMPTY)
            return -1;

        if (h->state[current] == OCCUPIED && h->key[current] == key)
            return current;
    }

    return -1;
}

int deleteKey(HASH *h, int key)
{
    int index = searchKey(h, key);

    if (index == -1)
    {
        printf("Key not found.\\n");
        return 0;
    }

    /* DELETED is a tombstone; do not mark this slot EMPTY. */
    h->state[index] = DELETED;
    printf("Key deleted from index %d.\\n", index);

    return 1;
}

void displayTable(HASH *h)
{
    int i;

    printf("\\nIndex\\tKey\\tState\\n");

    for (i = 0; i < h->size; i++)
    {
        printf("%d\\t", i);

        if (h->state[i] == OCCUPIED)
            printf("%d\\tOCCUPIED\\n", h->key[i]);
        else if (h->state[i] == DELETED)
            printf("-\\tDELETED\\n");
        else
            printf("-\\tEMPTY\\n");
    }
}

void displayStatistics(HASH *h)
{
    int i, occupied = 0, deleted = 0;

    for (i = 0; i < h->size; i++)
    {
        if (h->state[i] == OCCUPIED)
            occupied++;
        else if (h->state[i] == DELETED)
            deleted++;
    }

    printf("\\nOccupied slots : %d", occupied);
    printf("\\nDeleted slots  : %d", deleted);
    printf("\\nLoad factor    : %.2f", (float)occupied / h->size);
    printf("\\nCollisions     : %d\\n", h->totalCollisions);
}

void freeHashTable(HASH *h)
{
    if (h != NULL)
    {
        free(h->key);
        free(h->state);
        free(h);
    }
}

int main()
{
    HASH *h;
    int size, choice, key, index;

    printf("Enter hash table size: ");
    if (scanf("%d", &size) != 1 || size <= 0)
    {
        printf("Invalid table size.\\n");
        return 1;
    }

    h = createHashTable(size);

    if (h == NULL)
    {
        printf("Memory allocation failed.\\n");
        return 1;
    }

    do
    {
        printf("\\n----- HASH TABLE: LINEAR PROBING -----\\n");
        printf("1. Insert key\\n");
        printf("2. Search key\\n");
        printf("3. Delete key\\n");
        printf("4. Display table\\n");
        printf("5. Display statistics\\n");
        printf("0. Exit\\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\\n");
            break;
        }

        switch (choice)
        {
            case 1:
                printf("Enter key: ");
                if (scanf("%d", &key) == 1)
                    insertKey(h, key);
                else
                    printf("Invalid key.\\n");
                break;

            case 2:
                printf("Enter key to search: ");
                if (scanf("%d", &key) == 1)
                {
                    index = searchKey(h, key);

                    if (index == -1)
                        printf("Key not found.\\n");
                    else
                        printf("Key found at index %d.\\n", index);
                }
                else
                    printf("Invalid key.\\n");
                break;

            case 3:
                printf("Enter key to delete: ");
                if (scanf("%d", &key) == 1)
                    deleteKey(h, key);
                else
                    printf("Invalid key.\\n");
                break;

            case 4:
                displayTable(h);
                break;

            case 5:
                displayStatistics(h);
                break;

            case 0:
                printf("Exiting...\\n");
                break;

            default:
                printf("Invalid choice.\\n");
        }

    } while (choice != 0);

    freeHashTable(h);
    return 0;
}
