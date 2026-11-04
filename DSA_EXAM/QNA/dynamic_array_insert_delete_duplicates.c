/*
    Question 4: Dynamic Array Operations
    Marks: 20

    Operations:
    1. Create an array using dynamic memory allocation
    2. Insert an element at a given position
    3. Delete an element from a given position
    4. Find the second-largest distinct element
    5. Remove duplicate elements
    6. Display the array in reverse order
    7. Calculate average of array elements
    8. Display the array

    Tricky points:
    - Use a temporary pointer with realloc() so the original memory is not lost
      if reallocation fails.
    - Array positions are entered using 1-based indexing.
    - The second-largest value must be distinct from the largest value.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct ARRAY
{
    int *arr;
    int size;
} ARRAY;

int createArray(ARRAY *a, int size)
{
    int i;

    if (size <= 0)
    {
        printf("Array size must be greater than zero.\n");
        return 0;
    }

    a->arr = (int *)malloc(size * sizeof(int));

    if (a->arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 0;
    }

    a->size = size;

    for (i = 0; i < a->size; i++)
    {
        printf("Enter element %d: ", i + 1);

        if (scanf("%d", &a->arr[i]) != 1)
        {
            printf("Invalid input.\n");
            free(a->arr);
            a->arr = NULL;
            a->size = 0;
            return 0;
        }
    }

    return 1;
}

void displayArray(ARRAY *a)
{
    int i;

    if (a->size == 0)
    {
        printf("Array is empty.\n");
        return;
    }

    printf("Array elements: ");

    for (i = 0; i < a->size; i++)
    {
        printf("%d ", a->arr[i]);
    }

    printf("\n");
}

void insertAtPosition(ARRAY *a, int value, int position)
{
    int i;
    int *temp;

    if (position < 1 || position > a->size + 1)
    {
        printf("Invalid position.\n");
        return;
    }

    /*
       Store realloc() result in temp.
       If realloc fails, a->arr still points to the original allocated block.
    */
    temp = (int *)realloc(a->arr, (a->size + 1) * sizeof(int));

    if (temp == NULL)
    {
        printf("Memory reallocation failed.\n");
        return;
    }

    a->arr = temp;

    /* Shift elements right to make space at the required position. */
    for (i = a->size; i >= position; i--)
    {
        a->arr[i] = a->arr[i - 1];
    }

    a->arr[position - 1] = value;
    a->size++;

    printf("Element inserted successfully.\n");
}

void deleteAtPosition(ARRAY *a, int position)
{
    int i;
    int *temp;

    if (a->size == 0)
    {
        printf("Array is empty.\n");
        return;
    }

    if (position < 1 || position > a->size)
    {
        printf("Invalid position.\n");
        return;
    }

    printf("Deleted element = %d\n", a->arr[position - 1]);

    /* Shift all elements after the deleted position one place to the left. */
    for (i = position - 1; i < a->size - 1; i++)
    {
        a->arr[i] = a->arr[i + 1];
    }

    a->size--;

    if (a->size == 0)
    {
        free(a->arr);
        a->arr = NULL;
        return;
    }

    /*
       Shrinking is optional for correctness.
       If realloc fails here, the old block is still valid; logical size is
       already updated, so the remaining elements can still be used safely.
    */
    temp = (int *)realloc(a->arr, a->size * sizeof(int));

    if (temp != NULL)
        a->arr = temp;

    printf("Element deleted successfully.\n");
}

void secondLargest(ARRAY *a)
{
    int i;
    int largest;
    int second;
    int found = 0;

    if (a->size < 2)
    {
        printf("At least two distinct elements are required.\n");
        return;
    }

    largest = a->arr[0];

    for (i = 1; i < a->size; i++)
    {
        if (a->arr[i] > largest)
            largest = a->arr[i];
    }

    /*
       Find the greatest value strictly smaller than largest.
       This makes the result distinct even when the largest value repeats.
    */
    for (i = 0; i < a->size; i++)
    {
        if (a->arr[i] < largest)
        {
            if (!found || a->arr[i] > second)
            {
                second = a->arr[i];
                found = 1;
            }
        }
    }

    if (found)
        printf("Second-largest distinct element = %d\n", second);
    else
        printf("Second-largest distinct element does not exist.\n");
}

void removeDuplicates(ARRAY *a)
{
    int i;
    int j;
    int k;
    int duplicate;
    int *temp;

    if (a->size == 0)
    {
        printf("Array is empty.\n");
        return;
    }

    /*
       Keep the first occurrence of each value.
       For every element, check whether it has appeared earlier.
    */
    i = 0;

    while (i < a->size)
    {
        duplicate = 0;

        for (j = 0; j < i; j++)
        {
            if (a->arr[i] == a->arr[j])
            {
                duplicate = 1;
                break;
            }
        }

        if (duplicate)
        {
            for (k = i; k < a->size - 1; k++)
            {
                a->arr[k] = a->arr[k + 1];
            }

            a->size--;
        }
        else
        {
            i++;
        }
    }

    if (a->size == 0)
    {
        free(a->arr);
        a->arr = NULL;
    }
    else
    {
        temp = (int *)realloc(a->arr, a->size * sizeof(int));

        if (temp != NULL)
            a->arr = temp;
    }

    printf("Duplicate elements removed.\n");
}

void reverseDisplay(ARRAY *a)
{
    int i;

    if (a->size == 0)
    {
        printf("Array is empty.\n");
        return;
    }

    printf("Array in reverse order: ");

    for (i = a->size - 1; i >= 0; i--)
    {
        printf("%d ", a->arr[i]);
    }

    printf("\n");
}

void calculateAverage(ARRAY *a)
{
    int i;
    int sum = 0;

    if (a->size == 0)
    {
        printf("Array is empty. Average cannot be calculated.\n");
        return;
    }

    for (i = 0; i < a->size; i++)
    {
        sum += a->arr[i];
    }

    printf("Average = %.2f\n", (float)sum / a->size);
}

void freeArray(ARRAY *a)
{
    free(a->arr);
    a->arr = NULL;
    a->size = 0;
}

int main(void)
{
    ARRAY a;
    int choice;
    int value;
    int position;
    int initialized = 0;

    a.arr = NULL;
    a.size = 0;

    do
    {
        printf("\n----- DYNAMIC ARRAY OPERATIONS -----\n");
        printf("1. Create Array\n");
        printf("2. Insert at Position\n");
        printf("3. Delete at Position\n");
        printf("4. Find Second-Largest Distinct Element\n");
        printf("5. Remove Duplicates\n");
        printf("6. Display in Reverse Order\n");
        printf("7. Calculate Average\n");
        printf("8. Display Array\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            if (initialized)
                freeArray(&a);
            return 1;
        }

        switch (choice)
        {
            case 1:
                if (initialized)
                {
                    printf("Array is already created.\n");
                    break;
                }

                printf("Enter array size: ");

                if (scanf("%d", &position) != 1)
                {
                    printf("Invalid input.\n");
                    return 1;
                }

                initialized = createArray(&a, position);

                if (initialized)
                    printf("Array created successfully.\n");

                break;

            case 2:
                if (!initialized)
                {
                    printf("Create array first.\n");
                    break;
                }

                printf("Enter value to insert: ");
                if (scanf("%d", &value) != 1)
                {
                    printf("Invalid input.\n");
                    freeArray(&a);
                    return 1;
                }

                printf("Enter position (1 to %d): ", a.size + 1);
                if (scanf("%d", &position) != 1)
                {
                    printf("Invalid input.\n");
                    freeArray(&a);
                    return 1;
                }

                insertAtPosition(&a, value, position);
                break;

            case 3:
                if (!initialized)
                {
                    printf("Create array first.\n");
                    break;
                }

                printf("Enter position to delete (1 to %d): ", a.size);
                if (scanf("%d", &position) != 1)
                {
                    printf("Invalid input.\n");
                    freeArray(&a);
                    return 1;
                }

                deleteAtPosition(&a, position);
                break;

            case 4:
                if (initialized)
                    secondLargest(&a);
                else
                    printf("Create array first.\n");
                break;

            case 5:
                if (initialized)
                    removeDuplicates(&a);
                else
                    printf("Create array first.\n");
                break;

            case 6:
                if (initialized)
                    reverseDisplay(&a);
                else
                    printf("Create array first.\n");
                break;

            case 7:
                if (initialized)
                    calculateAverage(&a);
                else
                    printf("Create array first.\n");
                break;

            case 8:
                if (initialized)
                    displayArray(&a);
                else
                    printf("Create array first.\n");
                break;

            case 0:
                printf("Program terminated.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    if (initialized)
        freeArray(&a);

    return 0;
}
