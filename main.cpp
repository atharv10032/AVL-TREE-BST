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
    void boundaryOrderTraversal(node *root);
    void printRightBoundary(node *root);
    void printLeftBoundary(node *root);
    void printLeaves(node *root);
    void removeTree(node *&root);
    node *findLCA(node *root, int A1, int A2);
};

void avl_node::removeTree(node *&root)
{
    if (!root)
        return;
    removeTree(root->left);
    removeTree(root->right);
    delete root;
    root = nullptr;
}

void avl_node::printLeaves(node *root)
{
    if (!root)
        return;

    printLeaves(root->right);

    if (!root->left && !root->right)
        cout << root->val << ' ';

    printLeaves(root->left);
}
void avl_node::printRightBoundary(node *root)
{
    if (!root)
        return;
    if (!root->right && !root->left)
        return;
    cout << root->val << ' ';
    if (root->right)
        printRightBoundary(root->right);
    else
        printRightBoundary(root->left);
}
void avl_node::printLeftBoundary(node *root)
{

    if (!root)
        return;
    if (root->left)
    {
        printLeftBoundary(root->left);
        cout << root->val << " ";
    }
    else if (root->right)
    {
        printLeftBoundary(root->right);
        cout << root->val << ' ';
    }
}

void avl_node::boundaryOrderTraversal(node *root)
{
    cout << root->val << ' ';
    printRightBoundary(root->right);

    printLeaves(root);
    printLeftBoundary(root->left);
    cout << endl;
}

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

avl_node::node *avl_node::findLCA(node *root, int A1, int A2)
{
    // Base case: If the root is NULL, return NULL
    if (root == nullptr)
        return nullptr;

    // If both A1 and A2 are smaller than root, then LCA lies in the left subtree
    if (A1 < root->val && A2 < root->val)
        return findLCA(root->left, A1, A2);

    // If both A1 and A2 are greater than root, then LCA lies in the right subtree
    if (A1 > root->val && A2 > root->val)
        return findLCA(root->right, A1, A2);

    // If one key is on one side and the other is on the other side, the current node is the LCA
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
    void boundaryOrderTraversal(node *root);
    void printRightBoundary(node *root);
    void printLeftBoundary(node *root);
    void printLeaves(node *root);
    node *findLCA(node *root, int A1, int A2);
    void removeTree(node *&root);
    node *successor(node *root);
};

bst_node::node *bst_node::successor(node *root)
{
    if (root)
        if (!root->left)
            return root;
    return successor(root->left);
}

bst_node::node *bst_node::delete_key(node *root, int key)
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
    return root;
}
void bst_node::removeTree(node *&root)
{
    if (!root)
        return;
    removeTree(root->left);
    removeTree(root->right);
    delete root;
    root = nullptr;
}

bst_node::node *bst_node::findLCA(node *root, int A1, int A2)
{
    // Base case: If the root is NULL, return NULL
    if (root == nullptr)
        return nullptr;

    // If both A1 and A2 are smaller than root, then LCA lies in the left subtree
    if (A1 < root->val && A2 < root->val)
        return findLCA(root->left, A1, A2);

    // If both A1 and A2 are greater than root, then LCA lies in the right subtree
    if (A1 > root->val && A2 > root->val)
        return findLCA(root->right, A1, A2);

    // If one key is on one side and the other is on the other side, the current node is the LCA
    return root;
}
void postOrderFromPreIn(int pre[], int in[], int inStart, int inEnd, int &preIndex)
{
    if (inStart > inEnd)
        return;

    // The first element in preorder is the root
    int rootVal = pre[preIndex++];

    // Find the index of the root in inorder traversal
    int inIndex;
    for (inIndex = inStart; inIndex <= inEnd; ++inIndex)
    {
        if (in[inIndex] == rootVal)
            break;
    }

    // Recursively find postorder of the left subtree
    postOrderFromPreIn(pre, in, inStart, inIndex - 1, preIndex);

    // Recursively find postorder of the right subtree
    postOrderFromPreIn(pre, in, inIndex + 1, inEnd, preIndex);

    // Print the root after left and right subtrees have been processed
    cout << rootVal << " ";
}

void printPostOrderFromPreIn(int pre[], int in[], int n)
{
    int preIndex = 0;
    postOrderFromPreIn(pre, in, 0, n - 1, preIndex);
}

void preOrderFromPostIn(int post[], int in[], int inStart, int inEnd, int &postIndex)
{
    if (inStart > inEnd)
        return;

    // The last element in postorder is the root
    int rootVal = post[postIndex--];

    // Find the index of the root in inorder traversal
    int inIndex;
    for (inIndex = inStart; inIndex <= inEnd; ++inIndex)
    {
        if (in[inIndex] == rootVal)
            break;
    }

    // Print the root first for preorder
    cout << rootVal << " ";

    // Recursively find preorder of the right subtree (process right subtree first)
    preOrderFromPostIn(post, in, inIndex + 1, inEnd, postIndex);

    // Recursively find preorder of the left subtree
    preOrderFromPostIn(post, in, inStart, inIndex - 1, postIndex);
}

void printPreOrderFromPostIn(int post[], int in[], int n)
{
    int postIndex = n - 1;
    preOrderFromPostIn(post, in, 0, n - 1, postIndex);
}

void bst_node::printLeaves(node *root)
{
    if (!root)
        return;

    printLeaves(root->right);

    if (!root->left && !root->right)
        cout << root->val << ' ';

    printLeaves(root->left);
}
void bst_node::printRightBoundary(node *root)
{
    if (!root)
        return;
    if (!root->right && !root->left)
        return;
    cout << root->val << ' ';
    if (root->right)
        printRightBoundary(root->right);
    else
        printRightBoundary(root->left);
}
void bst_node::printLeftBoundary(node *root)
{

    if (!root)
        return;
    if (root->left)
        printLeftBoundary(root->left);

    else if (root->right)
        printLeftBoundary(root->right);
    if (!root->right && !root->left)
        return;

    cout << root->val << ' ';
}

void bst_node::boundaryOrderTraversal(node *root)
{
    cout << root->val << ' ';
    printRightBoundary(root->right);
    printLeaves(root);
    printLeftBoundary(root->left);
    cout << endl;
}

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
    int testCases;
    cin >> testCases;
    while (testCases--)
    {
        string command;
        bst_node *bstRoot = nullptr;
        avl_node *avlRoot = nullptr;
        bst_node bstTree(0);
        avl_node avlTree(0);
        bool avl = 0, bst = 0;

        while (cin >> command && command != "D")
        {
            if (command == "B" || command == "A")
            {
                int N;
                cin >> N;
                for (int i = 0; i < N; ++i)
                {
                    int value;
                    cin >> value;
                    if (value > 0)
                    {
                        if (command == "B")
                            bstRoot = bstTree.insert(bstRoot, value);
                        else
                            avlRoot = avlTree.insert(avlRoot, value);
                    }
                    else if (value < 0)
                    {
                        if (command == "B")
                            bstRoot = bstTree.delete_key(bstRoot, -value);
                        else
                            avlRoot = avlTree.delete_key(avlRoot, -value);
                    }
                    if (command == "B")
                        bst = 1;
                    else
                        avl = 1;
                }
            }
            else if (command == "I")
            {
                int value;
                cin >> value;
                if (!avl)
                    bstRoot = bstTree.insert(bstRoot, value);
                else
                    avlRoot = avlTree.insert(avlRoot, value);
            }
            else if (command == "R")
            {
                int value;
                cin >> value;
                if (!avl)
                    bstRoot = bstTree.delete_key(bstRoot, value);
                else
                    avlRoot = avlTree.delete_key(avlRoot, value);
            }
            else if (command == "F")
            {
                int X;
                cin >> X;
                if (X > 0)
                {
                    auto node = bstTree.search(bstRoot, X);
                    cout << (node ? "Yes" : "No") << endl;
                }
            }
            else if (command == "L")
            {
                if (!avl)
                    cout << bstTree.countLeaves(bstRoot) << endl;
                else
                    cout << avlTree.countLeaves(avlRoot) << endl;
            }
            else if (command == "N")
            {
                if (!avl)
                    cout << bstTree.numberOfNodes(bstRoot) << endl;
                else
                    cout << avlTree.numberOfNodes(avlRoot) << endl;
            }
            else if (command == "Q")
            {
                if (!avl)
                    bstTree.InOrder(bstRoot);
                else
                    avlTree.InOrder(avlRoot);
                cout << endl;
            }
            else if (command == "W")
            {
                if (!avl)
                    bstTree.PreOrder(bstRoot);
                else
                    avlTree.PreOrder(avlRoot);
                cout << endl;
            }
            else if (command == "E")
            {
                if (!avl)
                    bstTree.PostOrder(bstRoot);
                else
                    avlTree.PostOrder(avlRoot);
                cout << endl;
            }
            else if (command == "H")
            {
                if (!avl)
                    cout << bstTree.height_of_tree(bstRoot) << endl;
                else
                    cout << avlTree.height_of_tree(avlRoot) << endl;
            }
            else if (command == "M")
            {
                if (!avl)
                    bstTree.boundaryOrderTraversal(bstRoot);
                else
                    avlTree.boundaryOrderTraversal(avlRoot);
            }
            else if (command == "C")
            {
                int A1, A2;
                cin >> A1 >> A2;
                if (!avl)
                {
                    auto lca = bstTree.findLCA(bstRoot, A1, A2);
                    cout << (lca ? lca->val : -1) << endl;
                }
                else
                {
                    auto lca = avlTree.findLCA(avlRoot, A1, A2);
                    cout << (lca ? lca->val : -1) << endl;
                }
            }

            else if (command == "Z")
            {
                int N;
                cin >> N;
                int preOrder[N], inOrder[N];
                for (int i = 0; i < N; ++i)
                    cin >> preOrder[i];
                for (int i = 0; i < N; ++i)
                    cin >> inOrder[i];
                printPostOrderFromPreIn(preOrder, inOrder, N);
                cout << endl;
            }
            else if (command == "Y")
            {
                int N;
                cin >> N;
                int postOrder[N], inOrder[N];
                for (int i = 0; i < N; ++i)
                    cin >> postOrder[i];
                for (int i = 0; i < N; ++i)
                    cin >> inOrder[i];
                printPreOrderFromPostIn(postOrder, inOrder, N);
                cout << endl;
            }
            else if (command == "K")
            {
                bstTree.removeTree(bstRoot);
                avlTree.removeTree(avlRoot);
            }
        }
    }
    return 0;
}