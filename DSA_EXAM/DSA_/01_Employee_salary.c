/*
Q2. Create an employee structure with the following members empid, employee name, salary,
year of joining etc.
Accept the data for certain no. of employees and find their total, average, max, min salary.
Also find out the employees with maximum, minimum service, use a function to find service
for each employee element in the array.
*/

#include <stdio.h>

struct Employee
{
    int empid;
    char name[50];
    float salary;
    int year_of_joining;
};

int calculate_service(struct Employee e, int current_year);
void display_employee(struct Employee e);

int main()
{
    struct Employee emp[100];
    int n, i, current_year;
    float total_salary = 0, avg_salary;
    float max_salary, min_salary;
    int max_service, min_service;
    int max_salary_index = 0, min_salary_index = 0;
    int max_service_index = 0, min_service_index = 0;

    printf("Enter number of employees: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100)
    {
        printf("Invalid number of employees. Enter value between 1 and 100.\n");
        return 0;
    }

    printf("Enter current year: ");
    scanf("%d", &current_year);

    for (i = 0; i < n; i++)
    {
        printf("\nEnter details of employee %d\n", i + 1);

        printf("Enter employee ID: ");
        scanf("%d", &emp[i].empid);

        printf("Enter employee name: ");
        scanf(" %49[^\n]", emp[i].name);

        printf("Enter salary: ");
        scanf("%f", &emp[i].salary);

        printf("Enter year of joining: ");
        scanf("%d", &emp[i].year_of_joining);

        if (emp[i].year_of_joining > current_year)
        {
            printf("Invalid joining year. Enter the details again.\n");
            i--;
            continue;
        }

        total_salary = total_salary + emp[i].salary;
    }

    avg_salary = total_salary / n;

    max_salary = emp[0].salary;
    min_salary = emp[0].salary;

    max_service = calculate_service(emp[0], current_year);
    min_service = calculate_service(emp[0], current_year);

    for (i = 1; i < n; i++)
    {
        if (emp[i].salary > max_salary)
        {
            max_salary = emp[i].salary;
            max_salary_index = i;
        }

        if (emp[i].salary < min_salary)
        {
            min_salary = emp[i].salary;
            min_salary_index = i;
        }

        if (calculate_service(emp[i], current_year) > max_service)
        {
            max_service = calculate_service(emp[i], current_year);
            max_service_index = i;
        }

        if (calculate_service(emp[i], current_year) < min_service)
        {
            min_service = calculate_service(emp[i], current_year);
            min_service_index = i;
        }
    }

    printf("\nTotal salary = %.2f\n", total_salary);
    printf("Average salary = %.2f\n", avg_salary);

    printf("\nEmployee with maximum salary:\n");
    display_employee(emp[max_salary_index]);

    printf("\nEmployee with minimum salary:\n");
    display_employee(emp[min_salary_index]);

    printf("\nEmployee with maximum service (%d years):\n", max_service);
    display_employee(emp[max_service_index]);

    printf("\nEmployee with minimum service (%d years):\n", min_service);
    display_employee(emp[min_service_index]);

    return 0;
}

int calculate_service(struct Employee e, int current_year)
{
    return current_year - e.year_of_joining;
}

void display_employee(struct Employee e)
{
    printf("Employee ID: %d\n", e.empid);
    printf("Employee Name: %s\n", e.name);
    printf("Salary: %.2f\n", e.salary);
    printf("Year of Joining: %d\n", e.year_of_joining);
}
