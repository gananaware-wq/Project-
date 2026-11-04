/*
    DAY 7 - Q2: HEAP SORT

    Implement Heap Sort to sort unsorted elements using heapify.
*/

#include <stdio.h>
#include <stdlib.h>

void acceptArray(int arr[], int n);
void displayArray(int arr[], int n);
void heapify(int arr[], int n, int i);
void heapSort(int arr[], int n);

void acceptArray(int arr[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
}

void displayArray(int arr[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;
    int temp;

    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    int i;
    int temp;

    /* Build a max heap */
    for (i = (n / 2) - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    /* Move the largest element to the end one by one */
    for (i = n - 1; i > 0; i--)
    {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

int main()
{
    int n;
    int *arr;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid array size.\n");
        return 1;
    }

    arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter array elements:\n");
    acceptArray(arr, n);

    printf("\nArray before sorting:\n");
    displayArray(arr, n);

    heapSort(arr, n);

    printf("\nArray after Heap Sort:\n");
    displayArray(arr, n);

    free(arr);

    return 0;
}
