#include <iostream>

using namespace std;

class avl_node
{
public:
    using node = avl_node;
    node *left, *right;
    int val, height;
    avl_node(int val)
    {
        this->val = val;
        height = 0;
        left = right = nullptr;
    }
    node *insert(node *root, int key);
    node *delete_key(node *root, int key);
    node *search(node *root, int key);
    void InOrder(node *root);
    void PreOrder(node *root);
    void PostOrder(node *root);
    int height_of_tree(node *root);
    int heavy(node *root);
};

int avl_node::heavy(avl_node ::node *root)
{
    if (!root)
        return 0;
    int r = -1, l = -1;
    if (root->right)
        r = root->right->height;
    if (root->left)
        l = root->left->height;
    return r - l;
}

int avl_node::height_of_tree(node *root)
{
    if (!root)
        return 0;
    else
        return 1 + max(height_of_tree(root->left), height_of_tree(root->right));
}

avl_node ::node *avl_node::insert(node *root, int key)
{
    if (root == nullptr)
        return new avl_node(key);
    if (root->val > key)
        root->right = insert(root->right, key);
    else if (root->val < key)
        root->left = insert(root->left, key);
    else
        return root;
    root->height = height_of_tree(root);
}

class bst_node
{
public:
    using node = bst_node;
    bst_node *left, *right;
    int val;
    bst_node(int val)
    {
        this->val = val;
        left = right = nullptr;
    }
    node *insert(node *root, int key);
    node *delete_key(node *root, int key);
    node *search(node *root, int key);
    void InOrder(node *root);
    void PreOrder(node *root);
    void PostOrder(node *root);
    int height_of_tree(node *root);
};

int main()
{
}