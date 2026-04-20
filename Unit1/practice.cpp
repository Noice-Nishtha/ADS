// Finding Height of Tree
// Finding Leaf Nodes
// COunting number of nodes

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct Node
{
    int data;
    Node *left, *right;

    Node(int d)
    {
        data = d;
        left = right = nullptr;
    }
};

class BT
{
public:
    Node *root;

    BT()
    {
        root = nullptr;
    }

    // Insert (BST style)
    Node *insert(Node *root, int d)
    {
        if (root == nullptr)
            return new Node(d);

        if (d < root->data)
            root->left = insert(root->left, d);
        else if (d > root->data)
            root->right = insert(root->right, d);

        return root;
    }

    // Inorder Traversal
    void inorder(Node *root)
    {
        if (root == nullptr)
            return;

        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }

    // Preorder Traversal
    int countNodes(Node *root)
    {
        if (root == nullptr)
            return 0;

        return 1 + countNodes(root->left) + countNodes(root->right);
    }

    // Postorder Traversal
    void postorder(Node *root)
    {
        if (root == nullptr)
            return;

        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }

    int height(Node *root)
    {
        // queue<Node *> q;
        // q.push(root);

        // int h = -1;
        // while (!q.empty())
        // {
        //     int size = q.size();
        //     h++;
        //     for (int i = 0; i < size; i++)
        //     {
        //         Node *curr = q.front();
        //         q.pop();

        //         if (curr->left)
        //         {
        //             q.push(curr->left);
        //         }
        //         if (curr->right)
        //         {
        //             q.push(curr->right);
        //         }
        //     }
        // return h;

        if (root == nullptr)
            return -1;

        int LH = height(root->left);
        int RH = height(root->right);

        return max(LH, RH) + 1;
    }
    void printleaf(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }

        // stack<Node *> st;
        // st.push(root);
        // while (!st.empty())
        // {
        //     Node *curr = st.top();
        //     st.pop();

        //     if (curr->left == nullptr && curr->right == nullptr)
        //     {
        //         cout << curr->data << endl;
        //     }
        //     if (curr->left)
        //         st.push(curr->left);
        //     if (curr->right)
        //         st.push(curr->right);
        // }
        if (root->left == nullptr && root->right == nullptr)
        {
            cout << root->data << endl;
            return;
        }
        printleaf(root->left);
        printleaf(root->right);
    }
    int countLeafNodes(Node *root)
    {
        if (root == nullptr)
            return 0;

        if (root->left == nullptr && root->right == nullptr)
            return 1;

        return countLeafNodes(root->left) + countLeafNodes(root->right);
    }
};

int main()
{
    BT t;

    // Build tree
    t.root = t.insert(t.root, 10);
    t.root = t.insert(t.root, 5);
    t.root = t.insert(t.root, 15);
    t.root = t.insert(t.root, 2);
    t.root = t.insert(t.root, 7);

    // cout << "Inorder: ";
    // t.inorder(t.root);
    // cout << endl;

    cout << "counting number of nodes: " << t.countNodes(t.root);
    cout << endl;

    // cout << "Postorder: ";
    // t.postorder(t.root);
    // cout << endl;

    cout << "Height: " << t.height(t.root) << "\n";
    t.printleaf(t.root);
    cout << "COunt of leaf nodes:" << t.countLeafNodes(t.root);
    return 0;
}