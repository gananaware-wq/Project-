/*
    DAY 5 - Q4: QUICK SORT

    Implement program to accept list of elements from user
    and sort them using quick sort algorithm.
*/

#include <stdio.h>
#include <stdlib.h>

void acceptArray(int arr[], int n);
void displayArray(int arr[], int n);
int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);

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

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    int j;
    int temp;

    for (j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;

            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    int pivotIndex;

    if (low < high)
    {
        pivotIndex = partition(arr, low, high);

        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
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

    quickSort(arr, 0, n - 1);

    printf("\nArray after sorting:\n");
    displayArray(arr, n);

    free(arr);

    return 0;
}
