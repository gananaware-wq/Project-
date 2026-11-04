/*
    DAY 7 - Q1: AVL TREE

    Implement an AVL tree with the following operations:
    - Insert a node and balance the tree.
    - Search for a value.
    - Delete a node and balance the tree.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    int height;
    struct node *left;
    struct node *right;
} NODE;

int max(int a, int b);
int height(NODE *root);
int getBalance(NODE *root);
NODE *createNode(int value);
NODE *rightRotate(NODE *y);
NODE *leftRotate(NODE *x);
NODE *insertNode(NODE *root, int value);
NODE *searchNode(NODE *root, int value);
NODE *findMin(NODE *root);
NODE *deleteNode(NODE *root, int value);
void inOrder(NODE *root);
void freeTree(NODE *root);

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(NODE *root)
{
    if (root == NULL)
        return 0;

    return root->height;
}

int getBalance(NODE *root)
{
    if (root == NULL)
        return 0;

    return height(root->left) - height(root->right);
}

NODE *createNode(int value)
{
    NODE *newNode = (NODE *)malloc(sizeof(NODE));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    newNode->data = value;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

NODE *rightRotate(NODE *y)
{
    NODE *x = y->left;
    NODE *temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

NODE *leftRotate(NODE *x)
{
    NODE *y = x->right;
    NODE *temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

NODE *insertNode(NODE *root, int value)
{
    int balance;

    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insertNode(root->left, value);
    else if (value > root->data)
        root->right = insertNode(root->right, value);
    else
    {
        printf("Duplicate value is not allowed.\n");
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));
    balance = getBalance(root);

    /* Left Left case */
    if (balance > 1 && value < root->left->data)
        return rightRotate(root);

    /* Right Right case */
    if (balance < -1 && value > root->right->data)
        return leftRotate(root);

    /* Left Right case */
    if (balance > 1 && value > root->left->data)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    /* Right Left case */
    if (balance < -1 && value < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

NODE *searchNode(NODE *root, int value)
{
    if (root == NULL || root->data == value)
        return root;

    if (value < root->data)
        return searchNode(root->left, value);

    return searchNode(root->right, value);
}

NODE *findMin(NODE *root)
{
    NODE *temp = root;

    while (temp != NULL && temp->left != NULL)
        temp = temp->left;

    return temp;
}

NODE *deleteNode(NODE *root, int value)
{
    NODE *temp;
    int balance;

    if (root == NULL)
        return root;

    if (value < root->data)
        root->left = deleteNode(root->left, value);
    else if (value > root->data)
        root->right = deleteNode(root->right, value);
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            temp = (root->left != NULL) ? root->left : root->right;

            if (temp == NULL)
            {
                free(root);
                return NULL;
            }
            else
            {
                *root = *temp;
                free(temp);
            }
        }
        else
        {
            temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    root->height = 1 + max(height(root->left), height(root->right));
    balance = getBalance(root);

    /* Left Left case */
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    /* Left Right case */
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    /* Right Right case */
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    /* Right Left case */
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inOrder(NODE *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void freeTree(NODE *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main()
{
    NODE *root = NULL;
    NODE *result;
    int choice, value;

    do
    {
        printf("\n----- AVL TREE MENU -----\n");
        printf("1. Insert Node\n");
        printf("2. Search Node\n");
        printf("3. Delete Node\n");
        printf("4. Display (InOrder)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            break;
        }

        switch (choice)
        {
            case 1:
                printf("Enter value to insert: ");
                if (scanf("%d", &value) != 1)
                {
                    printf("Invalid input.\n");
                    break;
                }
                root = insertNode(root, value);
                break;

            case 2:
                printf("Enter value to search: ");
                if (scanf("%d", &value) != 1)
                {
                    printf("Invalid input.\n");
                    break;
                }

                result = searchNode(root, value);

                if (result != NULL)
                    printf("%d found in AVL tree.\n", value);
                else
                    printf("%d not found in AVL tree.\n", value);
                break;

            case 3:
                printf("Enter value to delete: ");
                if (scanf("%d", &value) != 1)
                {
                    printf("Invalid input.\n");
                    break;
                }

                if (searchNode(root, value) == NULL)
                    printf("Value not found.\n");
                else
                {
                    root = deleteNode(root, value);
                    printf("Node deleted successfully.\n");
                }
                break;

            case 4:
                printf("AVL tree (InOrder): ");
                inOrder(root);
                printf("\n");
                break;

            case 0:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    freeTree(root);

    return 0;
}
