/*
Q1. Write menu driven program consisting multiple sort methods.
Accept length of array from user at runtime. Allocate memory for array at runtime.
Using accept() get random values for array from user.
Display() must print values on terminal.
Using switch case ask user which sort method he wants to use.
Implement Bubble sort, insertion sort, selection sort using functions.
*/

#include <stdio.h>
#include <stdlib.h>

void accept(int *Arr, int index);
void display(int *Arr, int index);
void bubble_sort(int *Arr, int index);
void insertion_sort(int *Arr, int index);
void selection_sort(int *Arr, int index);

int main()
{
    int N, choice;
    int *Aptr;

    printf("Enter length of array: ");
    scanf("%d", &N);

    while(N < 1)
    {
        printf("Invalid input. Enter length again: ");
        scanf("%d", &N);
    }

    Aptr = (int *)malloc(N * sizeof(int));

    if(Aptr == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("\nArray created successfully.\n");

    accept(Aptr, N);
    display(Aptr, N);

    do
    {
        printf("\n----------- MENU -----------\n");
        printf("1. Bubble Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Selection Sort\n");
        printf("4. Display Array\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                bubble_sort(Aptr, N);
                display(Aptr, N);
                break;

            case 2:
                insertion_sort(Aptr, N);
                display(Aptr, N);
                break;

            case 3:
                selection_sort(Aptr, N);
                display(Aptr, N);
                break;

            case 4:
                display(Aptr, N);
                break;

            case 5:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
                break;
        }

    } while(choice != 5);

    free(Aptr);
    return 0;
}

void accept(int *Arr, int index)
{
    int i;

    printf("\nEnter array elements one by one:\n");

    for(i = 0; i < index; i++)
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &Arr[i]);
    }
}

void display(int *Arr, int index)
{
    int i;

    printf("\nArray: { ");

    for(i = 0; i < index; i++)
    {
        printf("%d ", Arr[i]);
    }

    printf("}\n");
}

void bubble_sort(int *Arr, int index)
{
    int i, pass, swapped, temp;

    for(pass = 0; pass < index - 1; pass++)
    {
        swapped = 0;

        for(i = 0; i < index - 1 - pass; i++)
        {
            if(Arr[i] > Arr[i + 1])
            {
                temp = Arr[i];
                Arr[i] = Arr[i + 1];
                Arr[i + 1] = temp;
                swapped = 1;
            }
        }

        if(swapped == 0)
        {
            break;
        }
    }

    printf("\nArray sorted using Bubble Sort.\n");
}

void insertion_sort(int *Arr, int index)
{
    int i, j, key;

    for(i = 1; i < index; i++)
    {
        key = Arr[i];
        j = i - 1;

        while(j >= 0 && Arr[j] > key)
        {
            Arr[j + 1] = Arr[j];
            j--;
        }

        Arr[j + 1] = key;
    }

    printf("\nArray sorted using Insertion Sort.\n");
}

void selection_sort(int *Arr, int index)
{
    int i, j, min, temp;

    for(i = 0; i < index - 1; i++)
    {
        min = i;

        for(j = i + 1; j < index; j++)
        {
            if(Arr[j] < Arr[min])
            {
                min = j;
            }
        }

        if(min != i)
        {
            temp = Arr[i];
            Arr[i] = Arr[min];
            Arr[min] = temp;
        }
    }

    printf("\nArray sorted using Selection Sort.\n");
}
