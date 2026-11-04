/*
    DAY 6 - Q1: BINARY SEARCH TREE (BST)

    Implement a Binary Search Tree.
    Add nodes to the left or right based on the node value.
    Implement Pre-order, In-order and Post-order traversals,
    Search and Delete operations.

    Menu options:
    Add, Search, Delete, PreOrder, InOrder, PostOrder and Exit.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} NODE;

NODE *createNode(int value);
NODE *addNode(NODE *root, int value);
NODE *searchNode(NODE *root, int value);
NODE *deleteNode(NODE *root, int value);
NODE *findMin(NODE *root);
void preOrder(NODE *root);
void inOrder(NODE *root);
void postOrder(NODE *root);

NODE *createNode(int value)
{
    NODE *newNode = (NODE *)malloc(sizeof(NODE));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

NODE *addNode(NODE *root, int value)
{
    if (root == NULL)
    {
        return createNode(value);
    }

    if (value < root->data)
    {
        root->left = addNode(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = addNode(root->right, value);
    }
    else
    {
        printf("Duplicate value is not allowed.\n");
    }

    return root;
}

NODE *searchNode(NODE *root, int value)
{
    if (root == NULL || root->data == value)
    {
        return root;
    }

    if (value < root->data)
    {
        return searchNode(root->left, value);
    }

    return searchNode(root->right, value);
}

NODE *findMin(NODE *root)
{
    while (root != NULL && root->left != NULL)
    {
        root = root->left;
    }

    return root;
}

NODE *deleteNode(NODE *root, int value)
{
    NODE *temp;

    if (root == NULL)
    {
        printf("Value not found.\n");
        return root;
    }

    if (value < root->data)
    {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = deleteNode(root->right, value);
    }
    else
    {
        /* Node has no child or only right child */
        if (root->left == NULL)
        {
            temp = root->right;
            free(root);
            return temp;
        }

        /* Node has only left child */
        if (root->right == NULL)
        {
            temp = root->left;
            free(root);
            return temp;
        }

        /* Node has two children */
        temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

void preOrder(NODE *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
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

void postOrder(NODE *root)
{
    if (root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

int main()
{
    NODE *root = NULL;
    NODE *result;
    int choice, value;

    do
    {
        printf("\n----- BINARY SEARCH TREE MENU -----\n");
        printf("1. Add Node\n");
        printf("2. Search Node\n");
        printf("3. Delete Node\n");
        printf("4. PreOrder Traversal\n");
        printf("5. InOrder Traversal\n");
        printf("6. PostOrder Traversal\n");
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
                root = addNode(root, value);
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
                    printf("%d found in BST.\n", value);
                else
                    printf("%d not found in BST.\n", value);
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
                printf("PreOrder: ");
                preOrder(root);
                printf("\n");
                break;

            case 5:
                printf("InOrder: ");
                inOrder(root);
                printf("\n");
                break;

            case 6:
                printf("PostOrder: ");
                postOrder(root);
                printf("\n");
                break;

            case 0:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    /* Free all remaining nodes */
    while (root != NULL)
    {
        root = deleteNode(root, root->data);
    }

    return 0;
}
