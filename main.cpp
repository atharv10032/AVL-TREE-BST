#include <iostream>
#include <queue>

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
    node *leftRotation(node *root);
    node *rightRotation(node *root);
    node *successor(node *root);
};

void levelOrder(avl_node *root)
{
    if (!root)
        return;

    queue<avl_node *> q;
    q.push(root);

    while (!q.empty())
    {
        avl_node *current = q.front();
        q.pop();

        // Print the value of the current node
        cout << current->val << " ";

        // Enqueue left child
        if (current->left)
            q.push(current->left);

        // Enqueue right child
        if (current->right)
            q.push(current->right);
    }
}

avl_node::node *avl_node::successor(node *root)
{
    if (!root->left)
        return root;
    return successor(root->left);
}
avl_node::node *avl_node::leftRotation(avl_node::node *root)
{

    avl_node *y = root->left;
    avl_node *x = root;
    avl_node *z = y->left;

    node *B = y->right;
    y->right = x;
    x->left = B;
    if (x)
        x->height = height_of_tree(x);
    if (y)
        y->height = height_of_tree(y);
    if (z)
        z->height = height_of_tree(z);

    return y;
}

avl_node::node *avl_node::rightRotation(avl_node::node *root)
{

    avl_node *x = root;
    avl_node *y = x->right;
    avl_node *z = y->right;

    node *B = y->left;
    y->left = x;
    x->right = B;

    x->height = height_of_tree(x);
    y->height = height_of_tree(y);
    z->height = height_of_tree(z);

    return y;
}

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

avl_node::node *avl_node::delete_key(node *root, int key)
{
    if (!root)
        return root;

    if (key < root->val)
        root->left = delete_key(root->left, key);
    else if (key > root->val)
        root->right = delete_key(root->right, key);
    else
    {
        if (!root->left && !root->right)
            return nullptr;
        if (!root->right)
            return root->left;
        if (!root->left)
            return root->right;
        node *succ = successor(root->right);
        root->val = succ->val;
        root->right = delete_key(root->right, succ->val);
        return root;
    }

    root->height = height_of_tree(root);

    int bal = heavy(root);

    if (bal > 1 && heavy(root->right) >= 0)
        return leftRotation(root);
    else if (bal < -1 && heavy(root->left) <= 0)
        return rightRotation(root);
    else if (bal > 1 && heavy(root->right) < 0)
    {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }
    else if (bal < -1 && heavy(root->left) > 0)
    {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }

    return root;
}
avl_node ::node *avl_node::insert(node *root, int key)
{
    if (root == nullptr)
        return new avl_node(key);
    if (root->val < key)
        root->right = insert(root->right, key);
    else if (root->val > key)
        root->left = insert(root->left, key);
    else
        return root;
    root->height = height_of_tree(root);

    int bal = heavy(root);

    if (bal < -1 && key < root->left->val)
        return leftRotation(root);

    if (bal > 1 && key > root->right->val)
        return rightRotation(root);
    if (bal < -1 && key > root->left->val)
    {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }

    if (bal > 1 && key < root->left->val)
    {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    return root;
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
    avl_node *root = nullptr;
    avl_node tree(0); // Just creating an instance for method calls

    // Insert some keys into the AVL tree
    root = tree.insert(root, 30);
    root = tree.insert(root, 20);
    root = tree.insert(root, 10); // This will trigger balancing
    root = tree.insert(root, 40);
    root = tree.insert(root, 50); // This will also trigger balancing
    root = tree.insert(root, 25);

    // Level order traversal to check the structure of the AVL tree
    cout << "Level Order Traversal after insertions: ";
    levelOrder(root);
    cout << endl;

    // // Test deletion
    // root = tree.delete_key(root, 20);
    // cout << "Level Order Traversal after deletion of 20: ";
    // levelOrder(root);
    // cout << endl;

    return 0;
}