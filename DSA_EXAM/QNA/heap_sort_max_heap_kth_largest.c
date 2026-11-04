#include <stdio.h>
#include <stdlib.h>

/* Swap two array elements. */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * Restore the max-heap property for the subtree rooted at index i.
 * The comparison counter counts comparisons between array values.
 */
void heapify(int arr[], int n, int i, int *comparisons)
{
    int largest = i;
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;

    if (left < n)
    {
        (*comparisons)++;

        if (arr[left] > arr[largest])
            largest = left;
    }

    if (right < n)
    {
        (*comparisons)++;

        if (arr[right] > arr[largest])
            largest = right;
    }

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest, comparisons);
    }
}

/* Convert the complete binary tree into a max heap. */
void buildMaxHeap(int arr[], int n, int *comparisons)
{
    int i;

    for (i = (n / 2) - 1; i >= 0; i--)
        heapify(arr, n, i, comparisons);
}

/* Heap Sort produces ascending order using a max heap. */
void heapSort(int arr[], int n, int *comparisons, int *swaps)
{
    int i;

    buildMaxHeap(arr, n, comparisons);

    for (i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        (*swaps)++;

        /* Exclude the sorted element at the end of the array. */
        heapify(arr, i, 0, comparisons);
    }
}

void displayArray(int arr[], int n)
{
    int i;

    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\\n");
}

/* Display the array as levels of a binary heap. */
void displayHeapLevels(int arr[], int n)
{
    int i, level = 0, levelCount = 1;

    printf("\\nHeap tree level-wise:\\n");

    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
        levelCount--;

        if (levelCount == 0)
        {
            printf("\\n");
            level++;
            levelCount = 1 << level;
        }
    }

    if (n > 0 && levelCount != 1)
        printf("\\n");
}

/* Return the kth largest value from an already sorted ascending array. */
int findKthLargest(int arr[], int n, int k, int *answer)
{
    if (k < 1 || k > n)
        return 0;

    *answer = arr[n - k];
    return 1;
}

int main()
{
    int *arr;
    int n, i, choice, k, answer;
    int comparisons = 0, swaps = 0;

    printf("Enter number of elements: ");

    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid array size.\\n");
        return 1;
    }

    arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed.\\n");
        return 1;
    }

    printf("Enter %d elements: ", n);

    for (i = 0; i < n; i++)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            printf("Invalid element.\\n");
            free(arr);
            return 1;
        }
    }

    do
    {
        printf("\\n========== HEAP OPERATIONS ==========\\n");
        printf("1. Build max heap and display\\n");
        printf("2. Perform Heap Sort\\n");
        printf("3. Find kth largest (after sorting)\\n");
        printf("4. Display current array\\n");
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
                comparisons = 0;
                buildMaxHeap(arr, n, &comparisons);
                printf("Max heap array: ");
                displayArray(arr, n);
                displayHeapLevels(arr, n);
                printf("Value comparisons: %d\\n", comparisons);
                break;

            case 2:
                comparisons = 0;
                swaps = 0;
                heapSort(arr, n, &comparisons, &swaps);
                printf("Sorted array: ");
                displayArray(arr, n);
                printf("Value comparisons: %d\\n", comparisons);
                printf("Extraction swaps: %d\\n", swaps);
                break;

            case 3:
                printf("Enter k (1 means largest): ");

                if (scanf("%d", &k) != 1)
                {
                    printf("Invalid k value.\\n");
                    break;
                }

                printf("Sort the array first if it is not sorted.\\n");

                if (findKthLargest(arr, n, k, &answer))
                    printf("%dth largest value: %d\\n", k, answer);
                else
                    printf("Invalid k. Enter a value from 1 to %d.\\n", n);
                break;

            case 4:
                displayArray(arr, n);
                break;

            case 0:
                printf("Exiting program.\\n");
                break;

            default:
                printf("Invalid choice.\\n");
        }

    } while (choice != 0);

    free(arr);
    return 0;
}
