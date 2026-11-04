/*
    DAY 5 - Q3: MERGE SORT

    Implement program to accept two list of elements from user
    and sort them using merge sort algorithm.
*/

#include <stdio.h>
#include <stdlib.h>

void acceptArray(int arr[], int n);
void displayArray(int arr[], int n);
void merge(int arr[], int low, int mid, int high);
void mergeSort(int arr[], int low, int high);

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

void merge(int arr[], int low, int mid, int high)
{
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int *left = (int *)malloc(n1 * sizeof(int));
    int *right = (int *)malloc(n2 * sizeof(int));

    if (left == NULL || right == NULL)
    {
        printf("Memory allocation failed.\n");
        free(left);
        free(right);
        exit(1);
    }

    for (i = 0; i < n1; i++)
        left[i] = arr[low + i];

    for (j = 0; j < n2; j++)
        right[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = low;

    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = right[j];
        j++;
        k++;
    }

    free(left);
    free(right);
}

void mergeSort(int arr[], int low, int high)
{
    int mid;

    if (low < high)
    {
        mid = (low + high) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

int main()
{
    int n1, n2;
    int *arr1, *arr2;

    printf("Enter number of elements in first list: ");
    scanf("%d", &n1);

    if (n1 <= 0)
    {
        printf("Invalid size for first list.\n");
        return 1;
    }

    arr1 = (int *)malloc(n1 * sizeof(int));

    if (arr1 == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("\nEnter elements of first list:\n");
    acceptArray(arr1, n1);

    printf("\nEnter number of elements in second list: ");
    scanf("%d", &n2);

    if (n2 <= 0)
    {
        printf("Invalid size for second list.\n");
        free(arr1);
        return 1;
    }

    arr2 = (int *)malloc(n2 * sizeof(int));

    if (arr2 == NULL)
    {
        printf("Memory allocation failed.\n");
        free(arr1);
        return 1;
    }

    printf("\nEnter elements of second list:\n");
    acceptArray(arr2, n2);

    mergeSort(arr1, 0, n1 - 1);
    mergeSort(arr2, 0, n2 - 1);

    printf("\nFirst list after sorting:\n");
    displayArray(arr1, n1);

    printf("\nSecond list after sorting:\n");
    displayArray(arr2, n2);

    free(arr1);
    free(arr2);

    return 0;
}
