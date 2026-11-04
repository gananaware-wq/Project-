/*
  Question 8: AVL Tree - Advanced Implementation
  File: avl_tree_insert_delete_rotations.c

  Practical requirements:
    Insert node
    Balance the tree
    Search node
    Delete node

  Additional operations:
    Inorder, preorder and postorder traversal
    Display height and balance factor
    Count total nodes
    Validate AVL balance and BST ordering

  Height convention:
    NULL subtree has height 0; a leaf node has height 1.
  Duplicate values are ignored.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    int height;
    struct node *left;
    struct node *right;
} node;

node *createNode(int data);
int height(node *root);
int maxValue(int a, int b);
int getBalance(node *root);
node *rightRotate(node *y);
node *leftRotate(node *x);
node *insertNode(node *root, int data);
node *deleteNode(node *root, int key);
node *findMinimum(node *root);
node *searchNode(node *root, int key);
void inorder(node *root);
void preorder(node *root);
void postorder(node *root);
int countNodes(node *root);
int validateAVL(node *root);
void displayTree(node *root);
void freeTree(node *root);

int main()
{
    node *root = NULL;
    node *found;
    int choice, value;

    do
    {
        printf("\n---------------- AVL TREE ----------------\n");
        printf("1. Insert node\n");
        printf("2. Search node\n");
        printf("3. Delete node\n");
        printf("4. Inorder traversal\n");
        printf("5. Preorder traversal\n");
        printf("6. Postorder traversal\n");
        printf("7. Display tree details\n");
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
                    goto input_error;

                root = insertNode(root, value);
                break;

            case 2:
                printf("Enter value to search: ");
                if (scanf("%d", &value) != 1)
                    goto input_error;

                found = searchNode(root, value);
                if (found != NULL)
                    printf("%d found in AVL tree.\n", value);
                else
                    printf("%d not found.\n", value);
                break;

            case 3:
                printf("Enter value to delete: ");
                if (scanf("%d", &value) != 1)
                    goto input_error;

                if (searchNode(root, value) == NULL)
                    printf("Value not found.\n");
                else
                {
                    root = deleteNode(root, value);
                    printf("Node deleted successfully.\n");
                }
                break;

            case 4:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;

            case 6:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;

            case 7:
                displayTree(root);
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

input_error:
    printf("Invalid input. Releasing allocated memory.\n");
    freeTree(root);
    return 1;
}

node *createNode(int data)
{
    node *newnode;

    newnode = (node *)malloc(sizeof(node));
    if (newnode == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    newnode->data = data;
    newnode->height = 1;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

int height(node *root)
{
    if (root == NULL)
        return 0;

    return root->height;
}

int maxValue(int a, int b)
{
    return (a > b) ? a : b;
}

int getBalance(node *root)
{
    if (root == NULL)
        return 0;

    return height(root->left) - height(root->right);
}

/*
   Right rotation:
          y                 x
         / \               / \
        x   T3   --->     T1  y
       / \                   / \
      T1 T2                 T2 T3

   Update the lower node's height before updating the new root.
*/
node *rightRotate(node *y)
{
    node *x, *t2;

    x = y->left;
    t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = 1 + maxValue(height(y->left), height(y->right));
    x->height = 1 + maxValue(height(x->left), height(x->right));

    return x;
}

/*
   Left rotation is the mirror image of right rotation.
*/
node *leftRotate(node *x)
{
    node *y, *t2;

    y = x->right;
    t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = 1 + maxValue(height(x->left), height(x->right));
    y->height = 1 + maxValue(height(y->left), height(y->right));

    return y;
}

node *insertNode(node *root, int data)
{
    int balance;

    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insertNode(root->left, data);
    else if (data > root->data)
        root->right = insertNode(root->right, data);
    else
    {
        printf("Duplicate value ignored.\n");
        return root;
    }

    /* Update height after insertion into one subtree. */
    root->height = 1 + maxValue(height(root->left), height(root->right));
    balance = getBalance(root);

    /* LL case: left subtree of left child became heavy. */
    if (balance > 1 && data < root->left->data)
        return rightRotate(root);

    /* RR case: right subtree of right child became heavy. */
    if (balance < -1 && data > root->right->data)
        return leftRotate(root);

    /* LR case: left rotate child, then right rotate root. */
    if (balance > 1 && data > root->left->data)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    /* RL case: right rotate child, then left rotate root. */
    if (balance < -1 && data < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

node *findMinimum(node *root)
{
    if (root == NULL)
        return NULL;

    while (root->left != NULL)
        root = root->left;

    return root;
}

node *deleteNode(node *root, int key)
{
    node *temp;
    int balance;

    if (root == NULL)
        return NULL;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else
    {
        /* Node with zero or one child. */
        if (root->left == NULL || root->right == NULL)
        {
            temp = (root->left != NULL) ? root->left : root->right;

            if (temp == NULL)
            {
                /* No child: release this leaf node. */
                free(root);
                return NULL;
            }
            else
            {
                /*
                   One child: copy the child's contents into this node,
                   then free the child's allocation.
                */
                *root = *temp;
                free(temp);
            }
        }
        else
        {
            /*
               Two children: replace with inorder successor, then
               remove that successor from the right subtree.
            */
            temp = findMinimum(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    /* A deleted leaf may make this subtree empty. */
    if (root == NULL)
        return NULL;

    root->height = 1 + maxValue(height(root->left), height(root->right));
    balance = getBalance(root);

    /*
       Deletion rebalancing uses the child's balance factor.
       Unlike insertion, the key alone is not enough to choose the case.
    */

    /* LL case or balanced left child. */
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    /* LR case. */
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    /* RR case or balanced right child. */
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    /* RL case. */
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

node *searchNode(node *root, int key)
{
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return searchNode(root->left, key);

    return searchNode(root->right, key);
}

void inorder(node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(node *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int countNodes(node *root)
{
    if (root == NULL)
        return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

/*
   Return 1 only if every node has a valid balance factor
   and its stored height matches the actual subtree height.
*/
int validateAVL(node *root)
{
    int leftHeight, rightHeight, difference;

    if (root == NULL)
        return 1;

    if (!validateAVL(root->left) || !validateAVL(root->right))
        return 0;

    leftHeight = height(root->left);
    rightHeight = height(root->right);
    difference = leftHeight - rightHeight;

    if (difference < -1 || difference > 1)
        return 0;

    if (root->height != 1 + maxValue(leftHeight, rightHeight))
        return 0;

    if (root->left != NULL && root->left->data >= root->data)
        return 0;

    if (root->right != NULL && root->right->data <= root->data)
        return 0;

    return 1;
}

void displayTree(node *root)
{
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }

    printf("Inorder traversal : ");
    inorder(root);

    printf("\nPreorder traversal: ");
    preorder(root);

    printf("\nPostorder traversal: ");
    postorder(root);

    printf("\nHeight (nodes)     : %d", height(root));
    printf("\nTotal nodes        : %d", countNodes(root));
    printf("\nRoot balance factor: %d", getBalance(root));
    printf("\nAVL validation     : %s\n",
           validateAVL(root) ? "Valid" : "Invalid");
}

void freeTree(node *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
