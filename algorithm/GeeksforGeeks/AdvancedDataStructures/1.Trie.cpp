// http://www.geeksforgeeks.org/trie-insert-and-search/

// Trie is an efficient information retrieval data structure. Using trie, search
// complexities can be brought to optimal limit (key length). If we store keys
// in binary search tree, a well balanced BST will need time proportional to
// M * log N, where M is maximum string length and N is number of keys in tree.
// Using trie, we can search the key in O(M) time. However the penalty is on
// trie storage requirements.

// Every node of trie consists of multiple branches. Each branch represents a
// possible character of keys. We need to mark the last node of every key as
// leaf node. A trie node field value will be used to distinguish the node as
// leaf node (there are other uses of the value field). A simple structure to
// represent nodes of English alphabet can be as following,

// struct trie_node
// {
//     int value;                  /* Used to mark leaf nodes */
//     trie_node_t *children[ALPHABET_SIZE];
// };

// Inserting a key into trie is simple approach. Every character of input key
// is inserted as an individual trie node. Note that the children is an array
// of pointers to next level trie nodes. The key character acts as an index into
// the array children. If the input key is new or an extension of existing key,
// we need to construct non-existing nodes of the key, and mark leaf node. If
// the input key is prefix of existing key in trie, we simply mark the last node
// of key as leaf. The key length determines trie depth.

// Searching for a key is similar to insert operation, however we only compare
// the characters and move down. The search can terminate due to end of string
// or lack of key in trie. In the former case, if the value field of last node
// is non-zero then the key exists in trie. In the second case, the search
// terminates without examining all the characters of key, since the key is
// not present in trie.

// The following picture explains construction of trie using keys given in the
// example below,

//       root
//    /   \    \
//    t   a     b
//    |   |     |
//    h   n     y
//    |   |  \  |
//    e   s  y  e
// /  |   |
// i  r   w
// |  |   |
// r  e   e
//        |
//        r

// In the picture, every character is of type trie_node_t. For example, the root
// is of type trie_node_t, and it's children a, b and t are filled, all other
// nodes of root will be NULL. Similarly, 'a' at the next level is having only
// one child ("n"), all other children are NULL. The leaf nodes are in blue.

// Insert and search costs O(key_length), however the memory requirements of
// trie is O(ALPHABET_SIZE * key_length * N) where N is number of keys in trie.
/// There are efficient representation of trie nodes (e.g. compressed trie,
// ternary search tree, etc.) to minimize memory requirements of trie.

// During delete operation we delete the key in bottom up manner using recursion.
// The following are possible conditions when deleting key from trie,

// Key may not be there in trie. Delete operation should not modify trie.
// Key present as unique key (no part of key contains another key (prefix), nor
//    the key itself is prefix of another key in trie). Delete all the nodes.
// Key is prefix key of another long key in trie. Unmark the leaf node.
// Key present in trie, having at least one other key as prefix key. Delete nodes
// from end of key until first leaf node of longest prefix key.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Macros */

// Give an array, return it's size
#define  ARRAY_SIZE(a)    sizeof(a)/sizeof(a[0])
// Alphabet size (# of symbols)
#define  ALPHABET_SIZE    (26)
// Converts key current character into index, e.g. 'b' => 1
// use only 'a' through 'z' and lower case
#define  CHAR_TO_INDEX(c) ((int)c - (int)'a')
// Free a pointer
#define  FREE(p)    { free(p); p = NULL;}



/* Structures */

// trie node
typedef struct trie_node trie_node_t;
struct trie_node
{
    int value;                  // main usage: whether a node is leaf or not
    trie_node_t *children[ALPHABET_SIZE];
};

// trie ADT (trie's root)
typedef struct trie trie_t;
struct trie
{
    trie_node_t *root;
    int count;
};



/* Implementations */

// Returns new trie node (initialized to NULLs)
trie_node_t *getNode(void) {

    trie_node_t *pNode = NULL;

    pNode = (trie_node_t *) malloc(sizeof(trie_node_t));

    if (pNode != NULL) {

        pNode->value = 0;

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            pNode->children[i] = NULL;
        }
    }

    return pNode;
}

// Initializes trie (root is dummy node, we only consider it's children)
void initialize(trie_t *pTrie) {
    pTrie->root = getNode();
    pTrie->count = 0;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(trie_t *pTrie, char key[]) {

    int level;
    int length = strlen(key);
    int index;
    trie_node_t *pCrawl;

    pTrie->count++;
    pCrawl = pTrie->root;

    for (level = 0; level < length; level++) {

        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index]) {
            pCrawl->children[index] = getNode();
        }

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf, non-zero value means not leaf
    pCrawl->value = pTrie->count;
}

// Returns non zero, if key presents in trie
int search(trie_t *pTrie, char key[]) {

    int level;
    int length = strlen(key);
    int index;
    trie_node_t *pCrawl;

    pCrawl = pTrie->root;

    for (level = 0; level < length; level++) {

        index = CHAR_TO_INDEX(key[level]);
        if( !pCrawl->children[index] ) {
            return 0;
        }

        pCrawl = pCrawl->children[index];
    }

    return (0 != pCrawl && pCrawl->value);
}

// return 1 if node is leaf
int leafNode(trie_node_t *pNode) {
    return (pNode->value != 0);
}

// return 1 if node has no children
int isItFreeNode(trie_node_t *pNode) {

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (pNode->children[i])
            return 0;
    }

    return 1;
}

bool deleteHelper(trie_node_t *pNode, char key[], int level, int len) {

    if (pNode == NULL) {
        return false;
    }

    if (level == len) {         // Reach bottom, base case

        if (leafNode(pNode)) {

            pNode->value = 0;   // unmark leaf node

            // If empty, node to be deleted
            if (isItFreeNode(pNode)) {
                return true;    // current node need to be deleted by parent
            }

            return false;
        }
        // return false at last, when key is not present
    } else {                    // Recursive case

        int index = CHAR_TO_INDEX(key[level]);

        if (deleteHelper(pNode->children[index], key, level+1, len)) {

            // last node marked, delete it
            FREE(pNode->children[index]);

            // recursively climb up, and delete eligible nodes (it has no
            // children and is not leaf of other keys)
            return (!leafNode(pNode) && isItFreeNode(pNode));
        }
    }

    return false;
}


void deleteKey(trie_t *pTrie, char key[]) {

    int len = strlen(key);
    if (len > 0) {
        deleteHelper(pTrie->root, key, 0, len);
    }
}



// Driver
int test1()
{
    // Input keys (use only 'a' through 'z' and lower case)
    char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
    trie_t trie;

    char output[][32] = {"Not present in trie", "Present in trie"};

    initialize(&trie);

    // Construct trie
    for (int i = 0; i < ARRAY_SIZE(keys); i++)
    {
        insert(&trie, keys[i]);
    }

    // Search for different keys
    printf("%s --- %s\n", "the", output[search(&trie, "the")] );
    printf("%s --- %s\n", "these", output[search(&trie, "these")] );
    printf("%s --- %s\n", "their", output[search(&trie, "their")] );
    printf("%s --- %s\n", "thaw", output[search(&trie, "thaw")] );

    return 0;
}


int test2()
{
    char keys[][8] = {"she", "sells", "sea", "shore", "the", "by", "sheer"};
    trie_t trie;

    initialize(&trie);

    for (int i = 0; i < ARRAY_SIZE(keys); i++)
    {
        insert(&trie, keys[i]);
    }

    deleteKey(&trie, keys[0]);

    printf("%s %s\n", "she", search(&trie, "she") ?
           "Present in trie" : "Not present in trie");

    return 0;
}


int main(void) {
    test1();
    test2();
}
