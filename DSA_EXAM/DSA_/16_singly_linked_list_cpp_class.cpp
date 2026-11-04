/*
    DAY 6 - Q3: SINGLY LINKED LIST USING C++ CLASS

    Implement a singly linked list using C++ class to store integer values.
    addNode() should insert a node only at the end.
    deleteNode() should delete only the last node.
    display() should display all nodes.
*/

#include <iostream>
using namespace std;

class LinkedList
{
private:
    struct Node
    {
        int data;
        Node *next;
    };

    Node *head;

public:
    LinkedList()
    {
        head = NULL;
    }

    void addNode()
    {
        int value;
        Node *newNode;
        Node *temp;

        cout << "Enter value: ";
        cin >> value;

        newNode = new Node;

        if (newNode == NULL)
        {
            cout << "Memory allocation failed." << endl;
            return;
        }

        newNode->data = value;
        newNode->next = NULL;

        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            temp = head;

            while (temp->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = newNode;
        }

        cout << value << " inserted successfully." << endl;
    }

    void deleteNode()
    {
        Node *temp;
        Node *prev;

        if (head == NULL)
        {
            cout << "Linked list is empty." << endl;
            return;
        }

        if (head->next == NULL)
        {
            cout << "Deleted node: " << head->data << endl;
            delete head;
            head = NULL;
            return;
        }

        temp = head;
        prev = NULL;

        while (temp->next != NULL)
        {
            prev = temp;
            temp = temp->next;
        }

        cout << "Deleted node: " << temp->data << endl;
        prev->next = NULL;
        delete temp;
    }

    void display()
    {
        Node *temp;

        if (head == NULL)
        {
            cout << "Linked list is empty." << endl;
            return;
        }

        temp = head;

        cout << "Linked list: ";
        while (temp != NULL)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }

        cout << "NULL" << endl;
    }

    ~LinkedList()
    {
        Node *temp;

        while (head != NULL)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main()
{
    LinkedList list;
    int choice;

    do
    {
        cout << "\n----- SINGLY LINKED LIST MENU -----" << endl;
        cout << "1. Add Node at End" << endl;
        cout << "2. Delete Last Node" << endl;
        cout << "3. Display" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                list.addNode();
                break;

            case 2:
                list.deleteNode();
                break;

            case 3:
                list.display();
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
