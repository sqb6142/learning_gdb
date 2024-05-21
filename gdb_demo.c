#include <stdlib.h>
#include <stdio.h>

typedef struct tree_s {
    int val;
    struct tree_s* left;
    struct tree_s* right;
} tree_t;

void tree_insert(tree_t* t, tree_t* node)
{
    if (node->val < t->val) { // left
        if (t->left) {
            tree_insert(t->left, node);
        } else {
            t->left = node;
        }
    } else if (node->val > t->val) { // right
        if (t->right) {
            tree_insert(t->right, node);
        } else {
            t->right = node;
        }
    } else {
        if (t->left == NULL) {
            t->left = node;
        }
        if (t->right == NULL) {
            t->right = node;
        }
    }
}

tree_t* tree_remove_root(tree_t* t)
{
    tree_t* new = NULL;
    tree_t* prev = NULL;
    if (t->left == NULL) {
        new = t->right;
        t->right = NULL;
    } else if (t->right == NULL) {
        new = t->left;
        t->left = NULL;
    } else {
        prev = t->left;
        new = prev->right;
        while (new->right != NULL) {
            prev = new;
            new = new->right;
        }
        new->left = t->left;
        new->right = t->right;
        prev->right = new->left;
        t->left = NULL;
        t->right = NULL;
    }
    return new;
}

int tree_size(tree_t* t)
{
    int size = 1;
    size += tree_size(t->left);
    size += tree_size(t->right);
    return size;
}

int main(int argc, char** argv)
{
    tree_t nodes[7] = {{4, NULL, NULL},
                       {2, NULL, NULL},
                       {3, NULL, NULL},
                       {6, NULL, NULL},
                       {1, NULL, NULL},
                       {5, NULL, NULL},
                       {7, NULL, NULL}};
    tree_t* root = &nodes[0];
    if (argc > 1) {
        nodes[0].val = atoi(argv[1]);
    }
    for (int i = 1; i < 7; i++) {
        tree_insert(root, &nodes[i]);
    }
    printf("tree size: %d\n", tree_size(root));

    //root = tree_remove_root(root);
    //root = tree_remove_root(root);
    //printf("tree size: %d\n", tree_size(root));
    return 0;
}
