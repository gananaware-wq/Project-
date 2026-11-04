/*
Q3. Write C/C++ program which allocate and deallocate memory dynamically.

(a) Allocating 1D array dynamically and access the elements.

(b) Allocating 2D array dynamically:
    (1) Contiguous rows with fixed number of columns.
    (2) Non-contiguous rows with variable number of columns.

(c) Allocate memory for array of structure variables dynamically and
    access members of each element.
*/

#include <stdio.h>
#include <stdlib.h>

struct Student
{
    int rollno;
    char name[50];
    float marks;
};

int main()
{
    int n, i, j;
    int rows, cols;
    int *arr;
    int *arr2;
    int **arr3;
    int *col;
    struct Student *s;

    /* (a) Dynamic allocation of 1D array */

    printf("Enter number of elements for 1D array: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid size.\n");
        return 0;
    }

    arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 0;
    }

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("1D array elements are:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    arr = NULL;

    /* (b-1) 2D array: contiguous rows with fixed columns */

    printf("\nEnter number of rows for contiguous 2D array: ");
    scanf("%d", &rows);

    printf("Enter number of columns: ");
    scanf("%d", &cols);

    if (rows <= 0 || cols <= 0)
    {
        printf("Invalid row or column size.\n");
        return 0;
    }

    arr2 = (int *)malloc(rows * cols * sizeof(int));

    if (arr2 == NULL)
    {
        printf("Memory allocation failed.\n");
        return 0;
    }

    printf("Enter elements of 2D array:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            scanf("%d", &arr2[i * cols + j]);
        }
    }

    printf("Contiguous 2D array elements are:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%d ", arr2[i * cols + j]);
        }
        printf("\n");
    }

    free(arr2);
    arr2 = NULL;

    /* (b-2) 2D array: non-contiguous rows with variable columns */

    printf("\nEnter number of rows for non-contiguous 2D array: ");
    scanf("%d", &rows);

    if (rows <= 0)
    {
        printf("Invalid number of rows.\n");
        return 0;
    }

    arr3 = (int **)malloc(rows * sizeof(int *));
    col = (int *)malloc(rows * sizeof(int));

    if (arr3 == NULL || col == NULL)
    {
        printf("Memory allocation failed.\n");
        free(arr3);
        free(col);
        return 0;
    }

    for (i = 0; i < rows; i++)
    {
        printf("Enter number of columns for row %d: ", i + 1);
        scanf("%d", &col[i]);

        if (col[i] <= 0)
        {
            printf("Invalid number of columns.\n");
            for (j = 0; j < i; j++)
            {
                free(arr3[j]);
            }
            free(arr3);
            free(col);
            return 0;
        }

        arr3[i] = (int *)malloc(col[i] * sizeof(int));

        if (arr3[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            for (j = 0; j < i; j++)
            {
                free(arr3[j]);
            }
            free(arr3);
            free(col);
            return 0;
        }
    }

    printf("Enter elements row by row:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < col[i]; j++)
        {
            scanf("%d", &arr3[i][j]);
        }
    }

    printf("Non-contiguous 2D array elements are:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < col[i]; j++)
        {
            printf("%d ", arr3[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < rows; i++)
    {
        free(arr3[i]);
    }
    free(arr3);
    free(col);

    /* (c) Dynamic allocation of array of structures */

    printf("\nEnter number of students: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of students.\n");
        return 0;
    }

    s = (struct Student *)malloc(n * sizeof(struct Student));

    if (s == NULL)
    {
        printf("Memory allocation failed.\n");
        return 0;
    }

    for (i = 0; i < n; i++)
    {
        printf("\nEnter details of student %d\n", i + 1);

        printf("Enter roll number: ");
        scanf("%d", &s[i].rollno);

        printf("Enter name: ");
        scanf(" %49[^\n]", s[i].name);

        printf("Enter marks: ");
        scanf("%f", &s[i].marks);
    }

    printf("\nStudent details are:\n");
    for (i = 0; i < n; i++)
    {
        printf("\nRoll number: %d\n", s[i].rollno);
        printf("Name: %s\n", s[i].name);
        printf("Marks: %.2f\n", s[i].marks);
    }

    free(s);
    s = NULL;

    return 0;
}
