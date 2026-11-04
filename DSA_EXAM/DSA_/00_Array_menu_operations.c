/*
DAY_1: ARRAY

Q1. Write a C/C++ program that declares an array of length N, containing integers between 1 and N.
Implement menu driven program using switch case for below mentioned functionalities.
(a) insert element at index
(b) delete element at index
(c) find min val
(d) find max val
(e) display array element
(f) reverse display array element
(g) search element in array
(h) array element count
(i) avg of all array element
(j) determine if array contains any duplicates.
(k) reverse array element
*/

#include <stdio.h>

#define MAX 100

int insert_element(int arr[], int index, int pos, int value, int n);
int delete_element(int arr[], int index, int pos);
int find_min(int arr[], int index);
int find_max(int arr[], int index);
int print_array(int arr[], int index);
int print_array_inrev(int arr[], int index);
int search_element(int arr[], int index, int value);
int count_element(int index);
float avg_element(int arr[], int index);
int check_duplicate(int arr[], int index);
int reverse_array(int arr[], int index);

int main()
{
    int arr[MAX];
    int index = 0;
    int n, i, choice, value, pos;

    printf("Enter size of array N (max %d) -> ", MAX);
    scanf("%d", &n);

    if(n <= 0 || n > MAX)
    {
        printf("Invalid size\n");
        return 0;
    }

    for(i = 0; i < n; i++)
    {
        printf("Enter element %d (between 1 and %d) -> ", i+1, n);
        scanf("%d", &value);

        if(value < 1 || value > n)
        {
            printf("Element must be between 1 and %d, try again.\n", n);
            i--;
        }
        else
        {
            arr[index++] = value;
        }
    }

    printf("\n\n");

    do{
        printf("1.insert element at index\n");
        printf("2.delete element at index\n");
        printf("3.find min value\n");
        printf("4.find max value\n");
        printf("5.display array element\n");
        printf("6.display array element in reverse order\n");
        printf("7.search element in array\n");
        printf("8.array element count\n");
        printf("9.average of all array element\n");
        printf("10.determine if array contains any duplicates\n");
        printf("11.reverse array element\n");
        printf("0.Enter 0 to exit..\n");
        printf("Enter your choice -> ");
        scanf("%d", &choice);
        printf("\n");

        switch(choice)
        {
            case 1: printf("Enter index and value -> ");
                    scanf("%d %d", &pos, &value);
                    index = insert_element(arr, index, pos, value, n);
                    break;

            case 2: printf("Enter index -> ");
                    scanf("%d", &pos);
                    index = delete_element(arr, index, pos);
                    break;

            case 3: find_min(arr, index);
                    break;

            case 4: find_max(arr, index);
                    break;

            case 5: print_array(arr, index);
                    break;

            case 6: print_array_inrev(arr, index);
                    break;

            case 7: printf("Enter element to search -> ");
                    scanf("%d", &value);
                    if(search_element(arr, index, value) == 0)
                    {
                        printf("Entered element is not present in array.\n");
                    }
                    break;

            case 8: printf("Total number of elements in array are %d.\n", count_element(index));
                    break;

            case 9: if(index == 0)
                    {
                        printf("There are no elements in array.\n");
                    }
                    else
                    {
                        printf("Average of array elements is %.2f\n", avg_element(arr, index));
                    }
                    break;

            case 10: if(check_duplicate(arr, index) == 1)
                     {
                         printf("Array contains duplicate elements.\n");
                     }
                     else
                     {
                         printf("Array does not contain any duplicate elements.\n");
                     }
                     break;

            case 11: reverse_array(arr, index);
                     break;

            case 0: printf("Exiting...\n");
                    break;

            default: printf("Invalid choice\n");
        }

        printf("\n");
    }while(choice != 0);

    return 0;
}

int insert_element(int arr[], int index, int pos, int value, int n)
{
    int i;

    if(index == MAX)
    {
        printf("Array is full can not insert %d\n", value);
        return index;
    }

    if(pos < 0 || pos > index)
    {
        printf("Enter valid index you are out of range.\n");
        return index;
    }

    if(value < 1 || value > n)
    {
        printf("Element must be between 1 and %d.\n", n);
        return index;
    }

    for(i = index; i > pos; i--)
    {
        arr[i] = arr[i-1];
    }

    arr[pos] = value;
    printf("Element %d inserted at %d index.\n", value, pos);

    return index+1;
}

int delete_element(int arr[], int index, int pos)
{
    int i;

    if(index == 0)
    {
        printf("There are no elements in array.\n");
        return index;
    }

    if(pos < 0 || pos >= index)
    {
        printf("Enter valid index you are out of range.\n");
        return index;
    }

    printf("Element %d deleted from %d index.\n", arr[pos], pos);

    for(i = pos; i < index-1; i++)
    {
        arr[i] = arr[i+1];
    }

    return index-1;
}

int find_min(int arr[], int index)
{
    int i, min;

    if(index == 0)
    {
        printf("There are no elements in array.\n");
        return 0;
    }

    min = arr[0];

    for(i = 1; i < index; i++)
    {
        if(arr[i] < min)
        {
            min = arr[i];
        }
    }

    printf("Minimum value in array is %d.\n", min);
    return min;
}

int find_max(int arr[], int index)
{
    int i, max;

    if(index == 0)
    {
        printf("There are no elements in array.\n");
        return 0;
    }

    max = arr[0];

    for(i = 1; i < index; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
        }
    }

    printf("Maximum value in array is %d.\n", max);
    return max;
}

int print_array(int arr[], int index)
{
    int i;

    if(index <= 0)
    {
        printf("There are no elements in array.\n");
    }
    else
    {
        printf("Printing Array\n");
        for(i = 0; i < index; i++)
        {
            printf("%d\t", arr[i]);
        }
        printf("\n");
    }

    return 0;
}

int print_array_inrev(int arr[], int index)
{
    int i;

    if(index <= 0)
    {
        printf("There are no elements in array.\n");
    }
    else
    {
        printf("Printing Array in reverse order\n");
        for(i = index-1; i >= 0; i--)
        {
            printf("%d\t", arr[i]);
        }
        printf("\n");
    }

    return 0;
}

int search_element(int arr[], int index, int value)
{
    int i, flag = 0;

    for(i = 0; i < index; i++)
    {
        if(arr[i] == value)
        {
            printf("Element %d found at %d index.\n", value, i);
            flag = 1;
        }
    }

    return flag;
}

int count_element(int index)
{
    return index;
}

float avg_element(int arr[], int index)
{
    int i, sum = 0;

    for(i = 0; i < index; i++)
    {
        sum = sum + arr[i];
    }

    return (float)sum/index;
}

int check_duplicate(int arr[], int index)
{
    int i, j;

    for(i = 0; i < index; i++)
    {
        for(j = i+1; j < index; j++)
        {
            if(arr[i] == arr[j])
            {
                return 1;
            }
        }
    }

    return 0;
}

int reverse_array(int arr[], int index)
{
    int i, temp;

    if(index <= 0)
    {
        printf("There are no elements in array.\n");
        return 0;
    }

    for(i = 0; i < index/2; i++)
    {
        temp = arr[i];
        arr[i] = arr[index-1-i];
        arr[index-1-i] = temp;
    }

    printf("Array reversed successfully.\n");
    return 0;
}
