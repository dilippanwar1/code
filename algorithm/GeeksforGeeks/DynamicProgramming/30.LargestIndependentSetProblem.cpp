// http://www.geeksforgeeks.org/largest-independent-set-problem/

// Given a Binary Tree, find size of the Largest Independent Set (LIS) in it.
// A subset of all tree nodes is an independent set if there is no edge between
// any two nodes of the subset.
// For example, consider the following binary tree. The largest independent
// set(LIS) is {10, 40, 60, 70, 80} and size of the LIS is 5.
//                    10
//                   /  \
//                 20   30
//                /  \    \
//              40   50    60
//                  /  \
//                70    80

// Following extensions to above solution can be tried as an exercise.
// 1) Extend the above solution for n-ary tree.
// 2) The above solution modifies the given tree structure by adding an
//    additional field 'liss' to tree nodes. Extend the solution so that it
//    doesn't modify the tree structure.
// 3) The above solution only returns size of LIS, it doesn't print elements
//    of LIS. Extend the solution to print all nodes that are part of LIS.

#include <stdio.h>
#include <stdlib.h>


struct node
{
    int data;
    int liss;
    int liss_true;
    int liss_false;
    struct node *left, *right;
};

// A utility function to create a node
struct node* newNode(int data) {
    struct node* temp = (struct node *) malloc( sizeof(struct node) );
    temp->data = data;
    temp->liss = -1;
    temp->liss_true = -1;
    temp->liss_false = -1;
    temp->left = temp->right = NULL;
    return temp;
}

// A utility function to create a random tree
struct node* newTree(int size) {

    if (size == 0) {
        return NULL;
    }
    if (size == 1) {
        struct node *leaf = newNode(rand());
        leaf->left = NULL;
        leaf->right = NULL;
        return leaf;
    }

    struct node *root = newNode(rand());
    root->left = newTree(size / 2);
    root->right = newTree(size / 2);

    return root;
}


// A utility function to find max of two integers
int max(int x, int y) { return (x > y)? x: y; }

// The function returns size of the largest independent set in a given
// binary tree
int LISS(struct node *root)
{
    if (root == NULL)
        return 0;

    // Caculate size excluding the current node
    int size_excl = LISS(root->left) + LISS(root->right);

    // Calculate size including the current node
    int size_incl = 1;
    if (root->left)
        size_incl += LISS(root->left->left) + LISS(root->left->right);
    if (root->right)
        size_incl += LISS(root->right->left) + LISS(root->right->right);

    // Return the maximum of two sizes
    return max(size_incl, size_excl);
}

// A memoization function returns size of the largest independent set in
// a given binary tree
int LISSDP(struct node *root)
{
    if (root == NULL)
        return 0;

    if (root->liss)
        return root->liss;

    if (root->left == NULL && root->right == NULL)
        return (root->liss = 1);

    // Caculate size excluding the current node
    int liss_excl = LISSDP(root->left) + LISSDP(root->right);

    // Calculate size including the current node
    int liss_incl = 1;
    if (root->left)
        liss_incl += LISSDP(root->left->left) + LISSDP(root->left->right);
    if (root->right)
        liss_incl += LISSDP(root->right->left) + LISSDP(root->right->right);

    // Return the maximum of two sizes
    root->liss = max(liss_incl, liss_excl);

    return root->liss;
}


class MySolution {
public:
    int LISS(struct node *root) {
        return max(LISSHelper(root, true), LISSHelper(root, false));
    }

private:
    // As in geeksforgeeks solution, instead of using a boolean `use`, we
    // can jump two hops to exclude current node.
    int LISSHelper(struct node *root, bool use) {

        if (use == true && root->liss_true != -1) {
            return root->liss_true;
        }
        if (use == false && root->liss_false != -1) {
            return root->liss_false;
        }

        if (root == NULL) {
            return 0;
        }
        if (root->left == NULL && root->right == NULL) {
            if (use == true) {
                return 1;
            } else {
                return 0;
            }
        }

        if (use == true) {
            root->liss_true = LISSHelper(root->left, false) +
                LISSHelper(root->right, false) + 1;
            return root->liss_true;
        } else {
            root->liss_false = max(LISSHelper(root->left, false),
                                   LISSHelper(root->left, true)) +
                max(LISSHelper(root->right, false),
                    LISSHelper(root->right, true));
            return root->liss_false;
        }
    }

    int max(int a, int b) {
        return a > b ? a : b;
    }
};


// Driver program to test above functions
int main()
{
    // Let us construct the tree given in the above diagram
    MySolution solution;
    struct node *root = newTree(100000);
    // struct node *root         = newNode(20);
    // root->left                = newNode(8);
    // root->left->left          = newNode(4);
    // root->left->right         = newNode(12);
    // root->left->right->left   = newNode(10);
    // root->left->right->right  = newNode(14);
    // root->right               = newNode(22);
    // root->right->right        = newNode(25);

    //printf ("Size of the Largest Independent Set is %d\n", LISS(root));
    printf ("Size of the Largest Independent Set is %d\n", LISSDP(root));
    //printf ("Size of the Largest Independent Set is %d\n", solution.LISS(root));

    return 0;
}
