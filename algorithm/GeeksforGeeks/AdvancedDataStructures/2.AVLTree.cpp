// http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
// http://www.geeksforgeeks.org/avl-tree-set-2-deletion/

// AVL tree is a self-balancing Binary Search Tree (BST) where the difference
// between heights of left and right subtrees cannot be more than one for all
// nodes.

// Why AVL Trees?
// Most of the BST operations (e.g., search, max, min, insert, delete.. etc)
// take O(h) time where h is the height of the BST. The cost of these operations
// may become O(n) for a skewed Binary tree. If we make sure that height of the
// tree remains O(Logn) after every insertion and deletion, then we can guarantee
// an upper bound of O(Logn) for all these operations. The height of an AVL tree
// is always O(Logn) where n is the number of nodes in the tree (See this video
// lecture for proof).

// Insertion
// To make sure that the given tree remains AVL after every insertion, we must
// augment the standard BST insert operation to perform some re-balancing.
// Following are two basic operations that can be performed to re-balance a BST
// without violating the BST property (keys(left) < key(root) < keys(right)).
//    1) Left Rotation
//    2) Right Rotation

// T1, T2 and T3 are subtrees of the tree rooted with y (on left side)
// or x (on right side)
//                 y                                   x
//                / \         Right Rotation          /  \
//               x   T3       – - – - – - – >        T1   y
//              / \           < - - - - - - -            / \
//             T1  T2         Left Rotation            T2  T3
// Keys in both of the above trees follow the following order
//      keys(T1) < key(x) < keys(T2) < key(y) < keys(T3)
// So BST property is not violated anywhere.

// Steps to follow for insertion, let the newly inserted node be w:
// 1) Perform standard BST insert for w.
// 2) Starting from w, travel up and find the first unbalanced node. Let z be the
//    first unbalanced node, y be the child of z that comes on the path from w to
//    z and x be the grandchild of z that comes on the path from w to z.
// 3) Re-balance the tree by performing appropriate rotations on the subtree
//    rooted with z. There can be 4 possible cases that needs to be handled as x,
//    y and z can be arranged in 4 ways. Following are the possible 4 arrangements:
//    a) y is left child of z and x is left child of y (Left Left Case)
//    b) y is left child of z and x is right child of y (Left Right Case)
//    c) y is right child of z and x is right child of y (Right Right Case)
//    d) y is right child of z and x is left child of y (Right Left Case)

// Following are the operations to be performed in above mentioned 4 cases. In
// all of the cases, we only need to re-balance the subtree rooted with z and the
// complete tree becomes balanced as the height of subtree (After appropriate
// rotations) rooted with z becomes same as it was before insertion. (See this
// video lecture for proof)

// a) Left Left Case
// T1, T2, T3 and T4 are subtrees.
//          z                                      y
//         / \                                   /   \
//        y   T4      Right Rotate (z)          x      z
//       / \          - - - - - - - - ->      /  \    /  \
//      x   T3                               T1  T2  T3  T4
//     / \
//   T1   T2

// b) Left Right Case
//      z                               z                           x
//     / \                            /   \                        /  \
//    y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
//   / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
// T1   x                          y    T3                    T1  T2 T3  T4
//     / \                        / \
//   T2   T3                    T1   T2

// c) Right Right Case
//   z                                y
//  /  \                            /   \
// T1   y     Left Rotate(z)       z      x
//     /  \   - - - - - - - ->    / \    / \
//    T2   x                     T1  T2 T3  T4
//        / \
//      T3  T4

// d) Right Left Case
//    z                            z                            x
//   / \                          / \                          /  \
// T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      x
//     / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
//    x   T4                      T2   y                  T1  T2  T3  T4
//   / \                              /  \
// T2   T3                           T3   T4

// C implementation
// Following is the C implementation for AVL Tree Insertion. The following C
// implementation uses the recursive BST insert to insert a new node. In the
// recursive BST insert, after insertion, we get pointers to all ancestors one
// by one in bottom up manner. So we don't need parent pointer to travel up.
// The recursive code itself travels up and visits all the ancestors of the
// newly inserted node.

// 1) Perform the normal BST insertion.
// 2) The current node must be one of the ancestors of the newly inserted node.
//    Update the height of the current node.
// 3) Get the balance factor (left subtree height – right subtree height) of the
//    current node.
// 4) If balance factor is greater than 1, then the current node is unbalanced
//    and we are either in Left Left case or left Right case. To check whether
//    it is left left case or not, compare the newly inserted key with the key
//    in left subtree root.
// 5) If balance factor is less than -1, then the current node is unbalanced and
//    we are either in Right Right case or Right Left case. To check whether it
//    is Right Right case or not, compare the newly inserted key with the key in
//    right subtree root.

// Time Complexity: The rotation operations (left and right rotate) take constant
// time as only few pointers are being changed there. Updating the height and
// getting the balance factor also take constant time. So the time complexity of
// AVL insert remains same as BST insert which is O(h) where h is height of the
// tree. Since AVL tree is balanced, the height is O(Logn). So time complexity of
// AVL insert is O(Logn).

// The AVL tree and other self balancing search trees like Red Black are useful
// to get all basic operations done in O(Logn) time. The AVL trees are more
// balanced compared to Red Black Trees, but they may cause more rotations during
// insertion and deletion. So if your application involves many frequent
// insertions and deletions, then Red Black trees should be preferred. And if the
// insertions and deletions are less frequent and search is more frequent operation,
// then AVL tree should be preferred over Red Black Tree.

// Following are some previous posts that have used self-balancing search trees.

// Median in a stream of integers (running integers)
// Maximum of all subarrays of size k
// Count smaller elements on right side

#include <stdio.h>
#include <stdlib.h>


// An AVL tree node
struct node
{
    int key;
    int height;
    struct node *left;
    struct node *right;
};

// A utility function to get height of the tree
int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Helper function that allocates a new node with the given key and
   NULL left and right pointers. */
struct node* newNode(int key)
{
    struct node* node = (struct node*)
        malloc(sizeof(struct node));
    node->key    = key;
    node->height = 1;  // new node is initially added at leaf
    node->left   = NULL;
    node->right  = NULL;
    return node;
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct node *N)
{
    if (N == NULL) {
        return 0;
    }

    return height(N->left) - height(N->right);
}

struct node* insert(struct node* node, int key)
{
    /* 1. Perform the normal BST rotation */
    if (node == NULL)
        return newNode(key);

    if (key < node->key) {
        node->left  = insert(node->left, key);
    } else {
        node->right = insert(node->right, key);
    }

    /* 2. Update height of this ancestor node */
    node->height = max(height(node->left), height(node->right)) + 1;

    /* 3. Get the balance factor of this ancestor node to check whether
       this node became unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
struct node * minValueNode(struct node* node)
{
    struct node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

struct node* deleteNode(struct node* root, int key)
{
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if ( key < root->key )
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if( key > root->key )
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then This is the node
    // to be deleted
    else {
        // node with only one child or no child
        if (root->left == NULL || root->right == NULL) {

            struct node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else { // One child case
                *root = *temp; // Copy the contents of the non-empty child
            }

            free(temp);
        } else {
            // node with two children: Get the inorder successor (smallest
            // in the right subtree)
            struct node* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = max(height(root->left), height(root->right)) + 1;

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
    //  this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// A utility function to print preorder traversal of the tree.
// The function also prints height of every node
void preOrder(struct node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

/* Driver program to test above function*/
int test1()
{
    struct node *root = NULL;

    /* Constructing tree given in the above figure */
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    /* The constructed AVL Tree would be
          30
         /  \
        20   40
       /  \     \
      10  25    50
    */

    printf("Pre order traversal of the constructed AVL tree is \n");
    preOrder(root);
    printf("\n");

    return 0;
}

int test2()
{
    struct node *root = NULL;

    /* Constructing tree given in the above figure */
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);

    /* The constructed AVL Tree would be
             9
            /  \
           1    10
          /  \     \
         0    5     11
        /    /  \
       -1   2    6
    */

    printf("Pre order traversal of the constructed AVL tree is \n");
    preOrder(root);
    printf("\n");

    root = deleteNode(root, 10);

    /* The AVL Tree after deletion of 10
            1
           /  \
          0    9
         /     /  \
       -1    5     11
       /  \
      2    6
    */

    printf("Pre order traversal after deletion of 10 \n");
    preOrder(root);
    printf("\n");

    return 0;
}

int main(void) {
    test1();
    test2();
}
