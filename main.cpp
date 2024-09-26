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

    // Test deletion
    root = tree.delete_key(root, 20);
    cout << "Level Order Traversal after deletion of 20: ";
    levelOrder(root);
    cout << endl;

    // Test searching for a node
    avl_node *found = tree.search(root, 25);
    if (found)
        cout << "Node with key 25 found." << endl;
    else
        cout << "Node with key 25 not found." << endl;

    return 0;
}