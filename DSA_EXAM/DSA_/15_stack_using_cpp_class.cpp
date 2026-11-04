/*
    DAY 6 - Q2: INTEGER STACK USING C++ CLASS

    Implement an integer Stack using C++ class with the following
    operations:
    Push(), Pop(), display(), initStack(), isEmpty() and isFull().
*/

#include <iostream>
using namespace std;

class Stack
{
private:
    int size;
    int tos;
    int *stack;

public:
    Stack()
    {
        size = 0;
        tos = -1;
        stack = NULL;
    }

    void initStack()
    {
        int newSize;

        cout << "Enter stack size: ";
        cin >> newSize;

        if (newSize <= 0)
        {
            cout << "Invalid stack size." << endl;
            return;
        }

        int *temp = new int[newSize];

        if (temp == NULL)
        {
            cout << "Memory allocation failed." << endl;
            return;
        }

        delete[] stack;

        stack = temp;
        size = newSize;
        tos = -1;

        cout << "Stack initialized successfully." << endl;
    }

    bool isEmpty()
    {
        return tos == -1;
    }

    bool isFull()
    {
        return tos == size - 1;
    }

    void Push()
    {
        int value;

        if (stack == NULL)
        {
            cout << "Please initialize the stack first." << endl;
            return;
        }

        if (isFull())
        {
            cout << "Stack is full." << endl;
            return;
        }

        cout << "Enter value: ";
        cin >> value;

        tos++;
        stack[tos] = value;

        cout << value << " pushed into stack." << endl;
    }

    void Pop()
    {
        if (stack == NULL || isEmpty())
        {
            cout << "Stack is empty." << endl;
            return;
        }

        cout << "Popped element: " << stack[tos] << endl;
        tos--;
    }

    void display()
    {
        int i;

        if (stack == NULL || isEmpty())
        {
            cout << "Stack is empty." << endl;
            return;
        }

        cout << "Stack elements (Top to Bottom): ";
        for (i = tos; i >= 0; i--)
        {
            cout << stack[i] << " ";
        }
        cout << endl;
    }

    ~Stack()
    {
        delete[] stack;
    }
};

int main()
{
    Stack s;
    int choice;

    do
    {
        cout << "\n----- STACK MENU -----" << endl;
        cout << "1. Initialize Stack" << endl;
        cout << "2. Push" << endl;
        cout << "3. Pop" << endl;
        cout << "4. Display" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                s.initStack();
                break;

            case 2:
                s.Push();
                break;

            case 3:
                s.Pop();
                break;

            case 4:
                s.display();
                break;

            case 0:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice." << endl;
        }

    } while (choice != 0);

    return 0;
}
