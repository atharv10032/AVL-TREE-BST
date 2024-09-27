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
    node *leftRotation(node *root);
    node *rightRotation(node *root);
    node *successor(node *root);
    int countLeaves(node *root);
    int numberOfNodes(node *root);
};

int avl_node::numberOfNodes(node *root)
{
    if (!root)
        return 0;

    return 1 + numberOfNodes(root->left) + numberOfNodes(root->right);
}

int avl_node::countLeaves(node *root)
{
    if (!root)
        return 0;
    if (!root->left && !root->right)
        return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

avl_node::node *avl_node::successor(node *root)
{
    if (root)
        if (!root->left)
            return root;
    return successor(root->left);
}
avl_node::node *avl_node::leftRotation(avl_node::node *root)
{

    avl_node *y = root->right;
    avl_node *x = root;
    x->right = y->left;
    y->left = x;

    x->height = height_of_tree(x);
    y->height = height_of_tree(y);

    return y;
}

avl_node::node *avl_node::rightRotation(avl_node::node *root)
{

    avl_node *x = root;
    avl_node *y = x->left;
    // avl_node* t = y->right ;

    x->left = y->right;

    y->right = x;

    y->height = height_of_tree(y);
    x->height = height_of_tree(x);

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
        return -1;
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
        return rightRotation(root);

    if (bal > 1 && key > root->right->val)
        return leftRotation(root);
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
    int countLeaves(node *root);
    int numberOfNodes(node *root);
};

int bst_node::numberOfNodes(node *root)
{
    if (!root)
        return 0;

    return 1 + numberOfNodes(root->left) + numberOfNodes(root->right);
}

int bst_node::countLeaves(node *root)
{
    if (!root)
        return 0;
    if (!root->left && !root->right)
        return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

bst_node::node *bst_node::insert(node *root, int key)
{
    if (root == nullptr)
    {
        // If the root is null, create a new node
        return new bst_node(key);
    }

    if (key < root->val)
    {
        // Insert in the left subtree if key is smaller
        root->left = insert(root->left, key);
    }
    else if (key > root->val)
    {
        // Insert in the right subtree if key is greater
        root->right = insert(root->right, key);
    }

    // Return the unchanged root pointer
    return root;
}

// Search function for BST
bst_node::node *bst_node::search(node *root, int key)
{
    if (root == nullptr || root->val == key)
    {
        // If the key is found or tree is empty
        return root;
    }

    if (key < root->val)
    {
        // Search the left subtree
        return search(root->left, key);
    }

    // Search the right subtree
    return search(root->right, key);
}

// Function to find the inorder successor (smallest in the right subtree)
bst_node::node *inorderSuccessor(bst_node *root)
{
    bst_node *current = root;
    while (current && current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

// Delete function for BST
bst_node::node *bst_node::delete_key(node *root, int key)
{
    if (root == nullptr)
        return root;

    // Traverse the tree to find the node to be deleted
    if (key < root->val)
        root->left = delete_key(root->left, key);
    else if (key > root->val)
        root->right = delete_key(root->right, key);
    else
    {
        // Node with only one child or no child
        if (root->left == nullptr)
        {
            node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            node *temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children: Get the inorder successor
        node *temp = inorderSuccessor(root->right);

        // Copy the inorder successor's value to this node
        root->val = temp->val;

        // Delete the inorder successor
        root->right = delete_key(root->right, temp->val);
    }
    return root;
}

// InOrder Traversal (Left, Root, Right)
void bst_node::InOrder(node *root)
{
    if (root == nullptr)
        return;
    InOrder(root->left);
    cout << root->val << " ";
    InOrder(root->right);
}

// PreOrder Traversal (Root, Left, Right)
void bst_node::PreOrder(node *root)
{
    if (root == nullptr)
        return;
    cout << root->val << " ";
    PreOrder(root->left);
    PreOrder(root->right);
}

// PostOrder Traversal (Left, Right, Root)
void bst_node::PostOrder(node *root)
{
    if (root == nullptr)
        return;
    PostOrder(root->left);
    PostOrder(root->right);
    cout << root->val << " ";
}

// Function to calculate the height of the tree
int bst_node::height_of_tree(node *root)
{
    if (root == nullptr)
        return 0;
    return 1 + max(height_of_tree(root->left), height_of_tree(root->right));
}

int main()
{

    return 0;
}