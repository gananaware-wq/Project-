/*
    Question 5: Advanced Sorting Analysis
    File: sorting_comparison_swap_count.c

    Features:
    1. Bubble Sort with early termination
    2. Selection Sort
    3. Insertion Sort
    4. Quick Sort using last element as pivot
    5. Ascending / descending order
    6. Count comparisons and data movements for each algorithm
    7. Preserve original array so every algorithm gets the same input

    Counting rule:
    - comparisons: number of key-to-key comparisons
    - movements: number of array assignments/swaps performed by the algorithm
      (a swap is counted as 3 movements; an insertion shift is 1 movement)
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct ARRAY
{
    int *arr;
    int size;
} ARRAY;

typedef struct SORTCOUNT
{
    long comparisons;
    long movements;
} SORTCOUNT;

int createArray(ARRAY *a)
{
    int i;

    printf("Enter number of elements: ");
    if (scanf("%d", &a->size) != 1 || a->size <= 0)
    {
        printf("Invalid size.\n");
        return 0;
    }

    a->arr = (int *)malloc(a->size * sizeof(int));
    if (a->arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 0;
    }

    printf("Enter %d elements:\n", a->size);
    for (i = 0; i < a->size; i++)
    {
        if (scanf("%d", &a->arr[i]) != 1)
        {
            printf("Invalid input.\n");
            free(a->arr);
            a->arr = NULL;
            return 0;
        }
    }

    return 1;
}

void displayArray(int arr[], int size)
{
    int i;

    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

void copyArray(int source[], int destination[], int size)
{
    int i;

    for (i = 0; i < size; i++)
        destination[i] = source[i];
}

int shouldSwap(int first, int second, int order)
{
    if (order == 1)
        return first > second;       /* ascending */

    return first < second;           /* descending */
}

void swap(int *a, int *b, SORTCOUNT *count)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;

    count->movements += 3;
}

void bubbleSort(int arr[], int size, int order, SORTCOUNT *count)
{
    int i, j, swapped;

    for (i = 0; i < size - 1; i++)
    {
        swapped = 0;

        for (j = 0; j < size - 1 - i; j++)
        {
            count->comparisons++;

            if (shouldSwap(arr[j], arr[j + 1], order))
            {
                swap(&arr[j], &arr[j + 1], count);
                swapped = 1;
            }
        }

        /* If no swap occurred, the array is already sorted. */
        if (swapped == 0)
            break;
    }
}

void selectionSort(int arr[], int size, int order, SORTCOUNT *count)
{
    int i, j, selected;

    for (i = 0; i < size - 1; i++)
    {
        selected = i;

        for (j = i + 1; j < size; j++)
        {
            count->comparisons++;

            if (shouldSwap(arr[selected], arr[j], order))
                selected = j;
        }

        if (selected != i)
            swap(&arr[i], &arr[selected], count);
    }
}

void insertionSort(int arr[], int size, int order, SORTCOUNT *count)
{
    int i, j, key;

    for (i = 1; i < size; i++)
    {
        key = arr[i];
        j = i - 1;

        /*
           Shift elements until the correct position for key is found.
           Each key comparison is counted, including the final failed
           comparison when j is still within the array.
        */
        while (j >= 0)
        {
            count->comparisons++;

            if (shouldSwap(arr[j], key, order))
            {
                arr[j + 1] = arr[j];
                count->movements++;
                j--;
            }
            else
            {
                break;
            }
        }

        arr[j + 1] = key;
        count->movements++;
    }
}

int partition(int arr[], int low, int high, int order, SORTCOUNT *count)
{
    int pivot, i, j;

    pivot = arr[high];
    i = low - 1;

    for (j = low; j < high; j++)
    {
        count->comparisons++;

        /*
           Move values that belong before the pivot into the left region.
           The order flag makes the same partition logic work both ways.
        */
        if (!shouldSwap(arr[j], pivot, order))
        {
            i++;

            if (i != j)
                swap(&arr[i], &arr[j], count);
        }
    }

    if (i + 1 != high)
        swap(&arr[i + 1], &arr[high], count);

    return i + 1;
}

void quickSort(int arr[], int low, int high, int order, SORTCOUNT *count)
{
    int pivotIndex;

    if (low < high)
    {
        pivotIndex = partition(arr, low, high, order, count);

        quickSort(arr, low, pivotIndex - 1, order, count);
        quickSort(arr, pivotIndex + 1, high, order, count);
    }
}

void printResult(char name[], int arr[], int size, SORTCOUNT count)
{
    printf("\n%s\n", name);
    printf("Sorted array : ");
    displayArray(arr, size);
    printf("Comparisons  : %ld\n", count.comparisons);
    printf("Movements    : %ld\n", count.movements);
}

void runAllSorts(ARRAY *original, int order)
{
    int *work;
    SORTCOUNT count;

    work = (int *)malloc(original->size * sizeof(int));
    if (work == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    copyArray(original->arr, work, original->size);
    count.comparisons = 0;
    count.movements = 0;
    bubbleSort(work, original->size, order, &count);
    printResult("1. Bubble Sort", work, original->size, count);

    copyArray(original->arr, work, original->size);
    count.comparisons = 0;
    count.movements = 0;
    selectionSort(work, original->size, order, &count);
    printResult("2. Selection Sort", work, original->size, count);

    copyArray(original->arr, work, original->size);
    count.comparisons = 0;
    count.movements = 0;
    insertionSort(work, original->size, order, &count);
    printResult("3. Insertion Sort", work, original->size, count);

    copyArray(original->arr, work, original->size);
    count.comparisons = 0;
    count.movements = 0;
    quickSort(work, 0, original->size - 1, order, &count);
    printResult("4. Quick Sort (last element pivot)", work, original->size, count);

    free(work);
}

int main()
{
    ARRAY a;
    int choice;

    a.arr = NULL;
    a.size = 0;

    if (!createArray(&a))
        return 1;

    printf("\nOriginal array: ");
    displayArray(a.arr, a.size);

    printf("\nSelect sorting order:\n");
    printf("1. Ascending\n");
    printf("2. Descending\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2))
    {
        printf("Invalid choice.\n");
        free(a.arr);
        return 1;
    }

    runAllSorts(&a, choice);

    free(a.arr);
    return 0;
}
