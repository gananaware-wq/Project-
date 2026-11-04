/*
    Question 6: Binary Search Tree - Advanced Operations
    File: bst_delete_kth_smallest_validate.c

    Requirements:
    1. Insert values into a Binary Search Tree (duplicates are ignored).
    2. Search for a value.
    3. Delete a value using all three BST deletion cases.
    4. Display inorder, preorder and postorder traversals.
    5. Find the height of the tree.
    6. Count leaf nodes and total nodes.
    7. Find the Kth smallest element.
    8. Validate whether the tree follows BST rules.

    Note:
    - Height is measured in number of nodes on the longest path.
    - The smallest element has position K = 1.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct NODE
{
    int data;
    struct NODE *left;
    struct NODE *right;
} NODE;

NODE *createNode(int data)
{
    NODE *newNode;

    newNode = (NODE *)malloc(sizeof(NODE));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

NODE *insertNode(NODE *root, int data)
{
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insertNode(root->left, data);
    else if (data > root->data)
        root->right = insertNode(root->right, data);
    else
        printf("Duplicate value %d ignored.\n", data);

    return root;
}

NODE *searchNode(NODE *root, int key)
{
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return searchNode(root->left, key);

    return searchNode(root->right, key);
}

NODE *findMinimum(NODE *root)
{
    if (root == NULL)
        return NULL;

    while (root->left != NULL)
        root = root->left;

    return root;
}

NODE *deleteNode(NODE *root, int key)
{
    NODE *temp;
    NODE *successor;

    if (root == NULL)
        return NULL;

    if (key < root->data)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        /* Case 1: Node has no child. */
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }

        /* Case 2: Node has exactly one child. */
        if (root->left == NULL)
        {
            temp = root->right;
            free(root);
            return temp;
        }

        if (root->right == NULL)
        {
            temp = root->left;
            free(root);
            return temp;
        }

        /*
           Case 3: Node has two children.
           Copy inorder successor (smallest value in right subtree),
           then delete that successor from the right subtree.
        */
        successor = findMinimum(root->right);
        root->data = successor->data;
        root->right = deleteNode(root->right, successor->data);
    }

    return root;
}

void inorder(NODE *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(NODE *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(NODE *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int treeHeight(NODE *root)
{
    int leftHeight, rightHeight;

    if (root == NULL)
        return 0;

    leftHeight = treeHeight(root->left);
    rightHeight = treeHeight(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int countNodes(NODE *root)
{
    if (root == NULL)
        return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeafNodes(NODE *root)
{
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 1;

    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

/*
   Inorder traversal visits BST values in ascending order.
   This function stops as soon as the Kth value is reached.
*/
void findKthSmallest(NODE *root, int k, int *visited, int *answer)
{
    if (root == NULL || *visited >= k)
        return;

    findKthSmallest(root->left, k, visited, answer);

    if (*visited < k)
    {
        (*visited)++;

        if (*visited == k)
        {
            *answer = root->data;
            return;
        }
    }

    findKthSmallest(root->right, k, visited, answer);
}

/*
   Use a lower and upper bound for every node.
   Long long bounds allow INT_MIN and INT_MAX as valid node values.
*/
int isValidBSTUtil(NODE *root, long long minimum, long long maximum)
{
    if (root == NULL)
        return 1;

    if (root->data <= minimum || root->data >= maximum)
        return 0;

    return isValidBSTUtil(root->left, minimum, root->data) &&
           isValidBSTUtil(root->right, root->data, maximum);
}

int isValidBST(NODE *root)
{
    return isValidBSTUtil(root, LLONG_MIN, LLONG_MAX);
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

void displayTreeDetails(NODE *root)
{
    printf("\nInorder   : ");
    inorder(root);

    printf("\nPreorder  : ");
    preorder(root);

    printf("\nPostorder : ");
    postorder(root);

    printf("\nTotal nodes     : %d", countNodes(root));
    printf("\nLeaf nodes      : %d", countLeafNodes(root));
    printf("\nHeight (nodes)  : %d", treeHeight(root));
    printf("\nBST validation  : %s\n", isValidBST(root) ? "Valid" : "Invalid");
}

int main()
{
    NODE *root = NULL;
    NODE *found;
    int choice, value, k;
    int visited, answer;

    do
    {
        printf("\n\n--- BINARY SEARCH TREE ---\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display traversals and tree details\n");
        printf("5. Find Kth smallest element\n");
        printf("6. Validate BST\n");
        printf("0. Exit\n");
        printf("Enter choice: ");

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
                    freeTree(root);
                    return 1;
                }

                root = insertNode(root, value);
                break;

            case 2:
                printf("Enter value to search: ");
                if (scanf("%d", &value) != 1)
                {
                    printf("Invalid input.\n");
                    freeTree(root);
                    return 1;
                }

                found = searchNode(root, value);

                if (found != NULL)
                    printf("%d found in BST.\n", value);
                else
                    printf("%d not found in BST.\n", value);
                break;

            case 3:
                printf("Enter value to delete: ");
                if (scanf("%d", &value) != 1)
                {
                    printf("Invalid input.\n");
                    freeTree(root);
                    return 1;
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
                if (root == NULL)
                    printf("Tree is empty.\n");
                else
                    displayTreeDetails(root);
                break;

            case 5:
                if (root == NULL)
                {
                    printf("Tree is empty.\n");
                    break;
                }

                printf("Enter K: ");
                if (scanf("%d", &k) != 1)
                {
                    printf("Invalid input.\n");
                    freeTree(root);
                    return 1;
                }

                if (k <= 0 || k > countNodes(root))
                {
                    printf("K is out of range.\n");
                    break;
                }

                visited = 0;
                answer = 0;
                findKthSmallest(root, k, &visited, &answer);
                printf("%dth smallest element = %d\n", k, answer);
                break;

            case 6:
                if (isValidBST(root))
                    printf("Tree follows BST rules.\n");
                else
                    printf("Tree does not follow BST rules.\n");
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    freeTree(root);
    return 0;
}
